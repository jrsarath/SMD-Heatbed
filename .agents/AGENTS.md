# AGENTS.md — Developer & AI Agent Guide for Tejasvini

This document provides developer guidelines, architectural rules, hardware specifications, and codebase navigation for AI agents and human developers working on **Tejasvini**.

---

## 1. Project Overview

**Tejasvini** is an open-source heatplate controller designed for reflow and SMT soldering work. It runs on a **Raspberry Pi Pico (RP2040)** paired with an **Elecrow 4.3" Pico DVI Display** running a declarative **LVGL UI** (`src/ui/`).

### Key Hardware Specifications
* **MCU:** Raspberry Pi Pico (RP2040 microcontroller)
* **Heater Element:** 400W PTC Heatplate driven via a 3.3V Logic Solid State Relay (SSR)
* **Temperature Sensor:** 100K NTC Thermistor in a voltage divider ($R = 2.2\text{k}\Omega$, $R_0 = 100\text{k}\Omega$, $\beta = 3950$, $T_0 = 298.15\text{K}$)
* **User Input:** DFRobot Rotary Encoder with integrated push-button & Capacitive Touchscreen (GT911 driver)
* **Display:** 400x240 RGB display output driven via PicoDVI (`DVIGFX16`, 2x scaled to 800x480 on Elecrow CrowPanel RTD2281)
* **Telemetry:** Serial1 UART (TX: GPIO 0, RX: GPIO 1) at 115200 baud

---

## 2. Directory Structure & File Map

```
Tejasvini/
├── Tejasvini.ino             # Main Arduino firmware sketch (timer ISRs, setup & loop)
├── CMakeLists.txt            # Root CMake build definition
├── README.md                 # Project user documentation & hardware BOM
├── AGENTS.md                 # Developer & AI agent architectural guide (this file)
├── docs/                     # Local offline documentation
│   └── lvgl/                 # Complete LVGL Pro XML syntax & architecture documentation
│       ├── README.md         # Documentation index & quick lookup reference
│       ├── syntax.mdx        # Core syntax index
│       ├── syntax/           # Detailed syntax pages (components, styles, data-binding, etc.)
│       ├── built_in_widgets.mdx
│       ├── ai.mdx            # LVGL AI integration & development loop guide
│       └── cli.mdx           # LVGL Pro CLI reference
└── src/
    ├── config.h              # Hardware pinout, thermal constants, timer & safety parameters
    ├── touch.h               # Touch controller abstraction (GT911 / FT6X36 / XPT2046)
    ├── thermal_control.h/.cpp# PI control loop, thermistor ADC math, PWM, soft-start ramping
    ├── input_handler.h/.cpp  # Debounced encoder push-button & quadrature encoder decoding
    ├── display_manager.h/.cpp# PicoDVI display driver & renderer bridge
    ├── telemetry.h/.cpp      # Serial UART telemetry logging
    └── lvgl_ui/              # Declarative LVGL Pro XML UI project
        ├── project.xml       # Project config, LVGL version (9.5.0), target displays
        ├── globals.xml       # Design system tokens: constants, styles, fonts, subjects
        ├── components/       # Reusable UI components (navigation, layout, controls, typography)
        ├── screens/          # Application screens (home, presets, settings, reflow, etc.)
        ├── fonts/ & images/  # Font assets and SVG vector icons
        ├── tests/            # Automated headless XML UI tests
        └── sim/              # Desktop simulator entry point
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

## 4. LVGL Pro XML UI Development & Documentation Reference (CRITICAL)

> [!IMPORTANT]
> ### Mandatory Rule for AI Agents: Referencing LVGL XML Documentation
> When creating, modifying, reviewing, or refactoring XML UI files in `src/lvgl_ui/`, **AI agents MUST ALWAYS refer to the local documentation stored in [`docs/lvgl/`](docs/lvgl/)**.
>
> Core reference files:
> - [`docs/lvgl/syntax.mdx`](docs/lvgl/syntax.mdx) — Main syntax index & element structure
> - [`docs/lvgl/syntax/overview.mdx`](docs/lvgl/syntax/overview.mdx) — Syntax rules, property types, naming conventions
> - [`docs/lvgl/syntax/components.mdx`](docs/lvgl/syntax/components.mdx) — Component architecture, parameters, slots, and APIs
> - [`docs/lvgl/syntax/widgets.mdx`](docs/lvgl/syntax/widgets.mdx) & [`docs/lvgl/built_in_widgets.mdx`](docs/lvgl/built_in_widgets.mdx) — Built-in & custom widget schemas
> - [`docs/lvgl/syntax/screens.mdx`](docs/lvgl/syntax/screens.mdx) & [`docs/lvgl/syntax/view.mdx`](docs/lvgl/syntax/view.mdx) — Screens, layouts, permanent screens, view hierarchy
> - [`docs/lvgl/syntax/styles.mdx`](docs/lvgl/syntax/styles.mdx) & [`docs/lvgl/syntax/constants.mdx`](docs/lvgl/syntax/constants.mdx) — Style sheets, state selectors, design constants
> - [`docs/lvgl/syntax/events.mdx`](docs/lvgl/syntax/events.mdx) & [`docs/lvgl/syntax/data-binding.mdx`](docs/lvgl/syntax/data-binding.mdx) — Event handling, screen switching, subject bindings
> - [`docs/lvgl/syntax/animations.mdx`](docs/lvgl/syntax/animations.mdx) — Timelines and transition animations
> - [`docs/lvgl/ai.mdx`](docs/lvgl/ai.mdx) — AI development loop and validation patterns

### 4.1 LVGL XML Architecture & Syntax Rules

1. **Naming Conventions:**
   - Attribute names: lowercase with underscore separation (e.g. `bg_color`, `border_width`, `pad_top`).
   - Constant references: Prefix with `#` (e.g. `pad="#space_md"`, `gap="#space_sm"`, `color="#color_primary"`).
   - Component property parameters: Prefix with `$` (e.g. `text="$title"`, `value="$temp"`).
   - Dynamic math expressions: Wrap in `{}` without `$` or `#` (e.g. `width="{width - 20}"`).

2. **Design Tokens & Theme Consistency:**
   - Never hardcode raw color hexes or magic spacing numbers in screen XMLs.
   - Always leverage definitions in [`src/lvgl_ui/globals.xml`](src/lvgl_ui/globals.xml) (`#color_*`, `#space_*`, `#radius_*`, `#font_*`).

3. **Component Hierarchy & Reusability:**
   - Build UI using modular components located in `src/lvgl_ui/components/`:
     - Layout: `<container>`, `<panel>`, `<row>`, `<column>`, `<base_box>`
     - Typography: `<h1>`...`<h5>`, `<text>`
     - Controls: `<button>`, `<slider>`, `<arc>`, `<switch>`, `<checkbox>`, `<dropdown>`, `<text_input>`
     - Navigation: `<navigation_bar>`, `<navigation_button>`
   - Screen files (`src/lvgl_ui/screens/`) should focus on high-level screen layout and compose components.

4. **Reactive Data Binding:**
   - Bind dynamic state to subjects declared in `globals.xml` using `bind_text`, `bind_value`, or `bind_style`.

---

## 5. Software Architecture & Critical Rules

### 5.1 Configuration Management
All configuration values, pin mappings, physical constants, timer parameters, and safety thresholds reside in [`src/config.h`](src/config.h). Do not introduce inline magic numbers in source files.

### 5.2 Timer Interrupt Safety Rules
- Hardware timers (`RPi_Pico_TimerInterrupt`) drive `regulator_isr()` (500 Hz) and `acquisition_isr()` (5000 Hz).
- ISR callbacks must operate quickly and strictly avoid blocking calls, heavy serial printing, or direct UI drawing.
- UI redraws are processed safely inside `loop()` via `display_manager_update()` and `lv_timer_handler()`.

### 5.3 Thermal & Duty Cycle Safety
- `MAX_DUTY` is intentionally limited to 40% to protect the 400W heatplate and mains SSR. Do not alter `MAX_DUTY` or remove duty cycle bounds without explicit verification.
- Maintain thermal runaway safety checks (`SAFETY_PERIOD` / `SAFETY_THRESHOLD`).

---

## 6. Build & Environment Instructions

### Microcontroller Firmware (Arduino IDE / PlatformIO)
1. Board Package: Earle F. Philhower RP2040 / Raspberry Pi Pico core.
2. Required Arduino Libraries:
   - `PicoDVI`
   - `lvgl` (version 9.5.0 / 8.3.x compatible)
   - `RPi_Pico_TimerInterrupt`
   - `RP2040_PWM`
   - `TAMC_GT911` (or corresponding touch library in `touch.h`)
3. Open `Tejasvini.ino` and upload to Raspberry Pi Pico.

### UI Desktop Simulator & Testing
1. Navigate to `src/lvgl_ui/` or root workspace.
2. Run test suites or simulator:
   ```bash
   lved run-all-tests src/lvgl_ui
   ```
