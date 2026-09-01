---
name: Bug Report
about: Create a report to help us reproduce and fix a firmware or UI defect
title: "[BUG] "
labels: ["bug"]
assignees: ""
---

## Description
A clear and concise description of what the bug is.

## Expected Behavior
A clear and concise description of what you expected to happen.

## Actual Behavior
What actually happened (include observed display states, heater behavior, or status messages).

## Steps to Reproduce
1. Power on the device / flash firmware version `...`
2. Set temperature or profile to `...`
3. Press / rotate `...`
4. Observe the issue: `...`

## Hardware Environment
- **MCU Board:** Raspberry Pi Pico (RP2040) / Feather RP2040 DVI / Other
- **Display Module:** Elecrow CrowPanel 4.3" Pico DVI (RTD2281) / Other
- **Touch Controller:** GT911 / FT6X36 / XPT2046 / None
- **Sensors:** Dual 100K 3950 NTCs / Single NTC / Other
- **SSR / Heater:** 400W PTC / AC Solid State Relay / DC MOSFET
- **Power Supply:** 5V Pico supply voltage and AC mains voltage

## Software & Toolchain Environment
- **Firmware Version / Git Commit:** (e.g. `v1.0.1` / commit hash)
- **Core / Toolchain:** Earle F. Philhower RP2040 core version `...`
- **Build Method:** `arduino-cli` / Arduino IDE / PlatformIO
- **LVGL Version:** `8.3.x`

## Telemetry / Serial Log
If possible, attach the startup banner and telemetry output from USB Serial or UART `Serial1` (GPIO 0/1 @ 115200 baud):

```text
Paste logs here
```

## Additional Context
Add any other context, screenshots, or oscilloscope/multimeter measurements here.
