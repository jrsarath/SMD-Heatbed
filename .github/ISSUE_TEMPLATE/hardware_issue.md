---
name: Hardware & Wiring Issue
about: Report or seek assistance regarding thermistor reading errors, SSR switching, or display artifacts
title: "[HW] "
labels: ["hardware"]
assignees: ""
---

## Hardware Issue Summary
A clear and concise description of the hardware-related problem (e.g. erratic temperature readings, display noise, touch calibration, SSR not firing).

## Hardware Bill of Materials (BOM)
- **MCU Board:** Raspberry Pi Pico (RP2040)
- **Display Board:** Elecrow CrowPanel 4.3" Pico DVI (RTD2281)
- **Heater Plate:** Model / Wattage / Dimensions (e.g., 400W 220V PTC plate)
- **Solid State Relay (SSR):** Model (e.g., Fotek SSR-25DA, Crydom), Zero-cross AC vs DC MOSFET
- **Thermistor 1 (NTC1):** Rated nominal resistance & Beta (e.g., 100kΩ, Beta=3950)
- **Thermistor 2 (NTC2):** Rated nominal resistance & Beta
- **Divider Resistors:** Exact measured resistance of high-side or low-side divider (Nominal: 100kΩ 1%)

## Physical Wiring Verification
Please confirm the physical wiring matches `src/config.h`:
- [ ] `PIN_NTC1` wired to GPIO 26 (ADC0) with 100kΩ divider to GND
- [ ] `PIN_NTC2` wired to GPIO 27 (ADC1) with 100kΩ divider to GND
- [ ] `PIN_SSR` wired to GPIO 22 (3.3V logic control to SSR `+`, SSR `-` to Pico GND)
- [ ] `PIN_BACKLIGHT` wired to GPIO 24 (Active LOW)
- [ ] `TOUCH_SDA` (GPIO 20) and `TOUCH_SCL` (GPIO 21) have appropriate I2C pullups
- [ ] Mains Earth / Ground is physically bonded to the metal heatplate chassis

## Safety Hardware Checks
- [ ] Independent thermal cut-off fuse (TCO / bimetal switch) installed in series with AC line
- [ ] Correctly rated fast-acting AC mains fuse installed
- [ ] Heatplate chassis measured `< 0.1Ω` to mains earth pin with multimeter

## Observed Symptoms & Diagnostic Data
- **Idle Ambient Reading:** NTC1 = `...°C` (`...` ADC counts), NTC2 = `...°C` (`...` ADC counts)
- **Expected Ambient Reading:** `...°C`
- **Error Messages in Telemetry:**
  ```text
  Paste serial log here
  ```

## Voltage / Oscilloscope Measurements
If available, list measured voltages on:
- 3.3V rail under active DVI display: `... V`
- ADC0 (GPIO 26) at ambient: `... V`
- ADC1 (GPIO 27) at ambient: `... V`
- SSR control input (GPIO 22): `... V`
