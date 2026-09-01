#include "display_manager.h"
#include "telemetry.h"
#include "touch.h"
#include "ui/screens.h"
#include "ui/ui.h"
#include "ui/vars.h"
#include <lvgl.h>

// Hardware DVI Display Instance
static DVIGFX16 display(DVI_RES_400x240p60, picodvi_dvi_cfg, VREG_VOLTAGE_1_25);

// LVGL Display Buffer (8 lines partial buffer = SCREEN_WIDTH * 8 * 2 = 240 * 8
// * 2 = 3840 bytes)
#define LVGL_BUF_LINES 8
static lv_color_t lvgl_buf[SCREEN_WIDTH * LVGL_BUF_LINES];
static lv_disp_draw_buf_t draw_buf;
static lv_disp_drv_t disp_drv;
static lv_indev_drv_t indev_drv;

/**
 * @brief LVGL flush callback rendering drawn buffers to the PicoDVI
 * framebuffer.
 */
static void dvi_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area,
                         lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
  display.drawRGBBitmap(area->x1, area->y1, (const uint16_t *)color_p, w, h);
  lv_disp_flush_ready(disp_drv);
}

/**
 * @brief LVGL touch input device read callback bridging hardware touch
 * controller.
 */
static void touch_read_cb(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
  (void)indev_drv;
  if (touch_has_signal()) {
    if (touch_touched()) {
      data->state = LV_INDEV_STATE_PR;
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
    } else if (touch_released()) {
      data->state = LV_INDEV_STATE_REL;
    }
  } else {
    data->state = LV_INDEV_STATE_REL;
  }
}

// Profile Definitions
typedef enum {
  PROFILE_MANUAL = 0,
  PROFILE_LEAD_FREE = 1,
  PROFILE_LEADED = 2,
  PROFILE_LOW_TEMP = 3
} ReflowProfile;

static ReflowProfile g_selected_profile = PROFILE_MANUAL;

static const char *g_profile_names[] = {"MANUAL", "LEAD FREE", "LEADED",
                                        "LOW TEMP"};

static const int g_profile_temps[] = {
    0,   // MANUAL (preserves user setpoint)
    245, // LEAD FREE (~245°C)
    215, // LEADED (~215°C)
    150  // LOW TEMP (~150°C)
};

// 4-Stage Reflow State Machine
typedef enum {
  STAGE_IDLE = 0,
  STAGE_PREHEAT = 1,
  STAGE_SOAK = 2,
  STAGE_REFLOW = 3,
  STAGE_COOL = 4,
  STAGE_DONE = 5
} ReflowStage;

struct ProfileStageConfig {
  int preheat_temp;        // °C (preheat target)
  uint32_t preheat_time_s; // nominal target duration in preheat (seconds)
  int soak_temp;           // °C (soak target)
  uint32_t soak_time_s;    // seconds in soak zone
  int peak_temp;           // °C (peak reflow target)
  uint32_t peak_dwell_s;   // seconds dwell at peak
  int cool_temp;           // °C (safe handling temperature)
  uint32_t cool_time_s;    // nominal cooling duration (seconds)
};

static const ProfileStageConfig g_profile_configs[4] = {
    {0, 0, 0, 0, 0, 0, 50, 0},             // MANUAL
    {150, 90, 175, 60, 245, 30, 50, 120},  // LEAD FREE: SAC305 (~245°C peak)
    {130, 80, 155, 60, 215, 30, 50, 120},  // LEADED: Sn63Pb37 (~215°C peak)
    {90, 60, 115, 45, 150, 25, 45, 90}     // LOW TEMP: Sn42Bi58 (~150°C peak)
};

static ReflowStage g_reflow_stage = STAGE_IDLE;
static uint32_t g_stage_start_time = 0;
static float g_stage_start_temp = 25.0f;
static float g_peak_reached_temp = 0.0f;
static bool g_last_heater_state = false;
static float g_manual_start_temp = 25.0f;
static int32_t g_ui_progress = 0;

// Timing tracking and formatting buffers
static char g_ui_stage_time[16] = "IDLE";
static char g_ui_stage_target[16] = "N/A";
static char g_ui_profile_time[16] = "IDLE";
static uint32_t g_profile_start_time = 0;

static void format_duration(char *buf, size_t buf_size, uint32_t total_sec) {
  uint32_t sec = total_sec % 60;
  uint32_t min = (total_sec / 60) % 60;
  uint32_t hr = total_sec / 3600;
  if (hr > 0) {
    snprintf(buf, buf_size, "%lu:%02lu:%02lu", (unsigned long)hr,
             (unsigned long)min, (unsigned long)sec);
  } else {
    snprintf(buf, buf_size, "%lu:%02lu", (unsigned long)min,
             (unsigned long)sec);
  }
}

/**
 * @brief Updates active reflow profile stages and calculates UI progress:
 * 1. Manual profile: 0 - 100 progress for heating towards setpoint.
 * 2. Reflow profiles: 0 - 1000 divided into 4 stages of 250 each (PREHEAT,
 * SOAK, REFLOW, COOL).
 */
static void update_profile_and_progress() {
  bool heater_active = is_heater_on();
  float current_temp = get_measured_temp();

  // Keep bar range in sync with active profile mode
  if (objects.obj14) {
    int32_t desired_max = (g_selected_profile == PROFILE_MANUAL) ? 100 : 1000;
    if (lv_bar_get_max_value(objects.obj14) != desired_max) {
      lv_bar_set_range(objects.obj14, 0, desired_max);
    }
  }

  // Detect heater start event
  if (heater_active && !g_last_heater_state) {
    g_manual_start_temp = current_temp;
    g_profile_start_time = millis();
    if (g_selected_profile != PROFILE_MANUAL) {
      g_reflow_stage = STAGE_PREHEAT;
      g_stage_start_time = millis();
      g_stage_start_temp = current_temp;
      const ProfileStageConfig &cfg =
          g_profile_configs[(int)g_selected_profile];
      set_desired_temp(cfg.preheat_temp);
      log_printf("[Profile] Started %s profile -> Stage PREHEAT (Target: %dC)",
                 g_profile_names[(int)g_selected_profile], cfg.preheat_temp);
    } else {
      log_printf("[Profile] Started MANUAL mode (Target: %dC, Start Temp: %.1fC)",
                 get_desired_temp(), current_temp);
    }
  }

  // Detect heater stop event (user aborted heating)
  if (!heater_active && g_last_heater_state) {
    if (g_reflow_stage != STAGE_COOL && g_reflow_stage != STAGE_DONE) {
      log_println("[Profile] Heating stopped by user. Returning to IDLE.");
      g_reflow_stage = STAGE_IDLE;
      g_ui_progress = 0;
    }
  }
  g_last_heater_state = heater_active;

  // --- MANUAL PROFILE (0 - 100) ---
  if (g_selected_profile == PROFILE_MANUAL) {
    g_reflow_stage = STAGE_IDLE;
    if (!heater_active || is_error_state()) {
      g_ui_progress = 0;
    } else {
      float target = (float)get_desired_temp();
      float span = target - g_manual_start_temp;
      if (span <= 1.0f) {
        g_ui_progress = (current_temp >= target) ? 100 : 0;
      } else {
        float pct = ((current_temp - g_manual_start_temp) / span) * 100.0f;
        if (pct < 0.0f)
          pct = 0.0f;
        if (pct > 100.0f)
          pct = 100.0f;
        g_ui_progress = (int32_t)(pct + 0.5f);
      }
    }
    return;
  }

  // --- 4-STAGE REFLOW PROFILES (0 - 1000, 250 PER STAGE) ---
  if (is_error_state()) {
    if (g_reflow_stage != STAGE_IDLE) {
      log_println("[Profile] Reflow aborted due to thermal safety error! Returning to IDLE.");
    }
    g_reflow_stage = STAGE_IDLE;
    g_ui_progress = 0;
    return;
  }

  const ProfileStageConfig &cfg = g_profile_configs[(int)g_selected_profile];

  switch (g_reflow_stage) {
  case STAGE_IDLE:
    g_ui_progress = 0;
    break;

  case STAGE_PREHEAT: {
    // Stage 0: 0 to 250
    float span = (float)cfg.preheat_temp - g_stage_start_temp;
    float p =
        (span > 1.0f) ? ((current_temp - g_stage_start_temp) / span) : 1.0f;
    if (p < 0.0f)
      p = 0.0f;
    if (p > 1.0f)
      p = 1.0f;
    g_ui_progress = (int32_t)(p * 250.0f);

    if (current_temp >= (float)cfg.preheat_temp - 1.0f) {
      g_reflow_stage = STAGE_SOAK;
      g_stage_start_time = millis();
      g_stage_start_temp = current_temp;
      set_desired_temp(cfg.soak_temp);
      log_printf("[Profile] PREHEAT complete (%.1fC). Entering SOAK stage (Target: %dC, Duration: %lus)",
                 current_temp, cfg.soak_temp, (unsigned long)cfg.soak_time_s);
    }
    break;
  }

  case STAGE_SOAK: {
    // Stage 1: 250 to 500
    uint32_t elapsed_s = (millis() - g_stage_start_time) / 1000;
    float p = (cfg.soak_time_s > 0)
                  ? ((float)elapsed_s / (float)cfg.soak_time_s)
                  : 1.0f;
    if (p < 0.0f)
      p = 0.0f;
    if (p > 1.0f)
      p = 1.0f;
    g_ui_progress = 250 + (int32_t)(p * 250.0f);

    if (elapsed_s >= cfg.soak_time_s) {
      g_reflow_stage = STAGE_REFLOW;
      g_stage_start_time = millis();
      g_stage_start_temp = current_temp;
      g_peak_reached_temp = 0.0f;
      set_desired_temp(cfg.peak_temp);
      log_printf("[Profile] SOAK complete (%lus). Entering REFLOW stage (Peak Target: %dC)",
                 (unsigned long)cfg.soak_time_s, cfg.peak_temp);
    }
    break;
  }

  case STAGE_REFLOW: {
    // Stage 2: 500 to 750
    if (g_peak_reached_temp == 0.0f) {
      if (current_temp >= (float)cfg.peak_temp - 2.0f) {
        g_peak_reached_temp = current_temp;
        g_stage_start_time = millis();
        g_ui_progress = 675;
        log_printf("[Profile] REFLOW peak reached (%.1fC). Starting %lus dwell...",
                   current_temp, (unsigned long)cfg.peak_dwell_s);
      } else {
        float span = (float)cfg.peak_temp - g_stage_start_temp;
        float p =
            (span > 1.0f) ? ((current_temp - g_stage_start_temp) / span) : 1.0f;
        if (p < 0.0f)
          p = 0.0f;
        if (p > 1.0f)
          p = 1.0f;
        g_ui_progress = 500 + (int32_t)(p * 175.0f);
      }
    } else {
      uint32_t dwell_elapsed_s = (millis() - g_stage_start_time) / 1000;
      float p = (cfg.peak_dwell_s > 0)
                    ? ((float)dwell_elapsed_s / (float)cfg.peak_dwell_s)
                    : 1.0f;
      if (p < 0.0f)
        p = 0.0f;
      if (p > 1.0f)
        p = 1.0f;
      g_ui_progress = 675 + (int32_t)(p * 75.0f);

      if (dwell_elapsed_s >= cfg.peak_dwell_s) {
        set_heater(false);
        g_reflow_stage = STAGE_COOL;
        g_stage_start_time = millis();
        g_stage_start_temp = current_temp;
        set_desired_temp(cfg.cool_temp);
        log_printf("[Profile] REFLOW dwell complete. Heater OFF. Entering COOL stage (Target: %dC)",
                   cfg.cool_temp);
      }
    }
    break;
  }

  case STAGE_COOL: {
    // Stage 3: 750 to 1000
    float span = g_stage_start_temp - (float)cfg.cool_temp;
    float cooled = g_stage_start_temp - current_temp;
    float p = (span > 1.0f) ? (cooled / span) : 1.0f;
    if (p < 0.0f)
      p = 0.0f;
    if (p > 1.0f)
      p = 1.0f;
    g_ui_progress = 750 + (int32_t)(p * 250.0f);

    // When profile finishes all stages (progress reaches 100% / cooled to safe limit):
    // Heater turns off and returns to idle mode
    if (current_temp <= (float)cfg.cool_temp) {
      set_heater(false);
      g_reflow_stage = STAGE_IDLE;
      g_ui_progress = 0;
      if (objects.obj14) {
        lv_bar_set_value(objects.obj14, 0, LV_ANIM_OFF);
      }
      log_printf("[Profile] Cooled to safe temperature (%.1fC <= %dC). Reflow profile complete! System IDLE.",
                 current_temp, cfg.cool_temp);
    }
    break;
  }

  case STAGE_DONE:
    set_heater(false);
    g_reflow_stage = STAGE_IDLE;
    g_ui_progress = 0;
    break;
  }
}

void display_manager_init() {
  log_println("[Display] Initializing PicoDVI display & EEZ Studio LVGL UI "
              "(Portrait 240x400, 400x240 DVI @ 60Hz)...");

  // 1. Setup backlight pin (Active LOW)
  pinMode(PIN_BACKLIGHT, OUTPUT);
  digitalWrite(PIN_BACKLIGHT, LOW);

  // 2. Initialize PicoDVI hardware display
  if (!display.begin()) {
    log_println("[Display] ERROR: display.begin() failed!");
  } else {
    log_println("[Display] PicoDVI display initialized successfully.");
  }
  display.setRotation(
      DISPLAY_ROTATION); // 270° rotation for Portrait mode (240x400)

  // 3. Initialize LVGL core
  lv_init();

  // 4. Register Display Buffer & Driver with LVGL (240x400)
  lv_disp_draw_buf_init(&draw_buf, lvgl_buf, NULL,
                        SCREEN_WIDTH * LVGL_BUF_LINES);
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = SCREEN_WIDTH;
  disp_drv.ver_res = SCREEN_HEIGHT;
  disp_drv.flush_cb = dvi_flush_cb;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  // 5. Register Touch Controller with LVGL
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = touch_read_cb;
  lv_indev_drv_register(&indev_drv);

  // 6. Initialize EEZ Studio UI & load main screen
  ui_init();

  // Offset dropdown list by -65px horizontally for optimal alignment
  if (objects.obj12) {
    lv_obj_t *list = lv_dropdown_get_list(objects.obj12);
    if (list) {
      lv_obj_set_style_translate_x(list, -20, LV_PART_MAIN);
      lv_obj_set_style_translate_x(list, -20, (lv_style_selector_t)LV_PART_MAIN | LV_STATE_SCROLLED);

      lv_obj_set_style_translate_y(list, -16, LV_PART_MAIN);
      lv_obj_set_style_translate_y(list, -16, (lv_style_selector_t)LV_PART_MAIN | LV_STATE_SCROLLED);
    }
  }

  // Initialize progress bar range (0-100 for manual, 0-1000 for profiles)
  if (objects.obj14) {
    lv_bar_set_range(objects.obj14, 0,
                     (g_selected_profile == PROFILE_MANUAL) ? 100 : 1000);
    lv_bar_set_value(objects.obj14, 0, LV_ANIM_OFF);
  }

  // Initialize NTC status text color (objects.obj25 assigned to ntc_status)
  if (objects.obj25) {
    bool is_err = is_error_state() || (get_system_status() == STATUS_NTC_ERROR);
    uint32_t color_id = is_err ? COLOR_ID_COLOR_RED : COLOR_ID_COLOR_GREEN;
    lv_obj_set_style_text_color(
        objects.obj25, lv_color_hex(theme_colors[active_theme_index][color_id]),
        LV_PART_MAIN);
  }

  log_println("[Display] EEZ Studio UI initialized successfully.");
}

void display_manager_update(bool force_redraw) {
  (void)force_redraw;
#if defined(LV_TICK_CUSTOM) && (LV_TICK_CUSTOM == 0)
  static uint32_t last_tick = 0;
  uint32_t now = millis();
  if (last_tick == 0) {
    last_tick = now;
  }
  lv_tick_inc(now - last_tick);
  last_tick = now;
#endif

  update_profile_and_progress();
  ui_tick();
  lv_timer_handler();
}

// Static status string buffer for UI header
static char g_ui_status[32] = "IDLE";

// Active navigation tab index (0: Home, 1: Profiles, 2: Manual, 3: Info)
static int32_t g_selected_tab = 0;

/**
 * @brief Native variable getter for EEZ Studio UI status label.
 */
const char *get_var_status() {
  HeatbedStatus st = get_system_status();
  if (st == STATUS_NTC_ERROR) {
    return "ERROR";
  }
  if (g_selected_profile != PROFILE_MANUAL) {
    switch (g_reflow_stage) {
    case STAGE_PREHEAT:
      return "PREHEAT";
    case STAGE_SOAK:
      return "SOAK";
    case STAGE_REFLOW:
      return "REFLOW";
    case STAGE_COOL:
      return "COOLING";
    case STAGE_DONE:
      return "DONE";
    default:
      break;
    }
  }
  if (st == STATUS_HEATING) {
    return "HEATING";
  }
  return g_ui_status;
}

/**
 * @brief Native variable setter for EEZ Studio UI status label.
 */
void set_var_status(const char *value) {
  if (value) {
    strncpy(g_ui_status, value, sizeof(g_ui_status) - 1);
    g_ui_status[sizeof(g_ui_status) - 1] = '\0';
  }
}

/**
 * @brief Native variable getters and setters for navigation buttons checked
 * state.
 */
bool get_var_nav_home() { return g_selected_tab == 0; }
void set_var_nav_home(bool value) {
  if (value)
    g_selected_tab = 0;
}

bool get_var_nav_profiles() { return g_selected_tab == 1; }
void set_var_nav_profiles(bool value) {
  if (value)
    g_selected_tab = 1;
}

bool get_var_nav_manual() { return g_selected_tab == 2; }
void set_var_nav_manual(bool value) {
  if (value)
    g_selected_tab = 2;
}

bool get_var_nav_info() { return g_selected_tab == 3; }
void set_var_nav_info(bool value) {
  if (value)
    g_selected_tab = 3;
}

// Static target temperature string buffer for UI
static char g_ui_target_temp[32] = "0";

/**
 * @brief Native variable getter for EEZ Studio UI target temperature label.
 * Returns target temperature formatted as a string (e.g. "270").
 */
const char *get_var_target_temp_str() {
  int target = get_desired_temp();
  snprintf(g_ui_target_temp, sizeof(g_ui_target_temp), "%d", target);
  return g_ui_target_temp;
}

/**
 * @brief Native variable setter for EEZ Studio UI target temperature label.
 */
void set_var_target_temp_str(const char *value) {
  if (value) {
    strncpy(g_ui_target_temp, value, sizeof(g_ui_target_temp) - 1);
    g_ui_target_temp[sizeof(g_ui_target_temp) - 1] = '\0';
    int temp = atoi(value);
    if (temp > 0) {
      set_desired_temp(temp);
    }
  }
}

/**
 * @brief Native variable getter for EEZ Studio UI target temperature numeric
 * value.
 */
int32_t get_var_target_temp_val() { return (int32_t)get_desired_temp(); }

/**
 * @brief Native variable setter for EEZ Studio UI target temperature numeric
 * value.
 */
void set_var_target_temp_val(int32_t value) {
  if (value > 0) {
    set_desired_temp(value);
  }
}

// Static current temperature string buffer for UI
static char g_ui_current_temp[32] = "0";

/**
 * @brief Native variable getter for EEZ Studio UI current temperature label.
 * Returns measured temperature formatted as a string (e.g. "25").
 */
const char *get_var_current_temp_str() {
  float current = get_measured_temp();
  int temp_int = (int)(current >= 0 ? (current + 0.5f) : (current - 0.5f));
  snprintf(g_ui_current_temp, sizeof(g_ui_current_temp), "%d", temp_int);
  return g_ui_current_temp;
}

/**
 * @brief Native variable setter for EEZ Studio UI current temperature label.
 */
void set_var_current_temp_str(const char *value) {
  if (value) {
    strncpy(g_ui_current_temp, value, sizeof(g_ui_current_temp) - 1);
    g_ui_current_temp[sizeof(g_ui_current_temp) - 1] = '\0';
  }
}

/**
 * @brief Native variable getter for EEZ Studio UI current temperature numeric
 * value (Arc).
 */
int32_t get_var_current_temp_val() {
  float current = get_measured_temp();
  return (int32_t)(current >= 0 ? (current + 0.5f) : (current - 0.5f));
}

/**
 * @brief Native variable setter for EEZ Studio UI current temperature numeric
 * value.
 */
void set_var_current_temp_val(int32_t value) { (void)value; }

// Static buffers for UI telemetry and profile variables
static char g_ui_heater_state[16] = "STANDBY";
static char g_ui_heater_status[32] = "Heater is inactive";
static char g_ui_output_percentage[16] = "0%";
static char g_ui_profile[32] = "MANUAL";

/**
 * @brief Native variable getter for EEZ Studio UI heater state label ("ON" /
 * "OFF").
 */
const char *get_var_heater_state() {
  if (g_selected_profile != PROFILE_MANUAL) {
    if (g_reflow_stage == STAGE_COOL)
      return "COOLING";
    if (g_reflow_stage == STAGE_DONE)
      return "COMPLETE";
  }
  return is_heater_on() ? "HEATING" : "STANDBY";
}

/**
 * @brief Native variable setter for EEZ Studio UI heater state label.
 */
void set_var_heater_state(const char *value) {
  if (value) {
    strncpy(g_ui_heater_state, value, sizeof(g_ui_heater_state) - 1);
    g_ui_heater_state[sizeof(g_ui_heater_state) - 1] = '\0';
  }
}

/**
 * @brief Native variable getter for EEZ Studio UI heater status label.
 */
const char *get_var_heater_status() {
  HeatbedStatus st = get_system_status();
  if (st == STATUS_NTC_ERROR) {
    return "NTC error";
  }
  if (g_selected_profile != PROFILE_MANUAL) {
    switch (g_reflow_stage) {
    case STAGE_PREHEAT:
      return "Stage: Preheating";
    case STAGE_SOAK:
      return "Stage: Soaking flux";
    case STAGE_REFLOW:
      return "Stage: Reflow peak";
    case STAGE_COOL:
      return "Stage: Cooling down";
    case STAGE_DONE:
      return "Profile complete!";
    default:
      return "Profile at standby";
    }
  }
  if (st == STATUS_HEATING) {
    return "Heater is active";
  }
  return "Heater at standby";
}

/**
 * @brief Native variable setter for EEZ Studio UI heater status label.
 */
void set_var_heater_status(const char *value) {
  if (value) {
    strncpy(g_ui_heater_status, value, sizeof(g_ui_heater_status) - 1);
    g_ui_heater_status[sizeof(g_ui_heater_status) - 1] = '\0';
  }
}

/**
 * @brief Native variable getter for EEZ Studio UI output duty cycle percentage
 * label.
 */
const char *get_var_output_percentage_str() {
  float duty = get_duty_cycle();
  snprintf(g_ui_output_percentage, sizeof(g_ui_output_percentage), "%d%%",
           (int)(duty + 0.5f));
  return g_ui_output_percentage;
}

/**
 * @brief Native variable setter for EEZ Studio UI output duty cycle percentage
 * label.
 */
void set_var_output_percentage_str(const char *value) {
  if (value) {
    strncpy(g_ui_output_percentage, value, sizeof(g_ui_output_percentage) - 1);
    g_ui_output_percentage[sizeof(g_ui_output_percentage) - 1] = '\0';
  }
}

/**
 * @brief Native variable getter for EEZ Studio UI output duty cycle numeric
 * percentage.
 */
int32_t get_var_output_percentage_val() {
  return (int32_t)(get_duty_cycle() + 0.5f);
}

/**
 * @brief Native variable setter for EEZ Studio UI output duty cycle numeric
 * percentage.
 */
void set_var_output_percentage_val(int32_t value) { (void)value; }

/**
 * @brief Native variable getter for EEZ Studio UI profile string label.
 * Returns the active profile name string (e.g. "MANUAL", "LEAD FREE", "LEADED",
 * "LOW TEMP").
 */
const char *get_var_profile_str() {
  int idx = (int)g_selected_profile;
  if (idx >= 0 && idx < 4) {
    return g_profile_names[idx];
  }
  return "MANUAL";
}

/**
 * @brief Native variable setter for EEZ Studio UI profile string label.
 */
void set_var_profile_str(const char *value) {
  if (value) {
    for (int i = 0; i < 4; i++) {
      if (strcmp(value, g_profile_names[i]) == 0) {
        g_selected_profile = (ReflowProfile)i;
        g_reflow_stage = STAGE_IDLE;
        g_ui_progress = 0;
        if (objects.obj14) {
          lv_bar_set_range(objects.obj14, 0,
                           (g_selected_profile == PROFILE_MANUAL) ? 100 : 1000);
          lv_bar_set_value(objects.obj14, 0, LV_ANIM_OFF);
        }
        if (g_profile_temps[i] > 0) {
          set_desired_temp(g_profile_temps[i]);
        }
        return;
      }
    }
  }
}

/**
 * @brief Native variable getter for EEZ Studio UI profile dropdown selected
 * index.
 */
int32_t get_var_profile_index() { return (int32_t)g_selected_profile; }

/**
 * @brief Native variable setter for EEZ Studio UI profile dropdown selected
 * index.
 */
void set_var_profile_index(int32_t value) {
  if (value >= 0 && value < 4) {
    g_selected_profile = (ReflowProfile)value;
    g_reflow_stage = STAGE_IDLE;
    g_ui_progress = 0;
    if (objects.obj14) {
      lv_bar_set_range(objects.obj14, 0,
                       (g_selected_profile == PROFILE_MANUAL) ? 100 : 1000);
      lv_bar_set_value(objects.obj14, 0, LV_ANIM_OFF);
    }
    if (g_profile_temps[value] > 0) {
      set_desired_temp(g_profile_temps[value]);
    }
  }
}

/**
 * @brief Native variable getter for EEZ Studio UI progress bar.
 * 1. Manual profile: 0 - 100 progress for heating towards setpoint.
 * 2. Reflow profiles: 0 - 1000 divided into 4 stages of 250 each (PREHEAT,
 * SOAK, REFLOW, COOL).
 */
int32_t get_var_progress() { return g_ui_progress; }

/**
 * @brief Native variable setter for EEZ Studio UI progress bar.
 */
void set_var_progress(int32_t value) { g_ui_progress = value; }

/**
 * @brief Native variable getter for EEZ Studio UI stage_time label.
 * Returns counting profile's current stage time, "N/A" when manual, "IDLE" when IDLE.
 */
const char *get_var_stage_time() {
  if (g_selected_profile == PROFILE_MANUAL) {
    return "N/A";
  }
  if (g_reflow_stage == STAGE_IDLE) {
    return "IDLE";
  }
  uint32_t elapsed_s = (millis() - g_stage_start_time) / 1000;
  format_duration(g_ui_stage_time, sizeof(g_ui_stage_time), elapsed_s);
  return g_ui_stage_time;
}

/**
 * @brief Native variable setter for EEZ Studio UI stage_time label.
 */
void set_var_stage_time(const char *value) {
  if (value) {
    strncpy(g_ui_stage_time, value, sizeof(g_ui_stage_time) - 1);
    g_ui_stage_time[sizeof(g_ui_stage_time) - 1] = '\0';
  }
}

/**
 * @brief Native variable getter for EEZ Studio UI stage_target label.
 * Returns profile's target stage time, "N/A" when manual, "IDLE" when IDLE.
 */
const char *get_var_stage_target() {
  if (g_selected_profile == PROFILE_MANUAL) {
    return "N/A";
  }
  if (g_reflow_stage == STAGE_IDLE) {
    return "IDLE";
  }
  const ProfileStageConfig &cfg = g_profile_configs[(int)g_selected_profile];
  uint32_t target_s = 0;
  switch (g_reflow_stage) {
  case STAGE_PREHEAT:
    target_s = cfg.preheat_time_s;
    break;
  case STAGE_SOAK:
    target_s = cfg.soak_time_s;
    break;
  case STAGE_REFLOW:
    target_s = cfg.peak_dwell_s;
    break;
  case STAGE_COOL:
    target_s = cfg.cool_time_s;
    break;
  default:
    return "IDLE";
  }
  format_duration(g_ui_stage_target, sizeof(g_ui_stage_target), target_s);
  return g_ui_stage_target;
}

/**
 * @brief Native variable setter for EEZ Studio UI stage_target label.
 */
void set_var_stage_target(const char *value) {
  if (value) {
    strncpy(g_ui_stage_target, value, sizeof(g_ui_stage_target) - 1);
    g_ui_stage_target[sizeof(g_ui_stage_target) - 1] = '\0';
  }
}

/**
 * @brief Native variable getter for EEZ Studio UI profile_time label.
 * Returns total time spent on the profile, "IDLE" when IDLE.
 */
const char *get_var_profile_time() {
  if (g_selected_profile == PROFILE_MANUAL) {
    if (!is_heater_on()) {
      return "IDLE";
    }
    uint32_t elapsed_s = (millis() - g_profile_start_time) / 1000;
    format_duration(g_ui_profile_time, sizeof(g_ui_profile_time), elapsed_s);
    return g_ui_profile_time;
  }
  if (g_reflow_stage == STAGE_IDLE && !is_heater_on()) {
    return "IDLE";
  }
  uint32_t elapsed_s = (millis() - g_profile_start_time) / 1000;
  format_duration(g_ui_profile_time, sizeof(g_ui_profile_time), elapsed_s);
  return g_ui_profile_time;
}

/**
 * @brief Native variable setter for EEZ Studio UI profile_time label.
 */
void set_var_profile_time(const char *value) {
  if (value) {
    strncpy(g_ui_profile_time, value, sizeof(g_ui_profile_time) - 1);
    g_ui_profile_time[sizeof(g_ui_profile_time) - 1] = '\0';
  }
}

// Static buffer for UI uptime string
static char g_ui_uptime[32] = "00:00:00";

/**
 * @brief Native variable getter for EEZ Studio UI uptime label.
 * Returns system uptime formatted as "HH:MM:SS" (e.g. "01:23:45").
 */
const char *get_var_uptime() {
  uint32_t total_sec = millis() / 1000UL;
  uint32_t sec = total_sec % 60UL;
  uint32_t min = (total_sec / 60UL) % 60UL;
  uint32_t hr = total_sec / 3600UL;

  snprintf(g_ui_uptime, sizeof(g_ui_uptime), "%02lu:%02lu:%02lu",
           (unsigned long)hr, (unsigned long)min, (unsigned long)sec);
  return g_ui_uptime;
}

/**
 * @brief Native variable setter for EEZ Studio UI uptime label.
 */
void set_var_uptime(const char *value) {
  if (value) {
    strncpy(g_ui_uptime, value, sizeof(g_ui_uptime) - 1);
    g_ui_uptime[sizeof(g_ui_uptime) - 1] = '\0';
  }
}

// Static buffer for UI heating button label
static char g_ui_heating_button_str[32] = "\uf04d  START HEATING";

/**
 * @brief Native variable getter for EEZ Studio UI heating button label.
 * Returns "STOP HEATING" if heater is ON or in cooling stage, otherwise "START
 * HEATING".
 */
const char *get_var_heating_button_str() {
  bool active = is_heater_on() || (g_selected_profile != PROFILE_MANUAL &&
                                   g_reflow_stage == STAGE_COOL);
  if (active) {
    strncpy(g_ui_heating_button_str, "\uf04d  STOP HEATING",
            sizeof(g_ui_heating_button_str) - 1);
  } else {
    strncpy(g_ui_heating_button_str, "\uf04b  START HEATING",
            sizeof(g_ui_heating_button_str) - 1);
  }
  g_ui_heating_button_str[sizeof(g_ui_heating_button_str) - 1] = '\0';
  return g_ui_heating_button_str;
}

/**
 * @brief Native variable setter for EEZ Studio UI heating button label.
 */
void set_var_heating_button_str(const char *value) {
  if (value) {
    strncpy(g_ui_heating_button_str, value,
            sizeof(g_ui_heating_button_str) - 1);
    g_ui_heating_button_str[sizeof(g_ui_heating_button_str) - 1] = '\0';
  }
}

// Static buffer for UI NTC status
static char g_ui_ntc_status[16] = "OK";

/**
 * @brief Native variable getter for EEZ Studio UI NTC status label.
 * Returns "OK" if NTC sensor is normal, "ERROR" if faulty or disconnected.
 * Also dynamically sets text color: COLOR_RED on error, COLOR_GREEN when OK.
 */
const char *get_var_ntc_status() {
  bool is_err = is_error_state() || (get_system_status() == STATUS_NTC_ERROR);
  if (is_err) {
    strncpy(g_ui_ntc_status, "ERROR", sizeof(g_ui_ntc_status) - 1);
  } else {
    strncpy(g_ui_ntc_status, "OK", sizeof(g_ui_ntc_status) - 1);
  }
  g_ui_ntc_status[sizeof(g_ui_ntc_status) - 1] = '\0';

  // Update text color of the ntc_status label (objects.obj25): COLOR_RED on
  // error, COLOR_GREEN when OK
  if (objects.obj25) {
    if (is_err) {
      lv_obj_set_style_text_color(
          objects.obj25,
          lv_color_hex(theme_colors[active_theme_index][COLOR_ID_COLOR_RED]),
          LV_PART_MAIN);
    } else {
      lv_obj_set_style_text_color(
          objects.obj25,
          lv_color_hex(theme_colors[active_theme_index][COLOR_ID_COLOR_GREEN]),
          LV_PART_MAIN);
    }
  }

  return g_ui_ntc_status;
}

/**
 * @brief Native variable setter for EEZ Studio UI NTC status label.
 */
void set_var_ntc_status(const char *value) {
  if (value) {
    strncpy(g_ui_ntc_status, value, sizeof(g_ui_ntc_status) - 1);
    g_ui_ntc_status[sizeof(g_ui_ntc_status) - 1] = '\0';
  }
}

// Static buffers for UI system info variables
static char g_ui_controller[32] = "RP2040";
static char g_ui_build[32] = "";

/**
 * @brief Helper to convert compile month string ("Jan".."Dec") to MM string
 * ("01".."12").
 */
static const char *get_build_month() {
  const char *date = __DATE__;
  if (strncmp(date, "Jan", 3) == 0)
    return "01";
  if (strncmp(date, "Feb", 3) == 0)
    return "02";
  if (strncmp(date, "Mar", 3) == 0)
    return "03";
  if (strncmp(date, "Apr", 3) == 0)
    return "04";
  if (strncmp(date, "May", 3) == 0)
    return "05";
  if (strncmp(date, "Jun", 3) == 0)
    return "06";
  if (strncmp(date, "Jul", 3) == 0)
    return "07";
  if (strncmp(date, "Aug", 3) == 0)
    return "08";
  if (strncmp(date, "Sep", 3) == 0)
    return "09";
  if (strncmp(date, "Oct", 3) == 0)
    return "10";
  if (strncmp(date, "Nov", 3) == 0)
    return "11";
  if (strncmp(date, "Dec", 3) == 0)
    return "12";
  return "01";
}

/**
 * @brief Native variable getter for EEZ Studio UI controller name label.
 * Returns the MCU / controller architecture string (e.g. "RP2040").
 */
const char *get_var_controller() {
#if defined(ARDUINO_BOARD)
  strncpy(g_ui_controller, ARDUINO_BOARD, sizeof(g_ui_controller) - 1);
#elif defined(PICO_BOARD)
  strncpy(g_ui_controller, PICO_BOARD, sizeof(g_ui_controller) - 1);
#else
  strncpy(g_ui_controller, "RP2040", sizeof(g_ui_controller) - 1);
#endif
  g_ui_controller[sizeof(g_ui_controller) - 1] = '\0';
  return g_ui_controller;
}

/**
 * @brief Native variable setter for EEZ Studio UI controller name label.
 */
void set_var_controller(const char *value) {
  if (value) {
    strncpy(g_ui_controller, value, sizeof(g_ui_controller) - 1);
    g_ui_controller[sizeof(g_ui_controller) - 1] = '\0';
  }
}

/**
 * @brief Native variable getter for EEZ Studio UI build info label.
 * Returns formatted version and build date as "v1.0.1 (MM/YYYY)".
 */
const char *get_var_build() {
  if (g_ui_build[0] == '\0') {
    const char *month = get_build_month();
    const char *year = &__DATE__[7];
    snprintf(g_ui_build, sizeof(g_ui_build), "%s (%s/%s)", FIRMWARE_VERSION, month, year);
  }
  return g_ui_build;
}

/**
 * @brief Native variable setter for EEZ Studio UI build info label.
 */
void set_var_build(const char *value) {
  if (value) {
    strncpy(g_ui_build, value, sizeof(g_ui_build) - 1);
    g_ui_build[sizeof(g_ui_build) - 1] = '\0';
  }
}

// Static buffer for UI heater icon string
static char g_ui_heater_icon[16] = "\uf251";

/**
 * @brief Native variable getter for EEZ Studio UI heater icon.
 * Returns "\uf3b1" when heater is active, otherwise "\uf251".
 */
const char *get_var_heater_icon() {
  bool active = is_heater_on() || (g_selected_profile != PROFILE_MANUAL &&
                                   g_reflow_stage == STAGE_COOL);
  if (active) {
    strncpy(g_ui_heater_icon, "\uf3b1", sizeof(g_ui_heater_icon) - 1);
  } else {
    strncpy(g_ui_heater_icon, "\uf251", sizeof(g_ui_heater_icon) - 1);
  }
  g_ui_heater_icon[sizeof(g_ui_heater_icon) - 1] = '\0';
  return g_ui_heater_icon;
}

/**
 * @brief Native variable setter for EEZ Studio UI heater icon.
 */
void set_var_heater_icon(const char *value) {
  if (value) {
    strncpy(g_ui_heater_icon, value, sizeof(g_ui_heater_icon) - 1);
    g_ui_heater_icon[sizeof(g_ui_heater_icon) - 1] = '\0';
  }
}

/**
 * @brief UI heater button click handler.
 * Safely handles stopping during cooling/done stage or toggling heater state.
 */
extern "C" void handle_ui_toggle_heating() {
  if (g_selected_profile != PROFILE_MANUAL &&
      (g_reflow_stage == STAGE_COOL || g_reflow_stage == STAGE_DONE)) {
    g_reflow_stage = STAGE_IDLE;
    g_ui_progress = 0;
    set_heater(false);
    return;
  }
  toggle_heater();
}

/**
 * @brief UI profile cycle action handler.
 * Stops heating first, then cycles to the next profile (MANUAL -> LEAD FREE -> LEADED -> LOW TEMP).
 */
extern "C" void handle_ui_cycle_profile() {
  // 1. Stop heating first if currently active or in reflow/cooling stage
  if (is_heater_on() || g_reflow_stage != STAGE_IDLE) {
    set_heater(false);
    g_reflow_stage = STAGE_IDLE;
    g_ui_progress = 0;
  }

  // 2. Cycle to the next profile
  int next_profile = ((int)g_selected_profile + 1) % 4;
  set_var_profile_index(next_profile);

  log_printf("[Profile] Cycled to: %s", g_profile_names[next_profile]);
}

