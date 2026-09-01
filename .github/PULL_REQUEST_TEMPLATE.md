## Pull Request Description
Provide a concise explanation of the changes introduced by this pull request. Reference any linked issues.

Closes # (issue number)

---

## Type of Change
- [ ] **Bug fix** (non-breaking change fixing an issue or defect)
- [ ] **Safety improvement** (firmware safety interlock, fault handling, watchdog)
- [ ] **New feature** (non-breaking change adding functionality)
- [ ] **Refactoring / Code quality** (cleanups, type consistency, removing dead code)
- [ ] **Documentation update** (README, docs, wiring diagrams, comments)
- [ ] **Hardware support / Board variant** (touch driver, display controller, pin mapping)

---

## Safety Impact Assessment
> [!CAUTION]
> Tejasvini controls high-power heating elements and AC mains SSRs. Any changes to temperature calculation, ADC acquisition, control loops, or duty cycle limits carry physical safety implications.

- [ ] Does this PR modify any thermal parameters in `src/config.h`?
- [ ] Does this PR modify NTC resistance math or ADC oversampling?
- [ ] Does this PR alter the PI regulator, soft-start ramp, or SSR actuation?
- [ ] Does this PR alter thermal runaway, sensor divergence, or emergency over-temp shutoff?
- [ ] If YES to any above, explain how the change was validated to prevent thermal runaway or unsafe heater lock-on:

---

## Testing & Verification
Describe how the changes were verified:

### 1. Build Verification
- [ ] Compiled with `arduino-cli` / Arduino IDE targeting `rp2040:rp2040:rpipico`
- [ ] Build succeeds with 0 errors
- [ ] RAM and Flash usage verified within RP2040 limits (RP2040 SRAM: 264 KB)

### 2. Hardware / Bench Testing (if applicable)
- [ ] Bench tested with real hardware (RP2040 + Elecrow DVI + NTCs + SSR)
- [ ] Tested open-circuit / disconnected NTC behavior (heater immediately trips OFF)
- [ ] Tested short-circuit NTC behavior (heater immediately trips OFF)
- [ ] Tested rotary encoder and touch responsiveness
- [ ] Telemetry stream checked over Serial / Serial1 (115200 baud)

---

## Checklist
- [ ] Code follows existing project style and naming conventions
- [ ] No magic numbers introduced (all constants defined in `src/config.h`)
- [ ] Documentation updated to reflect changes (if applicable)
- [ ] No copyrighted code or incompatible licenses included
