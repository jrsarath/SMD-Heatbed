#include "display_manager.h"
#include "touch.h"

// Hardware DVI Display Instance
static DVIGFX16 display(DVI_RES_320x240p60, picodvi_dvi_cfg);

// LVGL Display Buffer (8 lines partial buffer = 320 * 8 * 2 = 5120 bytes)
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

      static uint32_t last_touch_log = 0;
      if (millis() - last_touch_log > 200) {
        last_touch_log = millis();
        String touchMsg = "[Touch] Press X: " + String(touch_last_x) +
                          " Y: " + String(touch_last_y);
        Serial.println(touchMsg);
        Serial1.println(touchMsg);
      }
    } else if (touch_released()) {
      data->state = LV_INDEV_STATE_REL;
    }
  } else {
    data->state = LV_INDEV_STATE_REL;
  }
}

void display_manager_init() {
  Serial.println("[Display] Initializing PicoDVI display & LVGL v8.4.0 UI "
                 "(Portrait 240x320)...");
  Serial1.println("[Display] Initializing PicoDVI display & LVGL v8.4.0 UI "
                  "(Portrait 240x320)...");

  // 1. Setup backlight pin (Active LOW)
  pinMode(PIN_BACKLIGHT, OUTPUT);
  digitalWrite(PIN_BACKLIGHT, LOW);

  // 2. Initialize PicoDVI hardware display
  if (!display.begin()) {
    Serial.println("[Display] ERROR: display.begin() failed!");
    Serial1.println("[Display] ERROR: display.begin() failed!");
  }
  display.setRotation(DISPLAY_ROTATION); // 270° rotation for Portrait mode
                                         // (240x320, right-side up)

  // 3. Initialize LVGL core
  lv_init();

  // 4. Register Display Buffer & Driver with LVGL (240x320)
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

  Serial.println("[Display] EEZ Studio UI initialized successfully.");
  Serial1.println("[Display] EEZ Studio UI initialized successfully.");
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
