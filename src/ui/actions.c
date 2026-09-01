#include "actions.h"
#include "screens.h"
#include "ui.h"
#include "vars.h"
#include <stdint.h>

// External thermal control functions
extern void set_desired_temp(int temp);
extern void change_desired_temp(int delta);
extern void toggle_heater();

/**
 * @brief Sets the target temperature directly.
 * @param e LVGL event object carrying the desired temperature in user_data.
 */
void action_set_target_temp(lv_event_t *e) {
  intptr_t target_temp = (intptr_t)lv_event_get_user_data(e);
  if (target_temp > 0) {
    set_desired_temp((int)target_temp);
  }
}

/**
 * @brief Increases the target temperature by delta amount.
 * @param e LVGL event object carrying the increment step (defaults to 1 if 0).
 */
void action_increase_target_temp(lv_event_t *e) {
  intptr_t delta = (intptr_t)lv_event_get_user_data(e);
  int step = (delta != 0) ? (int)delta : 1;
  change_desired_temp(step);
}

/**
 * @brief Decreases the target temperature by delta amount.
 * @param e LVGL event object carrying the decrement step (defaults to 1 if 0).
 */
void action_decrease_target_temp(lv_event_t *e) {
  intptr_t delta = (intptr_t)lv_event_get_user_data(e);
  int step = (delta != 0) ? (int)delta : 1;
  change_desired_temp(-step);
}

extern void handle_ui_toggle_heating();
extern void handle_ui_cycle_profile();

/**
 * @brief Toggles heater ON/OFF state or cancels active reflow stage.
 * @param e LVGL event object.
 */
void action_toggle_heating(lv_event_t *e) {
  (void)e;
  handle_ui_toggle_heating();
}

/**
 * @brief Cycles to the next reflow profile (stops heating first).
 * @param e LVGL event object.
 */
void action_cycle_profile(lv_event_t *e) {
  (void)e;
  handle_ui_cycle_profile();
}


