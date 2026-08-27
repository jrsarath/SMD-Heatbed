#include "display_manager.h"
#include "touch.h"
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

// UI Demo Widgets
static lv_obj_t *lbl_slider_val = NULL;
static lv_obj_t *lbl_btn_cnt = NULL;
static lv_obj_t *lbl_touch_info = NULL;
static lv_obj_t *lbl_uptime = NULL;
static lv_obj_t *demo_arc = NULL;
static uint32_t btn_click_count = 0;

static void slider_event_cb(lv_event_t *e) {
  lv_obj_t *slider = lv_event_get_target(e);
  int32_t val = lv_slider_get_value(slider);
  if (lbl_slider_val) {
    lv_label_set_text_fmt(lbl_slider_val, "Setpoint: %d °C", (int)val);
  }
  if (demo_arc) {
    lv_arc_set_value(demo_arc, val);
  }
}

static void btn_event_cb(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    btn_click_count++;
    if (lbl_btn_cnt) {
      lv_label_set_text_fmt(lbl_btn_cnt, "Clicks: %d", (int)btn_click_count);
    }
  }
}

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

      if (lbl_touch_info) {
        lv_label_set_text_fmt(lbl_touch_info, "Touch: X=%d Y=%d", touch_last_x,
                              touch_last_y);
      }

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

static void create_test_ui() {
  lv_obj_t *scr = lv_scr_act();
  lv_obj_set_style_bg_color(scr, lv_color_hex(0x0E131A), 0);

  // 1. Header Container
  lv_obj_t *header = lv_obj_create(scr);
  lv_obj_set_size(header, 220, 48);
  lv_obj_align(header, LV_ALIGN_TOP_MID, 0, 8);
  lv_obj_set_style_bg_color(header, lv_color_hex(0x18202C), 0);
  lv_obj_set_style_border_color(header, lv_color_hex(0x00E5FF), 0);
  lv_obj_set_style_border_width(header, 1, 0);
  lv_obj_set_style_radius(header, 6, 0);
  lv_obj_set_style_pad_all(header, 4, 0);

  lv_obj_t *title = lv_label_create(header);
  lv_label_set_text(title, "TEJASVINI");
  lv_obj_set_style_text_color(title, lv_color_hex(0x00E5FF), 0);
  lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 0);

  lv_obj_t *subtitle = lv_label_create(header);
  lv_label_set_text(subtitle, "240x400 Test UI");
  lv_obj_set_style_text_color(subtitle, lv_color_hex(0x8A99AD), 0);
  lv_obj_align(subtitle, LV_ALIGN_BOTTOM_MID, 0, 0);

  // 2. Arc Gauge (Temperature / Setpoint display)
  demo_arc = lv_arc_create(scr);
  lv_obj_set_size(demo_arc, 116, 116);
  lv_obj_align(demo_arc, LV_ALIGN_TOP_MID, 0, 64);
  lv_arc_set_range(demo_arc, 0, 250);
  lv_arc_set_value(demo_arc, 150);
  lv_obj_set_style_arc_color(demo_arc, lv_color_hex(0x222C3A), LV_PART_MAIN);
  lv_obj_set_style_arc_color(demo_arc, lv_color_hex(0xFF5722),
                             LV_PART_INDICATOR);
  lv_obj_set_style_arc_width(demo_arc, 8, LV_PART_MAIN);
  lv_obj_set_style_arc_width(demo_arc, 8, LV_PART_INDICATOR);

  lbl_slider_val = lv_label_create(scr);
  lv_label_set_text(lbl_slider_val, "Setpoint: 150 °C");
  lv_obj_set_style_text_color(lbl_slider_val, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(lbl_slider_val, LV_ALIGN_TOP_MID, 0, 184);

  // 3. Interactive Slider
  lv_obj_t *slider = lv_slider_create(scr);
  lv_obj_set_size(slider, 200, 16);
  lv_obj_align(slider, LV_ALIGN_TOP_MID, 0, 208);
  lv_slider_set_range(slider, 0, 250);
  lv_slider_set_value(slider, 150, LV_ANIM_OFF);
  lv_obj_set_style_bg_color(slider, lv_color_hex(0x222C3A), LV_PART_MAIN);
  lv_obj_set_style_bg_color(slider, lv_color_hex(0x00E5FF), LV_PART_INDICATOR);
  lv_obj_set_style_bg_color(slider, lv_color_hex(0xFFFFFF), LV_PART_KNOB);
  lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

  // 4. Interactive Button
  lv_obj_t *btn = lv_btn_create(scr);
  lv_obj_set_size(btn, 200, 42);
  lv_obj_align(btn, LV_ALIGN_TOP_MID, 0, 238);
  lv_obj_set_style_bg_color(btn, lv_color_hex(0x00B0FF), 0);
  lv_obj_set_style_radius(btn, 8, 0);
  lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, NULL);

  lbl_btn_cnt = lv_label_create(btn);
  lv_label_set_text(lbl_btn_cnt, "Touch Test: 0");
  lv_obj_set_style_text_color(lbl_btn_cnt, lv_color_hex(0xFFFFFF), 0);
  lv_obj_center(lbl_btn_cnt);

  // 5. Info & Touch Panel
  lv_obj_t *info_panel = lv_obj_create(scr);
  lv_obj_set_size(info_panel, 210, 95);
  lv_obj_align(info_panel, LV_ALIGN_BOTTOM_MID, 0, -10);
  lv_obj_set_style_bg_color(info_panel, lv_color_hex(0x141B24), 0);
  lv_obj_set_style_border_color(info_panel, lv_color_hex(0x283548), 0);
  lv_obj_set_style_border_width(info_panel, 1, 0);
  lv_obj_set_style_radius(info_panel, 6, 0);
  lv_obj_set_style_pad_all(info_panel, 6, 0);

  lbl_touch_info = lv_label_create(info_panel);
  lv_label_set_text(lbl_touch_info, "Touch: Untouched");
  lv_obj_set_style_text_color(lbl_touch_info, lv_color_hex(0x00FF88), 0);
  lv_obj_align(lbl_touch_info, LV_ALIGN_TOP_LEFT, 0, 0);

  lbl_uptime = lv_label_create(info_panel);
  lv_label_set_text(lbl_uptime, "Uptime: 0s");
  lv_obj_set_style_text_color(lbl_uptime, lv_color_hex(0xCCD6E0), 0);
  lv_obj_align(lbl_uptime, LV_ALIGN_TOP_LEFT, 0, 24);

  lv_obj_t *lbl_res = lv_label_create(info_panel);
  lv_label_set_text(lbl_res, "Res: 240x400 (400x240 DVI)");
  lv_obj_set_style_text_color(lbl_res, lv_color_hex(0x7A889B), 0);
  lv_obj_align(lbl_res, LV_ALIGN_TOP_LEFT, 0, 48);
}

void display_manager_init() {
  Serial.println("[Display] Initializing PicoDVI display & Test LVGL UI "
                 "(Portrait 240x400, 400x240 DVI @ 60Hz)...");
  Serial1.println("[Display] Initializing PicoDVI display & Test LVGL UI "
                  "(Portrait 240x400, 400x240 DVI @ 60Hz)...");

  // 1. Setup backlight pin (Active LOW)
  pinMode(PIN_BACKLIGHT, OUTPUT);
  digitalWrite(PIN_BACKLIGHT, LOW);

  // 2. Initialize PicoDVI hardware display
  if (!display.begin()) {
    Serial.println("[Display] ERROR: display.begin() failed!");
    Serial1.println("[Display] ERROR: display.begin() failed!");
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

  // 6. Build Test LVGL UI
  create_test_ui();

  Serial.println("[Display] Test LVGL 240x400 UI created successfully.");
  Serial1.println("[Display] Test LVGL 240x400 UI created successfully.");
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

  static uint32_t last_ui_update = 0;
  if (millis() - last_ui_update > 1000) {
    last_ui_update = millis();
    if (lbl_uptime) {
      lv_label_set_text_fmt(lbl_uptime, "Uptime: %lus",
                            (unsigned long)(millis() / 1000));
    }
  }

  lv_timer_handler();
}

// Static status string buffer for UI header
static char g_ui_status[32] = "IDLE";

// Active navigation tab index (0: Home, 1: Profiles, 2: Manual, 3: Info)
static int32_t g_selected_tab = 0;

/**
 * @brief Native variable getter for UI status label.
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
 * @brief Native variable setter for UI status label.
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
