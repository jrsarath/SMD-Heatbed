#include "actions.h"
#include "screens.h"
#include "ui.h"
#include "vars.h"

/**
 * @brief Handles tab navigation events from the navigation bar widget.
 * @param e LVGL event object carrying the target screen ID in user_data.
 */
void action_navigation(lv_event_t *e) {
  uintptr_t target_screen = (uintptr_t)lv_event_get_user_data(e);
  if (target_screen >= _SCREEN_ID_FIRST && target_screen <= _SCREEN_ID_LAST) {
    switch ((enum ScreensEnum)target_screen) {
    case SCREEN_ID_MAIN:
      set_var_nav_home(true);
      break;
      // case SCREEN_ID_PROFILES:
      //   set_var_nav_profiles(true);
      //   break;
      // case SCREEN_ID_MANUAL:
      //   set_var_nav_manual(true);
      //   break;
      // case SCREEN_ID_INFO:
      //   set_var_nav_info(true);
      break;
    default:
      break;
    }
    loadScreen((enum ScreensEnum)target_screen);
  }
}
