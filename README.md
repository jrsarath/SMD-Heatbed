# Tejasvini (तेजस्विनी) — Open-Source Heatplate Controller

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform: RP2040](https://img.shields.io/badge/Platform-Raspberry%20Pi%20Pico%20%28RP2040%29-blue.svg)](https://www.raspberrypi.com/products/raspberry-pi-pico/)
[![Display: PicoDVI](https://img.shields.io/badge/Display-PicoDVI%20%28400x240%20%2F%20800x480%29-brightgreen.svg)](https://github.com/Wren6991/PicoDVI)
[![UI: LVGL 8.3](https://img.shields.io/badge/UI-LVGL%208.3%20%2F%20EEZ%20Studio-orange.svg)](https://lvgl.io/)

**Tejasvini** is an open-source, precision heatplate controller firmware engineered for surface-mount (SMD/SMT) reflow soldering, PCB pre-heating, and rework. It runs on the **Raspberry Pi Pico (RP2040)** paired with an **Elecrow 4.3" Pico DVI Display** running a high-resolution native LVGL user interface with touchscreen and rotary encoder controls.

---

## Key Features

* **Dual NTC Thermistor Sensing**: Redundant 100K 3950 NTC thermistors with 32x oversampling, trimmed-mean outlier rejection, and real-time sensor divergence detection.
* **AC Zero-Cross SSR Drive**: 1000ms time-proportioning slow PWM tailored specifically for AC zero-crossing Solid State Relays (e.g. Fotek SSR-25DA) to avoid half-cycle jitter.
* **Soft-Start Reference Ramping**: Temperature ramps smoothly towards setpoint at $1.5^\circ\text{C}/\text{s}$ to prevent thermal shock to ceramic SMD components and eliminate overshoot.
* **Automated 4-Stage Reflow State Machine**:
  * **Lead-Free (SAC305)**: 245°C peak reflow curve.
  * **Leaded (Sn63Pb37)**: 215°C peak reflow curve.
  * **Low-Temperature (Sn42Bi58)**: 150°C peak reflow curve for heat-sensitive components and plastic connectors.
  * **Manual Mode**: Direct setpoint adjustment (0°C to 270°C).
* **High-Resolution PicoDVI Dashboard**: Renders a 240x400 portrait UI (400x240 hardware DVI upscaled 2x to 800x480) with real-time temperature dials, duty percentage, stage timer, and status.
* **Dual Input Interfaces**: Capacitive touchscreen (GT911) with full on-screen control + detented rotary encoder and debounced push-button.
* **Comprehensive Safety Interlocks**: Fast-trip open/short circuit detection (<100ms), thermal runaway monitoring, 280°C emergency shutdown, pre-heat sensor discrepancy check, and clamped duty cycle (max 40%).
* **Real-Time Telemetry**: Tagged structured telemetry streamed simultaneously over USB CDC Serial and UART `Serial1` (115200 baud).

---

## Hardware Specifications & Bill of Materials (BOM)

| Component | Specification / Recommendation | Purpose |
| :--- | :--- | :--- |
| **Microcontroller** | Raspberry Pi Pico (RP2040, 133MHz, 264KB SRAM, 2MB Flash) | Main controller |
| **Display Module** | Elecrow CrowPanel 4.3" Pico DVI Display (RTD2281 scaler, 800x480 panel) | Native DVI output & touch |
| **Touch Controller**| Goodix GT911 Capacitive Touchscreen (I2C) | On-screen user input |
| **Rotary Encoder** | EC11 detented incremental quadrature encoder with momentary push-button | Manual dial input |
| **Heating Element** | 400W 220V/110V PTC Aluminum Heatplate (e.g. 100mm $\times$ 100mm) | Soldering hot plate |
| **Solid State Relay**| 3.3V Logic-compatible Zero-Cross AC SSR (e.g. Fotek SSR-25DA, 25A 250VAC) | Heater power switching |
| **Temperature Sensors**| $2\times$ 100kΩ NTC Thermistors (Beta = 3950, glass bead cartridge) | Redundant thermal sensing |
| **Divider Resistors**| $2\times$ 100kΩ 1% 1/4W Metal Film Resistors | Precision ADC voltage dividers |
| **Thermal Fuse (TCO)**| Non-resettable thermal cut-off fuse rated at 260°C to 280°C | Physical over-temp safety |
| **Mains Fuse** | 3.15A (for 230V) or 5A (for 110V) fast-acting fuse in IEC inlet socket | Mains over-current safety |

---

## Hardware Pinout Configuration

The firmware assigns GPIO pins in [`src/config.h`](src/config.h) as follows:

```
                                  Raspberry Pi Pico
                                     +---+--+---+
                       (TX) GPIO 0  -| 1    40 |-  VBUS (5V Input)
                       (RX) GPIO 1  -| 2    39 |-  VSYS
              (Encoder A)   GPIO 2  -| 4    38 |-  GND
              (Encoder B)   GPIO 3  -| 5    37 |-  3V3_EN
                            ...     -| ...  36 |-  3V3(OUT)
              (Touch SDA)   GPIO 20 -| 26   34 |-  GPIO 28 (Encoder Button)
              (Touch SCL)   GPIO 21 -| 27   32 |-  GPIO 27 (ADC1 / NTC2)
              (SSR Drive)   GPIO 22 -| 29   31 |-  GPIO 26 (ADC0 / NTC1)
              (Backlight)   GPIO 24 -| 30   30 |-  RUN
              (Touch INT)   GPIO 25 -| 31   29 |-  GPIO 29 (Touch RST)
                                     +----------+
```

| Signal | GPIO Pin | Hardware Function | Notes |
| :--- | :--- | :--- | :--- |
| `PIN_ENA` | GPIO 2 | Rotary Encoder Phase A | Internal pullup enabled |
| `PIN_ENB` | GPIO 3 | Rotary Encoder Phase B | Internal pullup enabled |
| `PIN_EBT` | GPIO 28 | Rotary Encoder Push-Button | Internal pullup enabled (Active LOW) |
| `PIN_SSR` | GPIO 22 | Solid State Relay Output | 3.3V logic time-proportioning drive |
| `PIN_NTC1` | GPIO 26 | Primary NTC Thermistor | RP2040 ADC0 (12-bit), 100kΩ divider |
| `PIN_NTC2` | GPIO 27 | Secondary NTC Thermistor | RP2040 ADC1 (12-bit), 100kΩ divider |
| `PIN_BACKLIGHT` | GPIO 24 | Display Backlight Enable | Active LOW |
| `TOUCH_SDA` | GPIO 20 | GT911 I2C Data | 4.7kΩ pullups required |
| `TOUCH_SCL` | GPIO 21 | GT911 I2C Clock | 4.7kΩ pullups required |
| `TOUCH_INT` | GPIO 25 | GT911 Touch Interrupt | Configured in `src/touch.h` |
| `TOUCH_RST` | GPIO 29 | GT911 Touch Reset | Configured in `src/touch.h` |
| `SERIAL_TX` | GPIO 0 | Telemetry UART TX (`Serial1`) | 115200 baud |
| `SERIAL_RX` | GPIO 1 | Telemetry UART RX (`Serial1`) | 115200 baud |

---

## Enclosure & 3D Printed Hardware

Tejasvini includes ready-to-print 3D models located in [`assets/3d files/`](assets/3d%20files/) for building a complete desktop workstation enclosure:

| Model File | Part Description | Recommended Material | Print Settings |
| :--- | :--- | :--- | :--- |
| [`Frame - Main.stl`](assets/3d%20files/Frame%20-%20Main.stl) | Main chassis housing RP2040, SSR, power supply & wiring | PETG / ABS / ASA | 35% Infill, 4 walls |
| [`Frame - Display.stl`](assets/3d%20files/Frame%20-%20Display.stl) | Front bezel securing the 4.3" Pico DVI display & GT911 touch | PETG / ABS / PLA | 25% Infill, 3 walls |
| [`Display Bottom Plate.stl`](assets/3d%20files/Display%20Bottom%20Plate.stl) | Rear protective backing plate for the display module | PETG / ABS / PLA | 25% Infill, 3 walls |
| [`Heating Plate.stl`](assets/3d%20files/Heating%20Plate.stl) | Heatplate carrier base & mechanical mounting bracket | **ABS / ASA / PC** *(High HDT)* | 40% Infill, 5 walls |
| [`Top Plate.stl`](assets/3d%20files/Top%20Plate.stl) | Top deck plate surrounding the heatplate surface | **ABS / ASA / PC** *(High HDT)* | 40% Infill, 4 walls |

> [!IMPORTANT]
> **Thermal Standoffs & Material Selection**:
> For components adjacent to the heatplate (`Heating Plate.stl` and `Top Plate.stl`), use materials with a high Heat Deflection Temperature (HDT) such as **ABS, ASA, or Polycarbonate (PC)**. Standard PLA softens around 55°C–60°C and must **not** be used near the heater. Always install silicone washers, ceramic washers, or brass/PTFE standoffs to thermally isolate the 200°C+ aluminum plate from printed surfaces.

---

## Safety Architecture & Physical Protections

> [!CAUTION]
> **Mains Voltage & Thermal Fire Warning**:
> Heating elements can exceed 280°C and cause severe burns, fire, or toxic gas generation. Solid-state relays almost always fail in a **shorted (ON)** state.
>
> You MUST install independent physical hardware protections:
> 1. **Thermal Cut-Off Fuse (TCO)**: A physical bimetallic or chemical thermal fuse rated at 260°C–280°C MUST be clamped directly against the aluminum plate in series with the AC Live wire.
> 2. **Chassis Earth Grounding**: The metal heatplate MUST be bonded to the AC mains protective earth wire (<0.1Ω to plug ground pin).
> 3. **Mains Fuse**: Fast-acting fuse sized for plate wattage.
>
> See [docs/hardware_and_safety.md](docs/hardware_and_safety.md) for full schematics and electrical requirements.

### Firmware Multi-Tier Safety Checks
* **Instant Open/Short Detection (<100ms)**: Raw ADC counts outside 50 to 4050 counts or raw temperatures outside -20°C to 300°C trip an immediate emergency shutdown.
* **Thermal Runaway Monitor**: Detects disconnected sensors or insufficient temperature rise under active heating within 18 seconds (`SAFETY_PERIOD`).
* **Sensor Divergence Lockout**: Detects detached sensors or uneven plate heating if the dual thermistors disagree by $> 35^\circ\text{C}$ during heating, or $> 15^\circ\text{C}$ before startup.
* **Duty Cycle Clamping**: SSR output is hard-clamped to 40% (`MAX_DUTY`) to protect the heating element and SSR.
* **Latching Shutdown (`trigger_safety_shutdown`)**: All safety trips immediately force the SSR GPIO LOW and require explicit user intervention to clear.

---

## Firmware Software Architecture

The firmware is structured into modular components operating cooperatively:

```text
Tejasvini/
├── Tejasvini.ino             # Main Arduino sketch (setup & cooperative non-blocking loop)
├── CMakeLists.txt            # CMake build definition
├── LICENSE                   # MIT License
├── README.md                 # Project documentation (this file)
├── CONTRIBUTING.md           # Developer guidelines & safety standards
├── CODE_OF_CONDUCT.md        # Contributor Covenant Code of Conduct
├── assets/
│   └── 3d files/             # Ready-to-print STL enclosure & mounting models
├── docs/
│   ├── architecture.md       # Detailed software architecture & state machines
│   ├── hardware_and_safety.md# Pinout, NTC voltage divider math, SSR & safety fuses
│   └── calibration_and_tuning.md # PI loop tuning & sensor calibration
└── src/
    ├── config.h              # Hardware pinout, thermal constants & safety parameters
    ├── display_manager.h/.cpp# PicoDVI display driver, LVGL bridge, reflow state machine
    ├── input_handler.h/.cpp  # Rotary encoder decoding & button debouncing
    ├── telemetry.h/.cpp      # USB CDC & UART serial logging
    ├── thermal_control.h/.cpp# Dual NTC ADC acquisition, PI regulator, SSR PWM, safety
    ├── touch.h/.cpp          # Touchscreen driver abstraction (GT911)
    └── ui/                   # EEZ Studio generated LVGL UI screens, styles, and vars
```

---

## Building and Flashing the Firmware

### Option 1: Using `arduino-cli` (Recommended)

1. Install the [Earle F. Philhower RP2040 Core](https://github.com/earlephilhower/arduino-pico).
2. Install required Arduino libraries (`PicoDVI`, `Adafruit_GFX`, `Adafruit_BusIO`, `lvgl`, `RP2040_PWM`, `RPI_PICO_TimerInterrupt`, `TAMC_GT911`).
3. Compile the project:
   ```bash
   arduino-cli compile \
     -b rp2040:rp2040:rpipico \
     --build-property "build.extra_flags=-DLV_LVGL_H_INCLUDE_SIMPLE -DLV_USE_OBJ_NAME=1 -DLV_USE_TRANSLATION=1 -Wall -Wextra" \
     .
   ```
4. Flash to the board:
   ```bash
   arduino-cli upload -p /dev/tty.usbmodem* -b rp2040:rp2040:rpipico .
   ```
   *(Or hold the **BOOTSEL** button on the Pico while plugging in USB, then copy the compiled `.uf2` file to the `RPI-RP2` drive).*

### Option 2: Using the Arduino IDE 2.x

1. Open `Tejasvini.ino` in Arduino IDE.
2. Select **Board:** `Raspberry Pi Pico` (under Raspberry Pi RP2040 by Earle Philhower).
3. Under **Tools**, configure:
   * **CPU Speed:** 133 MHz (or 200 MHz)
   * **Flash Size:** 2MB (Sketch: 1984KB, FS: 64KB)
   * **USB Stack:** Adafruit TinyUSB
4. Click **Verify** (`Ctrl+R` / `Cmd+R`) and **Upload** (`Ctrl+U` / `Cmd+U`).

---

## Operating Instructions

1. **Boot Screen**: Displays the project banner, firmware version, and initializes the DVI dashboard.
2. **Temperature Adjustment**:
   * Rotate the rotary encoder dial to increase/decrease target temperature in 1°C steps.
   * Or tap the on-screen temperature arc/buttons to adjust setpoint.
3. **Toggle Heating**:
   * Short-press the encoder knob or tap the **START HEATING** button on the display.
4. **Reflow Profile Selection**:
   * Tap the profile dropdown on the dashboard to select **MANUAL**, **LEAD FREE**, **LEADED**, or **LOW TEMP**.
   * Progress bar indicates current stage progress (0–25% Preheat, 25–50% Soak, 50–75% Reflow Peak, 75–100% Cool).
5. **Clear Error / Reset Fault**:
   * Long-press the encoder knob (>1.0 second) to attempt clearing an error state once sensor readings return to valid bounds.

---

## Telemetry Stream

Tejasvini streams structured status logs every 1000ms over USB Serial and UART `Serial1` (GPIO 0 TX / GPIO 1 RX @ 115200 baud):

```text
[Telemetry] Temp: 149.8C (T1: 150.1, T2: 149.5, dT: 0.6) | Target: 150C (Ref: 150.0) | Duty: 24.5% | Status: SOAK [LEAD FREE] | ADC: [2480/98.4k, 2475/98.1k] | Heap: 87450B
```

Send `b` or `?` over the serial monitor to reprint the diagnostic boot banner.

---

## Documentation

* [Architecture & State Machines](docs/architecture.md)
* [Hardware Wiring, Schematics & Safety Fuses](docs/hardware_and_safety.md)
* [Calibration & Controller Tuning](docs/calibration_and_tuning.md)

---

## Contributing

Contributions are welcome! Please read [CONTRIBUTING.md](CONTRIBUTING.md) and our [Code of Conduct](CODE_OF_CONDUCT.md) before submitting pull requests.

---

## License

This project is open-source under the **MIT License**. See the [LICENSE](LICENSE) file for details.

Copyright (c) 2026 Sarath "Delta" Singh <br />
Made with ❤️ in Kolkata, India.