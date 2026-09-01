# Contributing to Tejasvini

Thank you for your interest in contributing to **Tejasvini**! Tejasvini is an open-source heatplate controller designed for SMD/SMT soldering and reflow work, powered by the Raspberry Pi Pico (RP2040) and an Elecrow 4.3" Pico DVI display.

Because this firmware controls high-temperature physical heating hardware (400W PTC heatplate, mains voltage Solid State Relays), software quality and safety are of paramount importance. Please take a few minutes to read these guidelines before submitting code.

---

## 1. Safety-First Principle

> [!CAUTION]
> **Heater Safety is Non-Negotiable**:
> Firmware in this repository controls mains-powered heatplates capable of exceeding 280°C. A bug or deadlock in the control loop can cause fire, toxic fume generation, or destruction of hardware.
>
> Any contribution that modifies `src/thermal_control.cpp`, `src/config.h`, or sensor acquisition must adhere to the following principles:
> 1. **Fail-Safe Heater OFF**: Any detected sensor anomaly, invalid ADC value, sensor divergence, or unhandled fault must immediately force the heater output LOW and latch into an error state.
> 2. **Latching Faults**: Fault states cannot automatically re-enable the heater. Clearing a fault must require user action, and heating must remain idle until explicitly re-triggered.
> 3. **Never Remove Safety Bounds**: Do not remove `MAX_DUTY` (40%), `OVERTEMP_SHUTDOWN` (280°C), `NTC_MIN_VALID_TEMP`, `NTC_MAX_VALID_TEMP`, or thermal runaway detection.
> 4. **Hardware Safety Required**: Firmware safety checks do NOT replace physical hardware protection (thermal fuse, grounding, fuse).

---

## 2. Development Setup

### 2.1 Toolchain Requirements
* **Microcontroller Core:** Earle F. Philhower Raspberry Pi Pico / RP2040 Arduino core (version 3.x+ / 6.x).
* **CLI Tool:** `arduino-cli` (version 1.x+) or Arduino IDE 2.x.
* **Compiler:** `arm-none-eabi-gcc` (bundled with Earle Philhower core or ARM GNU Toolchain 12+).

### 2.2 Required Arduino Libraries
The following libraries must be installed in your Arduino libraries directory:
* `PicoDVI` (Adafruit fork for RP2040 DVI output)
* `Adafruit_GFX` & `Adafruit_BusIO`
* `lvgl` (version 8.3.x compatible with EEZ Studio UI)
* `RP2040_PWM` (by Khoi Hoang)
* `RPI_PICO_TimerInterrupt` (by Khoi Hoang)
* `TAMC_GT911` (for capacitive touchscreen support)

### 2.3 Compiling from Command Line
You can verify the firmware build locally using `arduino-cli`:

```bash
arduino-cli compile \
  -b rp2040:rp2040:rpipico \
  --build-property "build.extra_flags=-DLV_LVGL_H_INCLUDE_SIMPLE -DLV_USE_OBJ_NAME=1 -DLV_USE_TRANSLATION=1 -Wall -Wextra" \
  .
```

If using VS Code, run the preconfigured build task (`Cmd+Shift+B` or `Terminal -> Run Build Task -> Arduino: Verify (Compile)`).

---

## 3. Repository Architecture

```text
Tejasvini/
├── Tejasvini.ino             # Main Arduino sketch (setup & cooperative non-blocking loop)
├── CMakeLists.txt            # CMake build definition
├── LICENSE                   # MIT License
├── README.md                 # Main user & hardware guide
├── CONTRIBUTING.md           # Contributor guidelines (this file)
├── CODE_OF_CONDUCT.md        # Contributor Covenant Code of Conduct
├── docs/                     # Technical documentation & schematics
│   ├── architecture.md       # Software control loop & UI bridge
│   ├── hardware_and_safety.md# Pinout, NTC voltage divider math, SSR & safety fuses
│   └── calibration_and_tuning.md # PI loop tuning & sensor calibration
└── src/
    ├── config.h              # Single source of truth for pinout, constants, and limits
    ├── display_manager.h/.cpp# PicoDVI driver, LVGL bridge, reflow profile state machine
    ├── input_handler.h/.cpp  # Rotary encoder decoding & button debouncing
    ├── telemetry.h/.cpp      # USB CDC & UART serial logging
    ├── thermal_control.h/.cpp# PI controller, dual NTC ADC math, SSR drive, safety checks
    ├── touch.h/.cpp          # Touchscreen driver abstraction (GT911)
    └── ui/                   # EEZ Studio generated LVGL UI screens, styles, and vars
```

---

## 4. Coding Standards & Expectations

1. **No Magic Numbers**: All hardware pins, timing intervals, sensor constants, PID gains, and thresholds MUST be declared as descriptive `#define` or `constexpr` symbols in `src/config.h`.
2. **Resource-Constrained RP2040 Hygiene**:
   * RP2040 has 264 KB SRAM. The PicoDVI framebuffer occupies ~153.6 KB contiguous dynamic allocation. Keep static `.bss` allocations minimal and avoid large stack allocations.
   * Avoid heavy C++ standard library abstractions (`std::string`, `std::vector`, heap churn).
   * Prefer fixed-size buffers with `snprintf` / `strncpy` and explicit null-termination.
3. **Pin Configuration**:
   * Input pins connected to switches or encoder contacts MUST use `pinMode(pin, INPUT_PULLUP)` to prevent floating inputs.
   * Output pins controlling physical actuators MUST initialize safe output states (e.g. `digitalWrite(PIN_SSR, LOW)`) before enabling `pinMode(OUTPUT)`.
4. **Non-Blocking Execution**:
   * Avoid `delay()` in `loop()`. Use `millis()`-based delta timers or rate limiting so encoder polling and SSR time-proportioning remain responsive.
5. **Compiler Warnings**:
   * Code must compile cleanly with `-Wall -Wextra` without introducing new compiler warnings.

---

## 5. Testing & Validation Expectations

Before opening a pull request, perform the following validation steps:

1. **Compilation Check**:
   Confirm that the project compiles with 0 errors and 0 warnings on the RP2040 Earle Philhower core.
2. **Safety Interlock Testing**:
   If your change affects sensor acquisition or heating:
   * **Open Circuit**: Simulate or test disconnected NTC. Firmware must trip safety shutdown in $< 100\text{ms}$.
   * **Short Circuit**: Simulate or test shorted NTC input. Firmware must trip safety shutdown in $< 100\text{ms}$.
   * **Divergence**: Verify that sensor delta $> 35^\circ\text{C}$ during heating trips safety shutdown.
   * **Thermal Runaway**: Verify that failure to rise under high duty trips safety shutdown within `SAFETY_PERIOD`.
3. **UI & Input Responsiveness**:
   Ensure rotary encoder ticks adjust setpoint smoothly without stutter, and capacitive touch remains accurate.

---

## 6. How to Submit Changes

1. **Fork the Repository** on GitHub.
2. **Create a Feature Branch**:
   ```bash
   git checkout -b feature/my-cool-improvement
   ```
3. **Commit with Clear Messages**:
   * Use concise, descriptive commit subjects (e.g. `thermal: harden raw adc bounds check`, `docs: update pinout mapping in hardware guide`).
4. **Push to Your Fork** and open a Pull Request against the `main` branch.
5. **Fill out the PR Template**: Detail the rationale, safety impact assessment, and testing performed.

---

## 7. Issue & Community Guidelines

* **Bug Reports**: Use the [Bug Report Template](.github/ISSUE_TEMPLATE/bug_report.md) and include hardware details, firmware commit, and serial telemetry logs.
* **Feature Requests**: Use the [Feature Request Template](.github/ISSUE_TEMPLATE/feature_request.md) and outline motivation and hardware resource impact.
* **Electrical/Hardware Questions**: Use the [Hardware Issue Template](.github/ISSUE_TEMPLATE/hardware_issue.md).

All interactions are governed by our [Code of Conduct](CODE_OF_CONDUCT.md). Thank you for helping build safe, reliable open-source hardware tools!
