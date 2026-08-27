#ifndef THERMAL_CONTROL_H_
#define THERMAL_CONTROL_H_

#include <Arduino.h>
#include "config.h"
#include "RP2040_PWM.h"
#include "RPi_Pico_TimerInterrupt.h"

enum HeatbedStatus {
  STATUS_IDLE = 0,
  STATUS_HEATING = 1,
  STATUS_NTC_ERROR = 2
};

/**
 * @brief Initializes thermal control hardware, pins, ADC, and PWM.
 */
void thermal_control_init();

/**
 * @brief ISR callback for PI thermal regulation (called by hardware timer).
 */
bool regulator_isr(struct repeating_timer *t);

/**
 * @brief Measures temperature from the NTC thermistor ADC.
 * @return Temperature in degrees Celsius.
 */
float measure_temperature();

/**
 * @brief Sets the target temperature setpoint.
 * @param temp Desired temperature in °C (clamped to MIN_TEMP .. MAX_TEMP).
 */
void set_desired_temp(int temp);

/**
 * @brief Adjusts target temperature setpoint by a relative delta.
 * @param delta Adjustment amount in °C.
 */
void change_desired_temp(int delta);

/**
 * @brief Toggles heater state (ON / OFF).
 */
void toggle_heater();

/**
 * @brief Sets heater state directly.
 * @param state true to turn ON, false to turn OFF.
 */
void set_heater(bool state);

/**
 * @brief Gets current measured temperature.
 */
float get_measured_temp();

/**
 * @brief Gets raw 12-bit ADC reading from NTC thermistor pin.
 */
int get_raw_adc();

/**
 * @brief Gets calculated thermistor resistance in Ohms.
 */
float get_measured_resistance();

/**
 * @brief Gets current target temperature setpoint.
 */
int get_desired_temp();

/**
 * @brief Gets current reference temperature (soft-start ramp).
 */
float get_reference_temp();

/**
 * @brief Gets current PWM duty cycle (0.0 .. 100.0 %).
 */
float get_duty_cycle();

/**
 * @brief Checks if heater is currently active.
 */
bool is_heater_on();

/**
 * @brief Checks if thermal safety error state is active.
 */
bool is_error_state();

/**
 * @brief Gets the current high-level status of the heatbed.
 */
HeatbedStatus get_system_status();

#endif // THERMAL_CONTROL_H_
