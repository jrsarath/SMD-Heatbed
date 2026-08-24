#ifndef TELEMETRY_H_
#define TELEMETRY_H_

#include "config.h"
#include "thermal_control.h"
#include <Arduino.h>

/**
 * @brief Initializes Serial1 UART for telemetry output at SERIAL_BAUD (115200
 * baud).
 */
void telemetry_init();

/**
 * @brief Periodically logs telemetry data to Serial1 UART.
 */
void telemetry_update();

#endif // TELEMETRY_H_
