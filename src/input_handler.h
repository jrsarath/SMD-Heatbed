#ifndef INPUT_HANDLER_H_
#define INPUT_HANDLER_H_

#include <Arduino.h>
#include "config.h"
#include "thermal_control.h"
#include "RPi_Pico_TimerInterrupt.h"

/**
 * @brief Initializes rotary encoder GPIO pins with internal pullup resistors.
 */
void input_init();

/**
 * @brief Polling update for rotary encoder and debounced push-button.
 * Called continuously from loop().
 */
void input_handler_update();

/**
 * @brief Timer ISR compatibility callback for reading inputs.
 */
bool acquisition_isr(struct repeating_timer *t);

/**
 * @brief Gets current encoder setpoint value.
 */
int get_encoder_count();

/**
 * @brief Sets raw encoder count / desired temperature setpoint.
 */
void set_encoder_count(int count);

#endif // INPUT_HANDLER_H_
