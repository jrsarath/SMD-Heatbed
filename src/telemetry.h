#ifndef TELEMETRY_H_
#define TELEMETRY_H_

#include "config.h"
#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes Serial (USB CDC) and Serial1 (Hardware UART) at
 * SERIAL_BAUD (115200 baud).
 */
void telemetry_init();

/**
 * @brief Periodically logs telemetry data to Serial & Serial1.
 */
void telemetry_update();

/**
 * @brief Prints the project ASCII art boot banner and metadata.
 */
void telemetry_print_banner();

/**
 * @brief Formats and logs a message to both USB Serial and Serial1 UART with
 * newline.
 */
void log_printf(const char *fmt, ...);

/**
 * @brief Logs a string message to both USB Serial and Serial1 UART with
 * newline.
 */
void log_println(const char *msg);

#ifdef __cplusplus
}
#endif

#endif // TELEMETRY_H_
