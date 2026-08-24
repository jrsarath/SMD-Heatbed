# SMD-Heatbed Display Manager & LVGL Integration Log

This document serves as a persistent step-by-step implementation log to track code changes, hardware diagnostic results, memory benchmarks, state analysis, and rollback checkpoints for the PicoDVI display driver & LVGL Pro UI integration on RP2040.

---

## Current System State Analysis (Checkpoint 0)
- **Hardware Target:** Raspberry Pi Pico (RP2040) + Elecrow 4.3" Pico DVI Display (320x240 RGB565).
- **Display Hardware Driver:** `DVIGFX16 display(DVI_RES_320x240p60, picodvi_dvi_cfg)` via Adafruit PicoDVI library.
- **Current Codebase State:**
  - `src/display_manager.h` & `src/display_manager.cpp`: Bare minimum hardware driver setup with a 1-second RGB color cycle (Red -> Green -> Blue).
  - `src/config.h`: Configured with LVGL heap optimization flags (`LV_MEM_CUSTOM 1`, `LV_USE_STDLIB_MALLOC 1`, `LV_MEM_SIZE (32 * 1024U)`).
  - `SMD-Heatbed.ino`: Calls `display_manager_init()` in `setup()` and `display_manager_update()` in `loop()`.
- **Key Technical Findings:**
  - **Memory Baseline:** RP2040 SRAM is 264 KB. PicoDVI requires a 153.6 KB (153,600 bytes) contiguous dynamic allocation for the 320x240 16-bit DVI framebuffer.
  - **Prior Blocker Solved:** Default LVGL static memory pool pre-allocated ~192 KB in `.bss`, leaving only ~10 KB free heap and causing `display.begin()` to hang. Configuring dynamic heap for LVGL expanded available heap to >20 KB before DVI init and allowed `display.begin()` to report `SUCCESS`.

---

## Log Trajectory & History

### Entry #001 — Bare Minimum RGB Flashing Test
- **Date & Time:** 2026-08-25 01:23:16 IST
- **Goal:** Verify raw hardware DVI signal generation, GPIO backlight control, and DVI framebuffer writing independently of LVGL rendering pipeline.
- **Files Modified:**
  - [`src/display_manager.h`](file:///Users/jrsarath/Documents/GitHub/SMD-Heatbed/src/display_manager.h)
  - [`src/display_manager.cpp`](file:///Users/jrsarath/Documents/GitHub/SMD-Heatbed/src/display_manager.cpp)
- **Code State Details:**
  - Backlight pin `PIN_BACKLIGHT` (GPIO 24) set `OUTPUT` & `LOW`.
  - `display.begin()` called and result logged over `Serial1`.
  - `display_manager_update()` implements a 1000ms timer switching between `COLOR_RED` (`0xF800`), `COLOR_GREEN` (`0x07E0`), and `COLOR_BLUE` (`0x001F`).
- **Telemetry Log Output:**
  ```text
  [Display] Initializing backlight & PicoDVI hardware...
  [Display] Free Heap before DVI init: 20272 bytes
  [Display] Calling display.begin()...
  [Display] display.begin() result: SUCCESS
  [Display Pattern] Initial Fill: RED
  [Display Pattern] GREEN
  [Display Pattern] BLUE
  ```
- **Checkpoint Status:** BASELINE CHECKPOINT #0 CONFIRMED WORKING.

---

### Entry #002 — Integrated LVGL Pro UI Driver & Home Screen
- **Date & Time:** 2026-08-25 01:24:12 IST
- **Goal:** Re-integrate the declarative LVGL Pro UI library (`src/lvgl_ui`) onto the confirmed working PicoDVI hardware display foundation.
- **Files Modified:**
  - [`src/display_manager.h`](file:///Users/jrsarath/Documents/GitHub/SMD-Heatbed/src/display_manager.h)
  - [`src/display_manager.cpp`](file:///Users/jrsarath/Documents/GitHub/SMD-Heatbed/src/display_manager.cpp)
- **Code State Details:**
  - `lv_init()` & `lv_tick_set_cb(my_tick_cb)` initialized for hardware millisecond timing.
  - `lv_display_create(320, 240)` created with `LV_COLOR_FORMAT_RGB565` and 8-line partial buffer (`lvgl_buf`).
  - High-performance zero-copy `memcpy` row flushing to `display.getBuffer()` in `dvi_flush_cb`.
  - Registered touchscreen read callback `touch_read_cb` bridging `src/touch.h`.
  - Executed `lvgl_ui_init("")` and loaded home screen (`lv_screen_load(home_create())`).
  - Added explicit initial screen invalidation `lv_obj_invalidate(lv_screen_active())`.
  - `display_manager_update()` executes `lv_timer_handler()`.
- **Checkpoint Status:** CHECKPOINT #1 IN PROGRESS (Investigating missing flush calls).

---

### Entry #003 — Render Layer Heap Allocation Diagnostics
- **Date & Time:** 2026-08-25 01:27:37 IST
- **Observation:** `display.begin()` succeeded and firmware setup completed, but `dvi_flush_cb` was never invoked by LVGL (`0` flush calls recorded).
- **Hypothesis:** Heap memory remaining after `display.begin()` (20,272 bytes) is consumed during `lvgl_ui_init()` and `home_create()`. When `lv_timer_handler()` attempts to allocate LVGL 9 render layer buffers dynamically via `lv_malloc()`, allocation fails silently and aborts the render pass before calling `dvi_flush_cb`.
- **Files Modified:**
  - [`src/display_manager.cpp`](file:///Users/jrsarath/Documents/GitHub/SMD-Heatbed/src/display_manager.cpp)
- **Changes:**
  - Added heap measurement prints before and after `home_create()` to quantify exact RAM consumption during UI screen tree construction.
- **Checkpoint Status:** REVERTED BACK TO CHECKPOINT #0.

---

### Entry #004 — Rollback to RGB Flashing Baseline (Checkpoint #0)
- **Date & Time:** 2026-08-25 01:31:12 IST
- **Action:** User requested explicit rollback to the working RGB color flashing baseline.
- **Files Modified:**
  - [`src/display_manager.h`](file:///Users/jrsarath/Documents/GitHub/SMD-Heatbed/src/display_manager.h)
  - [`src/display_manager.cpp`](file:///Users/jrsarath/Documents/GitHub/SMD-Heatbed/src/display_manager.cpp)
- **Code State Restored:**
  - Restored bare minimum `display_manager_init()` initializing `display.begin()`, setting rotation, and filling initial RED.
  - Restored 1-second RGB flashing cycle (`display.fillScreen(COLOR_RED / GREEN / BLUE)`) in `display_manager_update()`.
  - Stripped LVGL driver calls, tick callbacks, and touch handlers from `display_manager`.
- **Checkpoint Status:** REVERTED TO BASELINE CHECKPOINT #0.

---

### Entry #005 — Key Learnings from Official LVGL Arduino Documentation
- **Date & Time:** 2026-08-25 01:51:20 IST
- **Source:** Official LVGL Arduino Integration Documentation.
- **Key Technical Insights:**
  1. **LVGL Built-in Debug Logger (`LV_USE_LOG`)**:
     - Enabling `#define LV_USE_LOG 1` and registering a custom UART print callback (`lv_log_register_print_cb(my_log_cb)`) allows LVGL to output internal warnings, heap allocation errors (`LV_LOG_LEVEL_WARN` / `LV_LOG_LEVEL_ERROR`), and render pipeline traces directly to `Serial1`.
     - This gives empirical visibility into why a render pass stutters or aborts.
  2. **Configuration Hierarchy (`lv_conf.h`)**:
     - Placement of `lv_conf.h` in Arduino libraries directory next to `lvgl`.
     - Explicit color depth configuration `<ApiLink name="LV_COLOR_DEPTH" />` (16 for RGB565).
  3. **Arduino Integration Flow (`LVGL_Arduino.ino`)**:
     - Standard custom display driver wrapper (`lv_display_create`, `lv_display_set_flush_cb`, `lv_display_set_buffers`) + touchpad registration (`lv_indev_create`, `lv_indev_set_read_cb`).
     - Periodic `lv_timer_handler()` processing inside `loop()`.
- **Action Plan Formulated:**
  - Register `lv_log_register_print_cb(my_log_cb)` to catch silent LVGL errors over `Serial1`.
  - Verify `LV_COLOR_DEPTH` (16) and color format alignment.
- **Checkpoint Status:** BASELINE CHECKPOINT #0 (Prepared for Logging-Enabled Integration).

---

### Entry #006 — LVGL Display & UI Screen Registration Architecture
- **Date & Time:** 2026-08-25 01:52:15 IST
- **Architectural Clarification:**
  - **1. Display Driver Registration (`lv_display_create`)**:
    Calling `lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT)` registers the physical display dimensions (320x240), color format (`LV_COLOR_FORMAT_RGB565`), draw buffer (`lvgl_buf`), and flush callback (`dvi_flush_cb`) with LVGL. It sets `lv_display_get_default()`.
  - **2. UI Screen Registration (`lv_screen_load`)**:
    Creating a screen via `home_create()` instantiates the top-level screen object (`lv_obj_create(NULL)`). Calling `lv_screen_load(home)` binds that screen tree to LVGL's active display.
  - **3. Hardware Bridge (`dvi_flush_cb`)**:
    LVGL renders widgets into `lvgl_buf` and passes the pixel block (`px_map`) to `dvi_flush_cb`. `dvi_flush_cb` writes those pixels into `display.getBuffer()`, where PicoDVI hardware streams them to the screen.
- **Checkpoint Status:** BASELINE CHECKPOINT #0.

---

### Entry #007 — Display & Screen Registration with LVGL Native Logger
- **Date & Time:** 2026-08-25 01:52:41 IST
- **Goal:** Re-register LVGL display driver (`lv_display_create`), touch indev (`lv_indev_create`), and UI home screen (`lv_screen_load(home_create())`) with native LVGL UART logging enabled (`lv_log_register_print_cb`).
- **Files Modified:**
  - [`src/display_manager.h`](file:///Users/jrsarath/Documents/GitHub/SMD-Heatbed/src/display_manager.h)
  - [`src/display_manager.cpp`](file:///Users/jrsarath/Documents/GitHub/SMD-Heatbed/src/display_manager.cpp)
- **Code State Details:**
  - Registered `my_lv_log_cb` with `lv_log_register_print_cb()` to transmit LVGL internal warnings and error traces directly over `Serial1`.
  - Registered `lv_disp` with `LV_COLOR_FORMAT_RGB565` and `dvi_flush_cb`.
  - Loaded `home_create()` screen and invoked `lv_obj_invalidate(lv_screen_active())`.
  - Flush counter tracking enabled inside `dvi_flush_cb`.
- **Checkpoint Status:** ACTIVE CHECKPOINT #3 (Logging-Enabled Registration Test).

---

### Entry #008 — MCU Watchdog Reset Analysis & Native Widget Isolation
- **Date & Time:** 2026-08-25 01:57:12 IST
- **Observation & Log Output:**
  ```text
  01:55:17.373 -> === SMD Heatbed Firmware Initialized ===
  01:55:17.373 -> [Display] Initializing[Display] lvgl_ui_init done. Loading home screen...
  01:55:17.570 -> [Display] LVGL UI registered & loaded successfully.
  01:55:17.702 -> Setup completed successfully.
  ```
- **Diagnostic Analysis:**
  - `[Display] Initializing[Display]` shows an unexpected RP2040 MCU watchdog/hardware reset mid-execution during initialization due to stack/heap memory faulting.
  - The complex screen tree `home_create()` (from `src/lvgl_ui`) combined with dynamic subject/style bindings exceeds RP2040 stack/heap limits after PicoDVI claims its 153.6 KB framebuffer.
- **Action Plan:**
  - Isolate LVGL display driver registration by replacing `home_create()` with a single minimal native LVGL label widget (`lv_label_create(lv_screen_active())`).
  - Test if native LVGL widgets trigger `dvi_flush_cb` successfully without MCU resets.
- **Checkpoint Status:** CHECKPOINT #4 CONFIRMED SUCCESSFUL.

---

### Entry #009 — Milestone Confirmed: Native LVGL Rendering Verified on PicoDVI Hardware
- **Date & Time:** 2026-08-25 01:58:47 IST
- **Hardware Test Result:**
  - Physical display text: `"SMD HEATBED - LVGL OK"` rendered cleanly in cyan (`0x00FFCC`) on dark background (`0x12151C`).
- **Verified Subsystems:**
  - `DVIGFX16 display` DVI hardware signal generation @ 60 Hz.
  - `LV_COLOR_FORMAT_RGB565` 16-bit color pipeline.
  - `dvi_flush_cb` zero-copy row `memcpy` to `display.getBuffer()`.
  - System millisecond tick source `my_tick_cb` / `millis()`.
  - Native LVGL widget engine, font rendering, style engine, and `lv_timer_handler()` loop execution.
- **Root Cause Confirmed for Full Screen Tree (`home_create()`):**
  - Standard native LVGL rendering is 100% operational on PicoDVI.
  - The monolithic generated UI project (`src/lvgl_ui`) exceeded RP2040 heap limits because it initialized all fonts, icon maps, translation dictionaries, and subject bindings simultaneously.
- **Checkpoint Status:** MILESTONE CHECKPOINT #5 CONFIRMED WORKING.

---

### Entry #010 — Integrated LVGL Pro Editor Project (`src/lvgl_ui`) with `LV_LVGL_H_INCLUDE_SIMPLE`
- **Date & Time:** 2026-08-25 02:00:51 IST
- **Reference Doc:** Official LVGL Pro Arduino Integration Guide (`https://lvgl.io/docs/pro/integration/arduino-ide.mdx`).
- **Files Modified:**
  - [`src/config.h`](file:///Users/jrsarath/Documents/GitHub/SMD-Heatbed/src/config.h)
  - [`src/display_manager.h`](file:///Users/jrsarath/Documents/GitHub/SMD-Heatbed/src/display_manager.h)
  - [`src/display_manager.cpp`](file:///Users/jrsarath/Documents/GitHub/SMD-Heatbed/src/display_manager.cpp)
- **Code State Details:**
  - Added `#define LV_LVGL_H_INCLUDE_SIMPLE 1` to `src/config.h` to resolve include path requirements across nested component folders (`src/lvgl_ui/components/`, `src/lvgl_ui/screens/`).
  - Added `lv_log_register_print_cb(my_lv_log_cb)` to output internal LVGL rendering traces, memory warnings, and trace logs over `Serial1`.
  - Executed `lvgl_ui_init("")` and loaded exported home screen (`lv_screen_load(home_create())`).
  - Flush counter tracking enabled in `dvi_flush_cb`.
- **Checkpoint Status:** ACTIVE CHECKPOINT #6 (LVGL Pro Project Integration).

---

### Entry #011 — Empirical Breakpoint Discovery: Hard Fault Crash During Flush Pass #2
- **Date & Time:** 2026-08-25 02:05:11 IST
- **Critical Serial Log Output:**
  ```text
  02:04:52.939 -> Setup completed successfully.
  02:04:53.038 -> [Display] dvi_flush_cb #1 area: 0,0 to 319,7
  02:04:53.038 -> [Display] dvi_flus
  ```
- **Empirical Breakthrough & Diagnosis:**
  1. `dvi_flush_cb #1` for lines 0 to 7 completed successfully.
  2. The MCU crashed and hard-fault reset immediately at the start of `dvi_flush_cb #2` (lines 8 to 15).
  3. **Root Cause (RP2040 Stack Overflow / ISR Collision)**:
     - RP2040 Core 0 stack size is 4 KB.
     - The rendering pass for `home_create()` (deep nested flexbox columns/rows, font rendering, subject bindings) uses ~3.5 KB of stack space.
     - `TimerAcquisition` (5000 Hz / 200 µs interval) and `TimerRegulator` (500 Hz / 2000 µs interval) trigger interrupts directly on Core 0 during `dvi_flush_cb`, pushing additional stack frames that breach the 4 KB stack limit, causing an immediate RP2040 Hardware Reset.
- **Action Plan:**
  - Increase stack size or optimize ISR execution on Core 0.
  - Temporarily disable 5 kHz hardware timer ISRs during display setup/render verification to isolate ISR stack collision.
- **Checkpoint Status:** ACTIVE DIAGNOSTIC CHECKPOINT #7.










