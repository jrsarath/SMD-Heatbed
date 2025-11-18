#ifndef UI_EVENTS_WRAPPER_H
#define UI_EVENTS_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

void call_toggle_heater(void);

// Call from C code to set desired temperature (degrees C)
void call_set_desired_temp(int temp);

// Call from C code to increment/decrement desired temperature by 1
void call_inc_desired_temp(void);
void call_dec_desired_temp(void);

#ifdef __cplusplus
}
#endif

#endif // UI_EVENTS_WRAPPER_H
