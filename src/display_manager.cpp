#include "display_manager.h"
#include "touch.h"

// Hardware DVI Display Instance
static DVIGFX16 display(DVI_RES_320x240p60, picodvi_dvi_cfg);

// LVGL Display Buffer (8 lines partial buffer = 320 * 8 * 2 = 5120 bytes)
#define LVGL_BUF_LINES 8
static uint16_t lvgl_buf[SCREEN_WIDTH * LVGL_BUF_LINES];

static lv_display_t *lv_disp = NULL;
static lv_indev_t *lv_indev_touch = NULL;

/**
 * @brief Custom LVGL UART log callback for serial diagnostics.
 */
static void my_lv_log_cb(lv_log_level_t level, const char *buf) {
  (void)level;
  Serial.print("[LVGL] ");
  Serial.println(buf);
  Serial1.print("[LVGL] ");
  Serial1.println(buf);
}

/**
 * @brief LVGL tick source callback returning system milliseconds.
 */
static uint32_t my_tick_cb(void) { return millis(); }

/**
 * @brief LVGL flush callback rendering drawn buffers to the PicoDVI
 * framebuffer.
 */
static void dvi_flush_cb(lv_display_t *disp, const lv_area_t *area,
                         uint8_t *px_map) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
  display.drawRGBBitmap(area->x1, area->y1, (const uint16_t *)px_map, w, h);
  lv_display_flush_ready(disp);
}

/**
 * @brief LVGL touch input device read callback bridging hardware touch
 * controller.
 */
static void touch_read_cb(lv_indev_t *indev, lv_indev_data_t *data) {
  if (touch_has_signal()) {
    if (touch_touched()) {
      data->state = LV_INDEV_STATE_PRESSED;
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;

      static uint32_t last_touch_log = 0;
      if (millis() - last_touch_log > 200) {
        last_touch_log = millis();
        String touchMsg = "[Touch] Press X: " + String(touch_last_x) +
                          " Y: " + String(touch_last_y) +
                          " | Free Heap: " + String(rp2040.getFreeHeap()) + " B";
        Serial.println(touchMsg);
        Serial1.println(touchMsg);
      }
    } else if (touch_released()) {
      data->state = LV_INDEV_STATE_RELEASED;
    }
  } else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

void display_manager_init() {
  Serial.println(
      "[Display] Initializing PicoDVI display & LVGL UI (Portrait 240x320)...");
  Serial1.println(
      "[Display] Initializing PicoDVI display & LVGL UI (Portrait 240x320)...");

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

  // 3. Initialize LVGL core & register log print callback
  lv_init();
#if LV_USE_LOG
  lv_log_register_print_cb(my_lv_log_cb);
#endif
  lv_tick_set_cb(my_tick_cb);

  // 4. Register Display Driver with LVGL (240x320)
  lv_disp = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);
  lv_display_set_color_format(lv_disp, LV_COLOR_FORMAT_RGB565);
  lv_display_set_buffers(lv_disp, lvgl_buf, NULL, sizeof(lvgl_buf),
                         LV_DISPLAY_RENDER_MODE_PARTIAL);
  lv_display_set_flush_cb(lv_disp, dvi_flush_cb);

  // 5. Register Touch Controller with LVGL
  lv_indev_touch = lv_indev_create();
  lv_indev_set_type(lv_indev_touch, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(lv_indev_touch, touch_read_cb);

  // 6. Initialize default active screen
  lv_obj_t *scr = lv_screen_active();
  lv_obj_set_style_bg_color(scr, lv_color_hex(0x0F131A), 0);
  lv_obj_invalidate(scr);

  Serial.println("[Display] LVGL UI initialized successfully.");
  Serial1.println("[Display] LVGL UI initialized successfully.");
  Serial.printf("[Display] Free Heap after LVGL Init: %lu bytes (Total Heap: %lu bytes)\n",
                rp2040.getFreeHeap(), rp2040.getTotalHeap());
  Serial1.printf("[Display] Free Heap after LVGL Init: %lu bytes (Total Heap: %lu bytes)\n",
                 rp2040.getFreeHeap(), rp2040.getTotalHeap());
}

void display_manager_update(bool force_redraw) {
  (void)force_redraw;
  lv_timer_handler();
}
