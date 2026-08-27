#ifndef CONFIG_H_
#define CONFIG_H_

#include <Arduino.h>

/*******************************************************************************
 * Hardware Pinout Configuration
 ******************************************************************************/
#define PIN_ENA 2        // Rotary Encoder Phase A (GPIO 2)
#define PIN_ENB 3        // Rotary Encoder Phase B (GPIO 3)
#define PIN_EBT 27       // Rotary Encoder Push-Button (GPIO 27)
#define PIN_SSR 22       // Solid State Relay PWM Output (GPIO 22)
#define PIN_NTC 28       // NTC Thermistor ADC Input (ADC2, GPIO 28)
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
 * Aspect Ratio Compensation
 * 400x240 matches 800x480 panel with 1:1 pixel aspect ratio (2x integer scale).
 * Set to 0 since no 4:3 anamorphic stretch compensation is needed.
 ******************************************************************************/
#define DISPLAY_ASPECT_COMPENSATION 0
#define DISPLAY_ASPECT_SCALE_NUM 1
#define DISPLAY_ASPECT_SCALE_DEN 1
#define DISPLAY_ASPECT_X_OFFSET 0

/*******************************************************************************
 * Temperature & Controller Parameters
 ******************************************************************************/
#define MIN_TEMP 0     // Minimum allowable setpoint (°C)
#define MAX_TEMP 250   // Maximum allowable setpoint (°C)
#define REF_STEP 0.05f // Soft-start reference ramping step per cycle (°C)

// NTC Voltage Divider Specifications
#define R_DIVIDER 2200.0f       // Series resistor value (Ohms)
#define R0_THERMISTOR 100000.0f // Thermistor nominal resistance at T0 (Ohms)
#define BETA_COEFF 3950.0f      // Thermistor Beta coefficient (K)
#define T0_KELVIN 298.15f // Nominal reference temperature (25°C in Kelvin)
#define MATH_E 2.71828f   // Euler's constant

// PI Controller Constants
#define KP_GAIN 0.2f     // Proportional gain
#define KI_GAIN 0.00001f // Integral gain

// PWM & Duty Cycle Limits
#define PWM_FREQUENCY 1000 // SSR PWM Frequency (Hz)
#define MIN_DUTY 0.0f      // Minimum duty cycle (%)
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
