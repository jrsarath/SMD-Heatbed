#ifndef DISPLAY_MANAGER_H_
#define DISPLAY_MANAGER_H_

#include <Arduino.h>
#include <PicoDVI.h>
#include "config.h"
#include "thermal_control.h"

/**
 * @brief Initializes the PicoDVI display hardware, backlight, and dashboard layout.
 */
void display_manager_init();

/**
 * @brief Updates the DVI display dashboard with current thermal readings and system status.
 * @param force_redraw Force a complete redraw of static UI elements.
 */
void display_manager_update(bool force_redraw = false);

#endif // DISPLAY_MANAGER_H_
