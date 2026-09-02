# AGENTS.md — Developer & AI Agent Guide for Tejasvini

This document provides developer guidelines, architectural rules, hardware specifications, and codebase navigation for AI agents and human developers working on **Tejasvini**.

---

## 1. Project Overview

**Tejasvini** is an open-source heatplate controller designed for SMD/SMT soldering and reflow work. It runs on a **Raspberry Pi Pico (RP2040)** paired with an **Elecrow 4.3" Pico DVI Display** running a high-resolution native LVGL UI (`src/ui/`).

### Key Hardware Specifications
* **MCU:** Raspberry Pi Pico (RP2040 dual ARM Cortex-M0+ microcontroller)
* **Heater Element:** 400W PTC Heatplate driven via a 3.3V Logic Solid State Relay (SSR)
* **Temperature Sensors:** Dual 100K NTC Thermistors in voltage dividers ($R_{\text{divider}} = 100\text{k}\Omega$, $R_0 = 100\text{k}\Omega$, $\beta = 3950$, $T_0 = 298.15\text{K}$)
* **User Input:** EC11 Rotary Encoder with integrated push-button & Capacitive Touchscreen (GT911 driver)
* **Display:** 400x240 RGB display output driven via PicoDVI (`DVIGFX16`, 2x scaled to 800x480 on Elecrow CrowPanel RTD2281, rendered in 240x400 Portrait Mode)
* **Telemetry:** USB CDC Serial and Serial1 UART (TX: GPIO 0, RX: GPIO 1) at 115200 baud

---

## 2. Directory Structure & File Map

```text
Tejasvini/
├── Tejasvini.ino             # Main Arduino firmware sketch (setup & cooperative non-blocking loop)
├── CMakeLists.txt            # Root CMake build definition
├── LICENSE                   # MIT License
├── README.md                 # Project documentation & hardware BOM
├── CONTRIBUTING.md           # Contribution & coding standards guide
├── CODE_OF_CONDUCT.md        # Contributor Covenant Code of Conduct
├── AGENTS.md                 # Developer & AI agent architectural guide (this file)
├── ui.eez-project            # EEZ Studio LVGL project source file
├── assets/                   # Hardware assets & 3D models
│   └── 3d files/             # Ready-to-print STL models (chassis, display frame, plates)
├── docs/                     # Technical documentation & schematics
│   ├── architecture.md       # Detailed software architecture & state machines
│   ├── hardware_and_safety.md# Pinout, NTC voltage divider math, SSR & safety fuses
│   ├── calibration_and_tuning.md # PI loop tuning & sensor calibration
│   └── implementation_log.md # Historical engineering & memory optimization log
└── src/
    ├── config.h              # Hardware pinout, thermal constants, timer & safety parameters
    ├── display_manager.h/.cpp# PicoDVI display driver, LVGL bridge, reflow state machine
    ├── input_handler.h/.cpp  # Debounced encoder push-button & quadrature encoder decoding
    ├── telemetry.h/.cpp      # Serial UART & USB CDC telemetry logging
    ├── thermal_control.h/.cpp# Dual NTC ADC acquisition, PI regulator, SSR PWM, safety
    ├── touch.h/.cpp          # Touch controller abstraction (GT911)
    └── ui/                   # EEZ Studio generated LVGL 8.3 UI implementation
        ├── actions.c/.h      # UI event callbacks (setpoint, toggle, cycle profile)
        ├── screens.c/.h      # Screen layout & widget tree
        ├── styles.c/.h       # Color themes & visual styles
        ├── vars.h            # Native UI variable getters and setters
        └── ui.c/.h           # UI initialization & tick dispatcher
```

---

## 3. Hardware Pinout Configuration

| Signal | GPIO Pin | Function / Description | Notes |
| :--- | :--- | :--- | :--- |
| `PIN_ENA` | GPIO 2 | Rotary Encoder Phase A | Internal pullup enabled |
| `PIN_ENB` | GPIO 3 | Rotary Encoder Phase B | Internal pullup enabled |
| `PIN_EBT` | GPIO 28 | Rotary Encoder Push-Button | Internal pullup enabled (Active LOW) |
| `PIN_SSR` | GPIO 22 | Solid State Relay Output | 3.3V Logic Drive (Time-Proportioning) |
| `PIN_NTC1` | GPIO 26 | Primary NTC Thermistor | RP2040 ADC0 (12-bit), 100kΩ divider |
| `PIN_NTC2` | GPIO 27 | Secondary NTC Thermistor | RP2040 ADC1 (12-bit), 100kΩ divider |
| `PIN_BACKLIGHT` | GPIO 24 | Display Backlight Control | Active LOW |
| `TOUCH_SDA` | GPIO 20 | GT911 Touch Controller I2C SDA | Requires 4.7kΩ pullups |
| `TOUCH_SCL` | GPIO 21 | GT911 Touch Controller I2C SCL | Requires 4.7kΩ pullups |
| `TOUCH_INT` | GPIO 25 | GT911 Touch Controller Interrupt | Configured in `src/touch.h` |
| `TOUCH_RST` | GPIO 29 | GT911 Touch Controller Reset | Configured in `src/touch.h` |
| `SERIAL_TX` | GPIO 0 | Telemetry UART TX (`Serial1`) | 115200 baud |
| `SERIAL_RX` | GPIO 1 | Telemetry UART RX (`Serial1`) | 115200 baud |

---

## 4. Software Architecture & Execution Rules

### 4.1 Cooperative Execution Model
* Firmware execution operates inside a non-blocking cooperative loop in [`Tejasvini.ino`](Tejasvini.ino).
* Do not introduce blocking calls or long `delay()` statements in `loop()`; use `millis()`-based delta timers.

### 4.2 Configuration Management
* All pin mappings, physical constants, controller gains, safety thresholds, and timing parameters reside in [`src/config.h`](src/config.h). Do not introduce inline magic numbers in source files.

### 4.3 Thermal & Duty Cycle Safety (CRITICAL)
* **Immediate Raw Bounds Validation**: Raw ADC values and raw calculated temperatures are validated *before* the smoothing filter to detect open or short circuits in $<100\text{ms}$.
* **Latching Fault Shutdown**: All safety trips must route through `trigger_safety_shutdown()`, which latches `error_state = true`, zeroes `duty` and `acc`, forces `heater = false`, and immediately writes `PIN_SSR` LOW.
* **`MAX_DUTY` Clamping**: SSR duty cycle is strictly limited to 40% (`MAX_DUTY`) to protect the 400W heatplate and SSR. Do not alter `MAX_DUTY` without explicit authorization.
* **Emergency Over-Temperature**: Immediate shutoff at 280°C (`OVERTEMP_SHUTDOWN`).
* **Thermal Runaway Detection**: Validates temperature rise under sustained power within `SAFETY_PERIOD` (18s).

---

## 5. Build & Environment Instructions

### Microcontroller Firmware (Arduino CLI / IDE)
1. Board Package: Earle F. Philhower RP2040 (`rp2040:rp2040:rpipico`).
2. Required Arduino Libraries:
   - `PicoDVI`
   - `Adafruit_GFX` & `Adafruit_BusIO`
   - `lvgl` (version 8.3.x)
   - `RP2040_PWM`
   - `RPI_PICO_TimerInterrupt`
   - `TAMC_GT911`
3. Command-Line Compilation:
   ```bash
   arduino-cli compile \
     -b rp2040:rp2040:rpipico \
     --build-property "build.extra_flags=-DLV_LVGL_H_INCLUDE_SIMPLE -DLV_USE_OBJ_NAME=1 -DLV_USE_TRANSLATION=1 -Wall -Wextra" \
     .
   ```
