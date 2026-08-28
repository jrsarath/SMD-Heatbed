/*******************************************************************************
 * Tejasvini Firmware
 * Open-Source Heatplate Controller for SMT Reflow Soldering
 *
 * Board:   Raspberry Pi Pico (RP2040)
 * Display: Elecrow CrowPanel RTD2281 4.3" Pico DVI Display (400x240 / 800x480
 * Scaled) Sensor:  100K NTC Thermistor (ADC2, GPIO 28) Output:  3.3V Logic
 * Solid State Relay PWM (GPIO 22) Input:   Rotary Encoder with Push-Button &
 * Touchscreen (GT911)
 ******************************************************************************/

#include "src/config.h"
#include "src/display_manager.h"
#include "src/input_handler.h"
#include "src/telemetry.h"
#include "src/thermal_control.h"
#include "src/touch.h"
#include <lvgl.h>

// Hardware Timers
static RPI_PICO_Timer TimerRegulator(0);
static RPI_PICO_Timer TimerAcquisition(1);

/**
 * @brief Main setup function
 */
void setup() {
  // 1. Initialize Telemetry UART (Serial1 @ 115200 baud)
  telemetry_init();

  // 2. Initialize Thermal Control & Input (Commented out for isolation)
  thermal_control_init();
  input_init();

  // 3. Initialize PicoDVI Display & Touch Subsystems
  touch_init();
  display_manager_init();

  // 4. Attach Hardware Timer ISR Handlers (Temporarily commented for stack
  // collision testing)
  /*
  if (!TimerRegulator.attachInterruptInterval(2000, regulator_isr)) {
    Serial1.println("ERROR: Failed to attach Regulator Timer ISR!");
  }

  if (!TimerAcquisition.attachInterruptInterval(200, acquisition_isr)) {
    Serial1.println("ERROR: Failed to attach Acquisition Timer ISR!");
  }
  */

  Serial1.println("Setup completed successfully.");
}

/**
 * @brief Main execution loop
 */
void loop() {
  // Read inputs (rotary encoder & push-button)
  input_handler_update();

  // Update DVI Display Dashboard & LVGL UI tasks
  display_manager_update();

  // Log Telemetry Data to Serial Output
  telemetry_update();

  delay(5);
}
