# SMD-Heatbed — Pico LVGL Heatbed Controller

**SMD-Heatbed** is an open-source heatplate controller for reflow/SMT work, built around the Raspberry Pi Pico with a small LVGL touchscreen UI. It implements a PID/PI-style regulator, encoder controls, presets and safety checks suitable for controlling a high-power PTC heatplate via an SSR.

**Hardware (BOM)**
- **3V SSR, 10A** — mains switching for the heatplate (use an SSR whose input is compatible with 3.3V logic).
- **Elecrow 4.3" Pico display** — display driven via the PicoDVI setup.
- **Hi-Link 5V power supply** — 5V supply for peripherals (if required by your display/touch)
- **100K NTC thermistor** — temperature sensor for bed/controller feedback.
- **2.2K resistor** (≈2K) — series/voltage-divider resistor used with the NTC (the code uses `R = 2200`).
- **DFRobot rotary encoder** — encoder with push-button for setpoint control.
- **400W PTC Heatplate** — the heater element controlled via the SSR; verify mains voltage/current ratings.
- **Raspberry Pi Pico (or compatible RP2040 board)** — main microcontroller running the firmware.

**Pin mappings (as used in `LVGL_UI.ino`)**
- `PIN_ENA` GPIO 2 — encoder A
- `PIN_ENB` GPIO 3 — encoder B
- `PIN_EBT` GPIO 27 — encoder push-button
- `PIN_SSR` GPIO 22 — SSR control (PWM driven via RP2040 PWM)
- `PIN_NTC` GPIO 28 — ADC input for NTC divider
- Backlight control pin used in sketch: GPIO 24

Adjust pins in `LVGL_UI.ino` if your wiring differs.

**How it works (brief)**
- The UI allows the user to set a desired temperature (`set_temp`) via the rotary encoder or preset buttons.
- The firmware ramps the internal `reference_temp` toward `set_temp` by an incremental value `REF_STEP` per regulator cycle to avoid aggressive initial overshoot.
- A PI controller computes an SSR PWM duty to drive the heater; safety checks will disable the heater if expected temperature rise does not occur within a timeout.

**Wiring notes & safety**
- Mains wiring is dangerous. Only work on mains-connected hardware if you are qualified and take proper safety precautions (isolate power before changing wiring, use an appropriately rated enclosure and fusing, use earth connection where needed).
- SSR input typically is LED-like; ensure the SSR can be driven by the Pico's 3.3V output and that the input polarity matches. The SSR output must be rated for the mains voltage and current of your heater.
- Mount the NTC thermistor securely to the heatplate so it measures representative temperature. Use the 100K NTC spec matching the code's assumed R0/BETA values or update the firmware constants accordingly.
- The sketch uses `R = 2200` (2.2kΩ) in the NTC voltage divider. If you use a different series resistor, update `R` in the code.
- The heatplate (400W) will draw significant current — ensure wiring and connectors are rated, and fit a suitably sized fuse / circuit protection.

**Software & libraries**
- The firmware is written for Arduino-style RP2040 (Raspberry Pi Pico) environment and depends on these libraries (examples — install via the Arduino Library Manager or PlatformIO equivalents):
  - `PicoDVI` (for the Elecrow Pico DVI display)
  - `lvgl` (LittlevGL graphics library)
  - `RPi_Pico_TimerInterrupt` (timed callbacks)
  - `RP2040_PWM` (PWM helper used in the project)
  - Any touch library used in this repo (see `touch.h`/`touch.c`).

**Build / Upload (Arduino IDE)**
1. Install the Raspberry Pi RP2040 board support in the Arduino IDE (if not already installed).
2. Install the required libraries listed above via the Library Manager.
3. Copy this project folder into your Arduino sketches directory or open `LVGL_UI.ino` directly in the Arduino IDE.
4. Select the correct board (Raspberry Pi Pico / RP2040) and the correct serial/USB port.
5. Click `Upload`.

Optional: clone the repo and open in your preferred editor:

```bash
git clone <your-repo-url>
cd LVGL_UI
# Open LVGL_UI.ino in Arduino IDE or import into PlatformIO
``` 

**Usage**
- Rotate the encoder to change the desired temperature.
- Press the encoder button to toggle the heater state (or use the UI power toggle).
- The UI contains two presets: one maps to 160°C and the other to 250°C (these can be changed in `ui_events.c`).
- Monitor the `Serial1` port at 115200 baud for debug output.

**Configuration**
- `REF_STEP` controls how fast `reference_temp` ramps toward `set_temp` — lower values = slower, gentler ramp; higher = faster.
- `MIN_TEMP` / `MAX_TEMP` limit the allowed setpoint range.
- PID-like gains (`kp`, `ki`) live in `LVGL_UI.ino` and can be tuned for your heatplate.

**Contributing**
Contributions welcome! Please open issues for feature requests or bugs, and submit PRs with clear descriptions. Suggested next improvements:
- Add a proper schematic and PCB layout
- Make the ramping time-based instead of per-timer-step
- Add temperature logging and profile save/load

**License**
This project is intended to be open-source. If you want a permissive license, consider `MIT`. Add a `LICENSE` file when you pick the license.

**Acknowledgements**
- LVGL for the GUI stack
- Elecrow and the PicoDVI community examples

**Contact / Author**
- Project: SMD-Heatbed
- Owner: `@jrsarath`

---

**Credits**

- **Inspiration:** DIY Hot Plate for SMD Soldering using Raspberry Pi Pico — element14 Community[^1]

[^1]: https://community.element14.com/challenges-projects/element14-presents/project-videos/w/documents/71810/diy-hot-plate-for-smd-soldering-using-raspberry-pi-pico----episode-655?CMP=SOM-YOUTUBE-PRG-E14PRESENTS-EP655-DESCRIPTION-COMM