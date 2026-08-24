# AGENTS.md — Developer & AI Agent Guide for SMD-Heatbed

This document provides developer guidelines, architectural rules, hardware specifications, and codebase navigation for AI agents and human developers working on **SMD-Heatbed**.

---

## 1. Project Overview

**SMD-Heatbed** is an open-source heatplate controller designed for reflow and SMT soldering work. It runs on a **Raspberry Pi Pico (RP2040)** paired with an **Elecrow 4.3" Pico DVI Display** running a native DVI dashboard user interface.

### Key Hardware Specifications
* **MCU:** Raspberry Pi Pico (RP2040 microcontroller)
* **Heater Element:** 400W PTC Heatplate driven via a 3.3V Logic Solid State Relay (SSR)
* **Temperature Sensor:** 100K NTC Thermistor in a voltage divider ($R = 2.2\text{k}\Omega$, $R_0 = 100\text{k}\Omega$, $\beta = 3950$, $T_0 = 298.15\text{K}$)
* **User Input:** DFRobot Rotary Encoder with integrated push-button & Capacitive Touchscreen (GT911 driver)
* **Display:** 320x240 RGB display output driven via PicoDVI (`DVIGFX16`)
* **Telemetry:** Serial1 UART (TX: GPIO 0, RX: GPIO 1) at 115200 baud

---

## 2. Directory Structure & File Map

```
SMD-Heatbed/
├── SMD-Heatbed.ino           # Main Arduino firmware sketch (minimal setup & loop)
├── config.h                  # Hardware pinout, thermal constants, timer & safety parameters
├── touch.h                   # Touch controller abstraction (GT911 / FT6X36 / XPT2046)
├── thermal_control.h / .cpp  # PI control loop, thermistor ADC math, PWM, soft-start ramping
├── input_handler.h / .cpp    # Debounced encoder push-button & quadrature encoder decoding
├── display_manager.h / .cpp  # Native PicoDVI dashboard renderer
├── telemetry.h / .cpp        # Serial UART telemetry logging
├── CMakeLists.txt            # Root CMake build definition
└── README.md                 # Project user documentation & hardware BOM
```

---

## 3. Hardware Pinout Configuration

| Signal | GPIO Pin | Function / Description |
| :--- | :--- | :--- |
| `PIN_ENA` | GPIO 2 | Rotary Encoder Phase A |
| `PIN_ENB` | GPIO 3 | Rotary Encoder Phase B |
| `PIN_EBT` | GPIO 27 | Rotary Encoder Push-Button |
| `PIN_SSR` | GPIO 22 | Solid State Relay PWM Output (`RP2040_PWM` @ 1000 Hz) |
| `PIN_NTC` | GPIO 28 | Analog Input for NTC Thermistor divider (ADC2, 12-bit) |
| `PIN_BACKLIGHT` | GPIO 24 | Display Backlight Control Pin (Active LOW) |
| `TOUCH_SDA` | GPIO 20 | I2C SDA for GT911 Touch Controller |
| `TOUCH_SCL` | GPIO 21 | I2C SCL for GT911 Touch Controller |
| `TOUCH_INT` | GPIO 25 | Touch Controller Interrupt Pin |
| `TOUCH_RST` | GPIO 29 | Touch Controller Reset Pin |
| `SERIAL_TX` | GPIO 0 | Telemetry UART TX (`Serial1` @ 115200 baud) |
| `SERIAL_RX` | GPIO 1 | Telemetry UART RX (`Serial1` @ 115200 baud) |

---

## 4. Software Architecture & Critical Rules

### 4.1 Configuration Management
All configuration values, pin mappings, physical constants, timer parameters, and safety thresholds reside in [`config.h`](file:///Users/jrsarath/Documents/GitHub/SMD-Heatbed/config.h). Do not introduce inline magic numbers in source files.

### 4.2 Timer Interrupt Safety Rules
- Hardware timers (`RPi_Pico_TimerInterrupt`) drive `regulator_isr()` (500 Hz) and `acquisition_isr()` (5000 Hz).
- ISR callbacks must operate quickly and strictly avoid blocking calls, heavy serial printing, or display redraws.
- Display redraws are processed safely inside `loop()` via [`display_manager_update()`](file:///Users/jrsarath/Documents/GitHub/SMD-Heatbed/display_manager.cpp).

---

## 5. Build & Environment Instructions

### Microcontroller Firmware (Arduino IDE / PlatformIO)
1. Board Package: Earle F. Philhower RP2040 / Raspberry Pi Pico core.
2. Required Arduino Libraries:
   - `PicoDVI`
   - `RPi_Pico_TimerInterrupt`
   - `RP2040_PWM`
   - `TAMC_GT911` (or corresponding touch library in `touch.h`)
3. Open `SMD-Heatbed.ino` and upload to Raspberry Pi Pico.
