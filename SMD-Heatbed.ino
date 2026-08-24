/*******************************************************************************
 * SMD Heatbed Firmware
 * Open-Source Heatplate Controller for SMT Reflow Soldering
 *
 * Board:   Raspberry Pi Pico (RP2040)
 * Display: Elecrow 4.3" Pico DVI Display (320x240)
 * Sensor:  100K NTC Thermistor (ADC2, GPIO 28)
 * Output:  3.3V Logic Solid State Relay PWM (GPIO 22)
 * Input:   Rotary Encoder with Push-Button & Touchscreen (GT911)
 ******************************************************************************/

#include "src/config.h"
#include "src/display_manager.h"
#include "src/input_handler.h"
#include "src/telemetry.h"
#include "src/thermal_control.h"
#include "src/touch.h"
#include "src/lvgl_ui/lvgl_ui.h"

// Hardware Timers
static RPI_PICO_Timer TimerRegulator(0);
static RPI_PICO_Timer TimerAcquisition(1);

/**
 * @brief Main setup function
 */
void setup() {
  // 1. Initialize Telemetry UART (Serial1 @ 115200 baud)
  telemetry_init();

  // 2. Initialize Thermal Control Hardware & Input Pins
  thermal_control_init();
  input_init();

  // 3. Initialize PicoDVI Display & Touch Subsystems
  display_manager_init();
  touch_init(SCREEN_WIDTH, SCREEN_HEIGHT);

  // 4. Attach Hardware Timer ISR Handlers
  // Regulator Loop: 500 Hz (2000 µs interval)
  if (!TimerRegulator.attachInterruptInterval(2000, regulator_isr)) {
    Serial1.println("ERROR: Failed to attach Regulator Timer ISR!");
  }

  // Acquisition Loop: 5000 Hz (200 µs interval)
  if (!TimerAcquisition.attachInterruptInterval(200, acquisition_isr)) {
    Serial1.println("ERROR: Failed to attach Acquisition Timer ISR!");
  }

  Serial1.println("Setup completed successfully.");

  // LVGL UI Initialization
  lvgl_ui_init("");
  lv_screen_load(home_create());
}

/**
 * @brief Main execution loop
 */
void loop() {
  // Update DVI Display Dashboard
  display_manager_update();

  // Log Telemetry Data to Serial Output
  telemetry_update();

  // Poll Touch Controller Signals
  if (touch_has_signal() && touch_touched()) {
    // Touch event recorded at touch_last_x, touch_last_y
  }

  delay(5);
}
