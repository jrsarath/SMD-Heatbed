#ifndef DISPLAY_MANAGER_H_
#define DISPLAY_MANAGER_H_

#include "config.h"
#include "thermal_control.h"
#include "ui/src/ui/ui.h"
#include "ui/src/ui/vars.h"
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

#endif // DISPLAY_MANAGER_H_
