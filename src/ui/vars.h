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
    FLOW_GLOBAL_VARIABLE_NAV_INFO = 3,
    FLOW_GLOBAL_VARIABLE_TARGET_TEMP_STR = 4,
    FLOW_GLOBAL_VARIABLE_CURRENT_TEMP_STR = 5,
    FLOW_GLOBAL_VARIABLE_HEATER_STATE = 6,
    FLOW_GLOBAL_VARIABLE_HEATER_STATUS = 7,
    FLOW_GLOBAL_VARIABLE_OUTPUT_PERCENTAGE_STR = 8,
    FLOW_GLOBAL_VARIABLE_PROFILE = 9,
    FLOW_GLOBAL_VARIABLE_CURRENT_TEMP_VAL = 10,
    FLOW_GLOBAL_VARIABLE_TARGET_TEMP_VAL = 11,
    FLOW_GLOBAL_VARIABLE_OUTPUT_PERCENTAGE_VAL = 12,
    FLOW_GLOBAL_VARIABLE_UPTIME = 13
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
extern const char *get_var_target_temp_str();
extern void set_var_target_temp_str(const char *value);
extern const char *get_var_current_temp_str();
extern void set_var_current_temp_str(const char *value);
extern const char *get_var_heater_state();
extern void set_var_heater_state(const char *value);
extern const char *get_var_heater_status();
extern void set_var_heater_status(const char *value);
extern const char *get_var_output_percentage_str();
extern void set_var_output_percentage_str(const char *value);
extern const char *get_var_profile();
extern void set_var_profile(const char *value);
extern int32_t get_var_current_temp_val();
extern void set_var_current_temp_val(int32_t value);
extern int32_t get_var_target_temp_val();
extern void set_var_target_temp_val(int32_t value);
extern int32_t get_var_output_percentage_val();
extern void set_var_output_percentage_val(int32_t value);
extern const char *get_var_uptime();
extern void set_var_uptime(const char *value);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/