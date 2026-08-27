# Tejasvini — Open-Source Heatplate Controller Firmware

**Tejasvini (तेजस्विनी)** is an open-source heatplate controller designed for reflow and SMT soldering work. It runs on a **Raspberry Pi Pico (RP2040)** paired with an **Elecrow 4.3" Pico DVI Display** rendering a real-time native DVI status dashboard.

---

## Hardware Specifications & Bill of Materials (BOM)
* **MCU:** Raspberry Pi Pico (RP2040 microcontroller)
* **Heater Element:** 400W PTC Heatplate driven via a 3.3V Logic Solid State Relay (SSR)
* **Temperature Sensor:** 100K NTC Thermistor in a voltage divider ($R = 2.2\text{k}\Omega$, $R_0 = 100\text{k}\Omega$, $\beta = 3950$, $T_0 = 298.15\text{K}$)
* **User Input:** DFRobot Rotary Encoder with integrated push-button & Capacitive Touchscreen (GT911 driver)
* **Display:** Elecrow CrowPanel RTD2281 4.3" DVI display (400x240 RGB driven via PicoDVI, scaled 2x to 800x480)
* **Telemetry:** Serial1 UART (TX: GPIO 0, RX: GPIO 1) at 115200 baud

---

## Hardware Pinout Configuration

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

## Firmware Software Architecture

The firmware is structured cleanly into modular C++ components with a minimal main sketch:

```
Tejasvini/
├── Tejasvini.ino             # Main Arduino sketch (minimal, standard setup & loop)
├── config.h                  # Hardware pinout, thermal constants, timer & safety parameters
├── touch.h                   # Touch controller abstraction & GT911 driver setup
├── thermal_control.h / .cpp  # Thermistor ADC math, PI controller, PWM, soft-start, safety checks
├── input_handler.h / .cpp    # Debounced encoder push-button & quadrature encoder decoding
├── display_manager.h / .cpp  # Native PicoDVI dashboard renderer (Current & Target Temp, Duty %, Status)
└── telemetry.h / .cpp        # Serial1 UART telemetry output
```

### Module Descriptions
- **`config.h`**: Central header containing all `#define` hardware pin definitions, controller gains, safety thresholds, and screen specs.
- **`thermal_control`**: Implements thermistor temperature reading (Steinhart-Hart equation), PI controller, soft-start reference ramping, SSR PWM control, and thermal runaway safety lockout.
- **`input_handler`**: Handles rotary encoder quadrature decoding and debounced push-button logic for setpoint control and heater toggling.
- **`display_manager`**: Renders the 240x400 portrait UI directly on the PicoDVI display (400x240 @ 60Hz scaled 2x to 800x480).
- **`telemetry`**: Periodically logs formatted status data over `Serial1` for temperature curve tracking.

---

## Safety & Ramping Features
1. **Soft-Start Ramping:** Increments `reference_temp` towards `set_temp` by `REF_STEP` (0.05°C/cycle) to prevent thermal overshoot.
2. **Duty Cycle Clamping:** SSR duty cycle is strictly clamped between `0%` and `40%` (`MAX_DUTY`) to protect the mains SSR and heatplate.
3. **Thermal Runaway Safety Check:** If temperature fails to rise by at least `SAFETY_THRESHOLD` (2.0°C) over `SAFETY_PERIOD` (18,000 ms) while active, the controller triggers an **NTC ERROR** state, disables PWM output, and locks out the heater.

---

## Build & Upload Instructions

### Required Libraries (Arduino IDE)
1. **Board Package:** Earle F. Philhower RP2040 / Raspberry Pi Pico core.
2. **Arduino Libraries:**
   - `PicoDVI`
   - `RPi_Pico_TimerInterrupt`
   - `RP2040_PWM`
   - `TAMC_GT911` (or corresponding touch library configured in `touch.h`)

### Upload Steps
1. Open `Tejasvini.ino` in the Arduino IDE.
2. Select **Raspberry Pi Pico** (or equivalent RP2040 board) and your USB serial port.
3. Compile and upload to the board.
4. Open Serial Monitor on `Serial1` (GPIO 0/1) at **115200 baud** to view real-time telemetry logs.

---
### Made with ❤️ in Kolkata, India
