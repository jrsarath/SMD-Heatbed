#include "display_manager.h"
#include "lvgl_ui/lvgl_ui.h"
#include "touch.h"

// Hardware DVI Display Instance
static DVIGFX16 display(DVI_RES_320x240p60, picodvi_dvi_cfg);

// LVGL Display Buffer (8 lines partial buffer = 320 * 8 * 2 = 5120 bytes)
#define LVGL_BUF_LINES 8
static uint16_t lvgl_buf[SCREEN_WIDTH * LVGL_BUF_LINES];

static lv_display_t *lv_disp = NULL;
static lv_indev_t *lv_indev_touch = NULL;
static uint32_t flush_count = 0;

/**
 * @brief Custom LVGL UART log callback for serial diagnostics.
 */
static void my_lv_log_cb(lv_log_level_t level, const char *buf) {
  (void)level;
  Serial1.print("[LVGL ");
  Serial1.print(level);
  Serial1.print("] ");
  Serial1.println(buf);
  Serial1.flush();
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
  flush_count++;
  if (flush_count <= 35) {
    Serial1.print("[Display] dvi_flush_cb #");
    Serial1.print(flush_count);
    Serial1.print(" area: ");
    Serial1.print(area->x1);
    Serial1.print(",");
    Serial1.print(area->y1);
    Serial1.print(" to ");
    Serial1.print(area->x2);
    Serial1.print(",");
    Serial1.println(area->y2);
    Serial1.flush();
  }

  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
  uint16_t *fb = display.getBuffer();
  const uint16_t *src = (const uint16_t *)px_map;

  if (fb != NULL) {
    for (int32_t y = area->y1; y <= area->y2; y++) {
      uint16_t *dst = fb + y * SCREEN_WIDTH + area->x1;
      memcpy(dst, src, w * sizeof(uint16_t));
      src += w;
    }
  } else {
    display.drawRGBBitmap(area->x1, area->y1, (const uint16_t *)px_map, w, h);
  }

  lv_display_flush_ready(disp);
}

/**
 * @brief LVGL touch input device read callback bridging hardware touch
 * controller.
 */
static void touch_read_cb(lv_indev_t *indev, lv_indev_data_t *data) {
  if (touch_has_signal() && touch_touched()) {
    data->point.x = touch_last_x;
    data->point.y = touch_last_y;
    data->state = LV_INDEV_STATE_PRESSED;
  } else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

void display_manager_init() {
  Serial1.println("[Display] Initializing backlight & PicoDVI hardware...");
  Serial1.flush();

  // 1. Setup backlight pin (Active LOW)
  pinMode(PIN_BACKLIGHT, OUTPUT);
  digitalWrite(PIN_BACKLIGHT, LOW);

  // 2. Log Free RAM
  Serial1.print("[Display] Free Heap before DVI init: ");
  Serial1.print(rp2040.getFreeHeap());
  Serial1.println(" bytes");
  Serial1.flush();

  // 3. Initialize PicoDVI hardware display
  Serial1.println("[Display] Calling display.begin()...");
  Serial1.flush();

  bool dvi_ok = display.begin();

  Serial1.print("[Display] display.begin() result: ");
  Serial1.println(dvi_ok ? "SUCCESS" : "FAILED");
  Serial1.flush();

  display.setRotation(0);

  Serial1.println(
      "[Display] Initializing LVGL core & registering log callback...");
  Serial1.flush();

  // 4. Initialize LVGL core & register native log print callback
  lv_init();
#if LV_USE_LOG
  lv_log_register_print_cb(my_lv_log_cb);
#endif
  lv_tick_set_cb(my_tick_cb);

  // 5. Register Display Driver with LVGL
  Serial1.println("[Display] Registering display driver with LVGL...");
  Serial1.flush();
  lv_disp = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);
  lv_display_set_color_format(lv_disp, LV_COLOR_FORMAT_RGB565);
  lv_display_set_buffers(lv_disp, lvgl_buf, NULL, sizeof(lvgl_buf),
                         LV_DISPLAY_RENDER_MODE_PARTIAL);
  lv_display_set_flush_cb(lv_disp, dvi_flush_cb);

  // 6. Register Touch Controller with LVGL
  Serial1.println("[Display] Registering touch indev with LVGL...");
  Serial1.flush();
  lv_indev_touch = lv_indev_create();
  lv_indev_set_type(lv_indev_touch, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(lv_indev_touch, touch_read_cb);

  Serial1.println("[Display] Initializing LVGL Pro project (lvgl_ui)...");
  Serial1.flush();

  // 7. Initialize LVGL Pro project & load home screen
  lvgl_ui_init("");
  Serial1.println("[Display] lvgl_ui_init done. Loading home screen...");
  Serial1.flush();

  lv_obj_t * home_scr = home_create();
  lv_screen_load(home_scr);
  lv_obj_invalidate(lv_screen_active());

  Serial1.println("[Display] LVGL Pro UI registered & loaded successfully.");
  Serial1.flush();
}


void display_manager_update(bool force_redraw) {
  (void)force_redraw;
  lv_timer_handler();
}
