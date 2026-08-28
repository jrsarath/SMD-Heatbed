#ifndef INPUT_HANDLER_H_
#define INPUT_HANDLER_H_

#include <Arduino.h>
#include "config.h"
#include "thermal_control.h"
#include "RPi_Pico_TimerInterrupt.h"

/**
 * @brief Initializes rotary encoder GPIO pins and pullup resistors.
 */
void input_init();

/**
 * @brief ISR callback for reading rotary encoder and debouncing push-button.
 */
bool acquisition_isr(struct repeating_timer *t);

/**
 * @brief Gets current raw encoder count.
 */
int get_encoder_count();

/**
 * @brief Sets raw encoder count value.
 */
/**
 * @brief Polling update for rotary encoder and button (called from main loop if timers are disabled).
 */
void input_handler_update();

#endif // INPUT_HANDLER_H_
