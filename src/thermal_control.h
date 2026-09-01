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
 * @brief Periodically updates thermal control loop, soft-start ramping, and SSR actuation.
 * Should be called continuously from loop().
 */
void thermal_control_update();

/**
 * @brief ISR callback for PI thermal regulation (backward-compatibility wrapper).
 */
bool regulator_isr(struct repeating_timer *t);

/**
 * @brief Measures temperatures from both NTC thermistor ADCs and updates control states.
 * @return Average/composite temperature in degrees Celsius.
 */
float measure_temperature();

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Clears safety error state if sensors are currently physically valid.
 */
void reset_error_state();

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
 * @brief Gets current measured composite/average temperature.
 */
float get_measured_temp();

/**
 * @brief Gets current temperature measured by primary NTC (NTC1).
 */
float get_measured_temp_ntc1();

/**
 * @brief Gets current temperature measured by secondary NTC (NTC2).
 */
float get_measured_temp_ntc2();

/**
 * @brief Gets absolute difference between NTC1 and NTC2 temperatures.
 */
float get_ntc_delta();

/**
 * @brief Gets current target temperature setpoint.
 */
int get_desired_temp();

/**
 * @brief Checks if heater is currently active.
 */
bool is_heater_on();

/**
 * @brief Checks if thermal safety error state is active.
 */
bool is_error_state();

#ifdef __cplusplus
}
#endif

/**
 * @brief Gets raw 12-bit ADC reading from primary NTC thermistor pin (PIN_NTC1).
 */
int get_raw_adc();

/**
 * @brief Gets raw 12-bit ADC reading from primary NTC thermistor pin (PIN_NTC1).
 */
int get_raw_adc_ntc1();

/**
 * @brief Gets raw 12-bit ADC reading from secondary NTC thermistor pin (PIN_NTC2).
 */
int get_raw_adc_ntc2();

/**
 * @brief Gets calculated primary thermistor resistance in Ohms.
 */
float get_measured_resistance();

/**
 * @brief Gets calculated primary thermistor resistance in Ohms (NTC1).
 */
float get_measured_resistance_ntc1();

/**
 * @brief Gets calculated secondary thermistor resistance in Ohms (NTC2).
 */
float get_measured_resistance_ntc2();

/**
 * @brief Gets current reference temperature (soft-start ramp).
 */
float get_reference_temp();

/**
 * @brief Gets current PWM duty cycle (0.0 .. 100.0 %).
 */
float get_duty_cycle();

/**
 * @brief Gets the current high-level status of the heatbed.
 */
HeatbedStatus get_system_status();

#endif // THERMAL_CONTROL_H_
