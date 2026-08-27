#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_NAV_HOME = 0,
    FLOW_GLOBAL_VARIABLE_NAV_PROFILES = 1,
    FLOW_GLOBAL_VARIABLE_NAV_MANUAL = 2,
    FLOW_GLOBAL_VARIABLE_NAV_INFO = 3
};

// Native global variables

extern const char *get_var_status();
extern void set_var_status(const char *value);
extern bool get_var_nav_home();
extern void set_var_nav_home(bool value);
extern bool get_var_nav_profiles();
extern void set_var_nav_profiles(bool value);
extern bool get_var_nav_manual();
extern void set_var_nav_manual(bool value);
extern bool get_var_nav_info();
extern void set_var_nav_info(bool value);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/