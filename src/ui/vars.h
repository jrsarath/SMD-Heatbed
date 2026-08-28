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
    FLOW_GLOBAL_VARIABLE_NONE
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
extern const char *get_var_heating_button_str();
extern void set_var_heating_button_str(const char *value);
extern const char *get_var_ntc_status();
extern void set_var_ntc_status(const char *value);
extern const char *get_var_controller();
extern void set_var_controller(const char *value);
extern const char *get_var_build();
extern void set_var_build(const char *value);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/