#include "ui_events_wrapper.h"

// Prototype of the C++ function defined in the .ino file
void toggleHeater();
void setDesiredTemp(int temp);
void incDesiredTemp();
void decDesiredTemp();

void call_toggle_heater(void) {
    toggleHeater();
}

void call_set_desired_temp(int temp) {
    setDesiredTemp(temp);
}

void call_inc_desired_temp(void) {
    incDesiredTemp();
}

void call_dec_desired_temp(void) {
    decDesiredTemp();
}
