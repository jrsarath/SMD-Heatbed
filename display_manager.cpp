#include "display_manager.h"

// DVI Display Instance
static DVIGFX16 display(DVI_RES_320x240p60, picodvi_dvi_cfg);

// Color definitions (RGB 565 format)
#define COLOR_BG            0x0842 // Dark slate blue background
#define COLOR_HEADER_BG     0x18C3 // Header bar background
#define COLOR_CARD_BG       0x18E5 // Card background
#define COLOR_CARD_BORDER   0x31A6 // Card border line
#define COLOR_TEXT_MAIN     0xFFFF // White
#define COLOR_TEXT_SUB      0xBDF7 // Light grey
#define COLOR_CYAN          0x07FF // Cyan
#define COLOR_YELLOW        0xFFE0 // Yellow
#define COLOR_GREEN         0x07E0 // Bright Green
#define COLOR_ORANGE        0xFA20 // Orange / Heating
#define COLOR_RED           0xF800 // Bright Red / Error

static uint32_t last_display_update = 0;

static float last_meas_temp = -999.0f;
static int last_set_temp = -999;
static float last_duty = -1.0f;
static HeatbedStatus last_status = (HeatbedStatus)-1;

static void draw_static_ui() {
  display.fillScreen(COLOR_BG);

  // Header Bar
  display.fillRect(0, 0, SCREEN_WIDTH, 28, COLOR_HEADER_BG);
  display.drawFastHLine(0, 28, SCREEN_WIDTH, COLOR_CARD_BORDER);

  display.setTextSize(1);
  display.setTextColor(COLOR_TEXT_MAIN);
  display.setCursor(10, 10);
  display.print("SMD HEATBED CONTROLLER");

  display.setTextColor(COLOR_TEXT_SUB);
  display.setCursor(220, 10);
  display.print("RP2040 Pico");

  // Measured Temperature Card (Left)
  display.fillRoundRect(10, 36, 145, 110, 6, COLOR_CARD_BG);
  display.drawRoundRect(10, 36, 145, 110, 6, COLOR_CARD_BORDER);
  display.setCursor(20, 46);
  display.setTextColor(COLOR_TEXT_SUB);
  display.print("MEASURED TEMP");

  // Target Temperature Card (Right)
  display.fillRoundRect(165, 36, 145, 110, 6, COLOR_CARD_BG);
  display.drawRoundRect(165, 36, 145, 110, 6, COLOR_CARD_BORDER);
  display.setCursor(175, 46);
  display.setTextColor(COLOR_TEXT_SUB);
  display.print("TARGET SETPOINT");

  // Status & Duty Cycle Card (Bottom)
  display.fillRoundRect(10, 154, 300, 76, 6, COLOR_CARD_BG);
  display.drawRoundRect(10, 154, 300, 76, 6, COLOR_CARD_BORDER);
  display.setCursor(20, 164);
  display.setTextColor(COLOR_TEXT_SUB);
  display.print("HEATER STATUS");

  display.setCursor(180, 164);
  display.print("SSR DUTY CYCLE");
}

void display_manager_init() {
  // Setup backlight pin
  pinMode(PIN_BACKLIGHT, OUTPUT);
  digitalWrite(PIN_BACKLIGHT, LOW); // Active LOW to turn on display backlight

  display.begin();
  display.setRotation(0);
  draw_static_ui();
}

void display_manager_update(bool force_redraw) {
  uint32_t now = millis();
  if (!force_redraw && (now - last_display_update < DISPLAY_PERIOD)) {
    return;
  }
  last_display_update = now;

  if (force_redraw) {
    draw_static_ui();
    last_meas_temp = -999.0f;
    last_set_temp = -999;
    last_duty = -1.0f;
    last_status = (HeatbedStatus)-1;
  }

  float current_meas = get_measured_temp();
  int current_set = get_desired_temp();
  float current_duty = get_duty_cycle();
  HeatbedStatus current_status = get_system_status();

  // 1. Update Measured Temperature Display
  if (abs(current_meas - last_meas_temp) >= 0.1f || force_redraw) {
    last_meas_temp = current_meas;

    // Erase old value background
    display.fillRect(20, 70, 125, 45, COLOR_CARD_BG);

    display.setTextSize(3);
    if (current_status == STATUS_HEATING) {
      display.setTextColor(COLOR_ORANGE);
    } else if (current_status == STATUS_NTC_ERROR) {
      display.setTextColor(COLOR_RED);
    } else {
      display.setTextColor(COLOR_CYAN);
    }

    display.setCursor(20, 80);
    display.print((int)current_meas);
    display.setTextSize(2);
    display.print(" C");
  }

  // 2. Update Target Setpoint Display
  if (current_set != last_set_temp || force_redraw) {
    last_set_temp = current_set;

    // Erase old value background
    display.fillRect(175, 70, 125, 45, COLOR_CARD_BG);

    display.setTextSize(3);
    display.setTextColor(COLOR_YELLOW);
    display.setCursor(175, 80);
    display.print(current_set);
    display.setTextSize(2);
    display.print(" C");
  }

  // 3. Update Status Indicator
  if (current_status != last_status || force_redraw) {
    last_status = current_status;

    display.fillRect(20, 185, 140, 30, COLOR_CARD_BG);
    display.setTextSize(2);

    switch (current_status) {
      case STATUS_HEATING:
        display.setTextColor(COLOR_ORANGE);
        display.setCursor(20, 190);
        display.print("HEATING");
        break;
      case STATUS_NTC_ERROR:
        display.setTextColor(COLOR_RED);
        display.setCursor(20, 190);
        display.print("NTC ERROR");
        break;
      case STATUS_IDLE:
      default:
        display.setTextColor(COLOR_GREEN);
        display.setCursor(20, 190);
        display.print("IDLE");
        break;
    }
  }

  // 4. Update Duty Cycle Bar & Text
  if (abs(current_duty - last_duty) >= 0.5f || force_redraw) {
    last_duty = current_duty;

    display.fillRect(180, 185, 120, 35, COLOR_CARD_BG);

    // Duty text
    display.setTextSize(2);
    display.setTextColor(COLOR_TEXT_MAIN);
    display.setCursor(180, 185);
    display.print((int)current_duty);
    display.print("%");

    // Progress bar frame
    display.drawRect(180, 208, 120, 12, COLOR_CARD_BORDER);

    // Progress bar fill (0 .. MAX_DUTY mapped to 0 .. 118 px)
    int fill_width = map((int)current_duty, 0, (int)MAX_DUTY, 0, 116);
    if (fill_width > 116) fill_width = 116;
    if (fill_width < 0) fill_width = 0;

    display.fillRect(182, 210, fill_width, 8, COLOR_ORANGE);
    if (fill_width < 116) {
      display.fillRect(182 + fill_width, 210, 116 - fill_width, 8, COLOR_BG);
    }
  }
}
