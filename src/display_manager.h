#ifndef DISPLAY_MANAGER_H_
#define DISPLAY_MANAGER_H_

#include "config.h"
#include "thermal_control.h"
#include "ui/ui.h"
#include "ui/vars.h"
#include <Arduino.h>
#include <PicoDVI.h>

/**
 * @brief Initializes the PicoDVI display hardware, backlight, and LVGL UI
 * subsystem.
 */
void display_manager_init();

/**
 * @brief Updates the LVGL display manager task handler.
 * @param force_redraw Unused parameter.
 */
void display_manager_update(bool force_redraw = false);

/**
 * @brief Handles heating toggle action from touch screen or encoder button.
 */
extern "C" void handle_ui_toggle_heating();

/**
 * @brief Cycles to the next reflow profile (stops heating first).
 */
extern "C" void handle_ui_cycle_profile();

#endif // DISPLAY_MANAGER_H_
