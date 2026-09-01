/*******************************************************************************
 * Tejasvini Firmware
 * Open-Source Heatplate Controller for SMT Reflow Soldering
 *
 * Board:   Raspberry Pi Pico (RP2040)
 * Display: Elecrow CrowPanel RTD2281 4.3" Pico DVI Display (400x240 / 800x480
 * Scaled) Sensor:  Dual 100K NTC Thermistors (NTC1: ADC2/GPIO 28, NTC2:
 * ADC0/GPIO 26) with 100K Dividers Output:  3.3V Logic Solid State Relay PWM
 * (GPIO 22) Input:   Rotary Encoder with Push-Button & Touchscreen (GT911)
 ******************************************************************************/

#include "src/config.h"
#include "src/display_manager.h"
#include "src/input_handler.h"
#include "src/telemetry.h"
#include "src/thermal_control.h"
#include "src/touch.h"
#include <lvgl.h>

void setup() {
  // 1. Initialize Telemetry UART (Serial1 @ 115200 baud)
  telemetry_init();

  // 2. Initialize Thermal Control & Input Subsystems
  thermal_control_init();
  input_init();

  // 3. Initialize PicoDVI Display & Touch Subsystems
  touch_init();
  display_manager_init();

  log_println("[System] Setup completed successfully. Entering main execution loop.");
}

/**
 * @brief Main execution loop
 */
void loop() {
  // 1. Read inputs (rotary encoder & push-button)
  input_handler_update();

  // 2. Regulate heatplate thermal control & SSR actuation
  thermal_control_update();

  // 3. Update DVI Display Dashboard & LVGL UI tasks
  display_manager_update();

  // 4. Log Telemetry Data to Serial Output
  telemetry_update();

  delay(5);
}
