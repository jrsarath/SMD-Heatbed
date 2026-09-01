#ifndef CONFIG_H_
#define CONFIG_H_

#include <Arduino.h>

/*******************************************************************************
 * Hardware Pinout Configuration
 ******************************************************************************/
#define PIN_ENA 2        // Rotary Encoder Phase A (GPIO 2)
#define PIN_ENB 3        // Rotary Encoder Phase B (GPIO 3)
#define PIN_EBT 28       // Rotary Encoder Push-Button (GPIO 28)
#define PIN_SSR 22       // Solid State Relay PWM Output (GPIO 22)
#define PIN_NTC1 26      // Primary NTC Thermistor ADC Input (ADC2, GPIO 26)
#define PIN_NTC2 27      // Secondary NTC Thermistor ADC Input (ADC0, GPIO 27)
#define PIN_NTC PIN_NTC1 // Backward compatibility alias
#define PIN_BACKLIGHT 24 // Display Backlight Control (Active LOW, GPIO 24)

#define SERIAL_TX 0 // Telemetry UART TX (GPIO 0)
#define SERIAL_RX 1 // Telemetry UART RX (GPIO 1)
#define SERIAL_BAUD 115200

/*******************************************************************************
 * Display Specifications (Elecrow CrowPanel RTD2281 4.3" DVI Display)
 * Hardware DVI Resolution: 400x240 @ 60Hz (scaled 2x to 800x480 by RTD2281)
 * Logical UI Resolution: 240x400 (Portrait Mode, 270° hardware rotation)
 ******************************************************************************/
#define SCREEN_WIDTH 240  // Logical UI horizontal resolution (pixels, portrait)
#define SCREEN_HEIGHT 400 // Logical UI vertical resolution (pixels, portrait)
#define DISPLAY_WIDTH                                                          \
  400 // Hardware DVI horizontal resolution (pixels, landscape)
#define DISPLAY_HEIGHT                                                         \
  240 // Hardware DVI vertical resolution (pixels, landscape)
#define DISPLAY_ROTATION 3 // Display Rotation 90 * 3 = 270° (Portrait)

/*******************************************************************************
 * Temperature & Controller Parameters
 ******************************************************************************/
#define MIN_TEMP 0   // Minimum allowable setpoint (°C)
#define MAX_TEMP 270 // Maximum allowable setpoint (°C)
#define CONTROL_PERIOD_MS                                                      \
  100 // Thermal control loop update interval (ms, 10 Hz)
#define RAMP_RATE_DEG_PER_SEC                                                  \
  1.5f                 // Soft-start reference ramping rate (°C/second)
#define REF_STEP 0.05f // Backward compatibility alias

// Dual NTC Voltage Divider Specifications
#define R_DIVIDER 100000.0f // Series divider resistor value (100k Ohms)
#define R0_THERMISTOR                                                          \
  100000.0f                // Thermistor nominal resistance at T0 (100k Ohms)
#define BETA_COEFF 3950.0f // Thermistor Beta coefficient (K)
#define T0_KELVIN 298.15f  // Nominal reference temperature (25°C in Kelvin)
#define MATH_E 2.71828f    // Euler's constant

// Dual NTC Sensor Safety Bounds
#define NTC_MIN_VALID_TEMP                                                     \
  -20.0f // Minimum physically valid sensor reading (°C)
#define NTC_MAX_VALID_TEMP                                                     \
  300.0f // Maximum physically valid sensor reading (°C)
#define MAX_NTC_DIFF                                                           \
  35.0f // Max allowable temp delta between NTCs during heating (°C)
#define OVERTEMP_SHUTDOWN                                                      \
  280.0f // Absolute emergency thermal shutdown limit (°C)

// PI Controller Constants (Calibrated for seconds-based delta-time integration)
#define KP_GAIN 1.5f  // Proportional gain
#define KI_GAIN 0.02f // Integral gain

// SSR Actuation & Duty Cycle Limits
#define SSR_TIME_PROPORTIONING                                                 \
  1 // 1: Time-proportioning (Slow PWM for AC mains SSR), 0: Hardware PWM
#define SSR_WINDOW_MS                                                          \
  1000 // Time-proportioning cycle window in milliseconds (1 second)
#define PWM_FREQUENCY                                                          \
  1000 // Hardware PWM Frequency in Hz (used if SSR_TIME_PROPORTIONING is 0)
#define MIN_DUTY 0.0f // Minimum duty cycle (%)
#define MAX_DUTY                                                               \
  40.0f // Maximum duty cycle (%) — Safety clamped to protect mains SSR

/*******************************************************************************
 * Timing & Safety Parameters
 ******************************************************************************/
#define BTN_SHORT_PRESS 100 // Minimum duration for short press (ms)
#define BTN_LONG_PRESS 1000 // Minimum duration for long press (ms)

#define SAFETY_PERIOD 18000 // Thermal runaway check interval (ms)
#define SAFETY_THRESHOLD                                                       \
  2.0f // Minimum temperature rise required over safety period (°C)

#define TELEMETRY_PERIOD 1000 // Telemetry output update interval (ms)

#endif // CONFIG_H_
