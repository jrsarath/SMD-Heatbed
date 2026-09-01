/*******************************************************************************
 * Tejasvini Firmware
 * Open-Source Heatplate Controller for SMT Reflow Soldering
 *
 * Board:   Raspberry Pi Pico (RP2040)
 * Display: Elecrow CrowPanel RTD2281 4.3" Pico DVI Display (400x240 / 800x480 Scaled)
 * Sensors: Dual 100K NTC Thermistors (NTC1: ADC0/GPIO 26, NTC2: ADC1/GPIO 27)
 * Output:  Solid State Relay (GPIO 22, AC Zero-Cross Time Proportioning / PWM)
 * Input:   Rotary Encoder (GPIO 2, 3, 28) & Capacitive Touchscreen (GT911)
 * Telemetry: Serial (USB CDC) & Serial1 (GPIO 0 TX, GPIO 1 RX) @ 115200 baud
 ******************************************************************************/

#include "src/config.h"
#include "src/display_manager.h"
#include "src/input_handler.h"
#include "src/telemetry.h"
#include "src/thermal_control.h"
#include "src/touch.h"
#include <lvgl.h>

void setup() {
  // 1. Initialize Telemetry UART (Serial1 @ 115200 baud & USB CDC)
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
 * @brief Main execution loop (cooperative, non-blocking scheduling)
 */
void loop() {
  // 1. Poll inputs (rotary encoder quadrature decoding & debounced button)
  input_handler_update();

  // 2. Regulate heatplate thermal control & update SSR actuation
  thermal_control_update();

  // 3. Update DVI Display Dashboard & LVGL UI tasks
  display_manager_update();

  // 4. Log Telemetry Data to Serial Output
  telemetry_update();

  // Yield to allow background microcontroller housekeeping
  yield();
}
