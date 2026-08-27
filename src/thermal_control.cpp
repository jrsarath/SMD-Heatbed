#include "thermal_control.h"

// Global hardware instances
static RP2040_PWM* pwm_ssr = nullptr;

// Internal state variables (volatile for ISR safe access)
static volatile int set_temp = 0;
static volatile float reference_temp = 0.0f;
static volatile float measured_temp = 0.0f;
static volatile float measured_resistance = 0.0f;
static volatile int adc_raw = 0;

static volatile float duty = 0.0f;
static volatile float acc = 0.0f;
static volatile float error = 0.0f;

static volatile bool heater = false;
static volatile uint32_t heater_turned_on = 0;

static volatile float last_safety_temp = 0.0f;
static volatile uint32_t last_safety_check = 0;
static volatile bool error_state = false;

void thermal_control_init() {
  pinMode(PIN_SSR, OUTPUT);
  pinMode(PIN_NTC, INPUT);
  analogReadResolution(12);

  // Initialize RP2040 PWM driver for SSR
  pwm_ssr = new RP2040_PWM(PIN_SSR, PWM_FREQUENCY, 0.0f);
  if (pwm_ssr) {
    pwm_ssr->setPWM();
  }
}

float measure_temperature() {
  adc_raw = analogRead(PIN_NTC);
  if (adc_raw <= 0) adc_raw = 1; // Protect against division by zero

  // Voltage divider resistance calculation
  measured_resistance = R_DIVIDER * (4086.0f / (float)adc_raw - 1.0f);
  if (measured_resistance <= 0.0f) measured_resistance = 0.001f;

  // Steinhart-Hart / Beta equation for NTC thermistor
  float term = measured_resistance / (R0_THERMISTOR * powf(MATH_E, -BETA_COEFF / T0_KELVIN));
  measured_temp = (BETA_COEFF / logf(term)) - 273.15f;

  return measured_temp;
}

bool regulator_isr(struct repeating_timer *t) {
  (void)t;

  measure_temperature();

  if (heater && !error_state) {
    // Reference ramping (soft-start)
    if (set_temp > reference_temp) reference_temp += REF_STEP;
    if (set_temp < reference_temp) reference_temp = (float)set_temp;

    // PI Controller
    error = reference_temp - measured_temp;
    acc += error;

    duty = KP_GAIN * error + KI_GAIN * acc;

    // Turn off heater duty if setpoint reached closely after initial ramp
    uint32_t active_time = millis() - heater_turned_on;
    if (error < 10.0f && active_time > 10000) duty = 0.0f;
    if (error < 5.0f && active_time < 10000) duty = 0.0f;

    // Overshoot regulation (duty clamping)
    if (duty > MAX_DUTY) {
      duty = MAX_DUTY;
      acc -= error;
    }

    // Undershoot regulation
    if (duty < MIN_DUTY) {
      duty = MIN_DUTY;
      acc -= error;
    }

    // Reset safety check timer when duty cycle drops to zero
    if (duty == MIN_DUTY) {
      last_safety_check = millis();
    }

    // Thermal runaway safety check
    if (millis() - last_safety_check > SAFETY_PERIOD) {
      last_safety_check = millis();
      if (measured_temp - last_safety_temp < SAFETY_THRESHOLD) {
        // Temperature failed to rise sufficiently under active heating -> Thermal Error
        error_state = true;
        duty = 0.0f;
        acc = 0.0f;
      }
      last_safety_temp = measured_temp;
    }

    // Update SSR PWM output
    if (pwm_ssr) {
      float current_duty = duty;
      pwm_ssr->setPWM(PIN_SSR, (float)PWM_FREQUENCY, current_duty);
    }

  } else if (!error_state) {
    // Idle state (heater off, no error)
    acc = 0.0f;
    duty = 0.0f;
    last_safety_check = millis();
    if (pwm_ssr) {
      pwm_ssr->setPWM(PIN_SSR, PWM_FREQUENCY, 0.0f);
    }
  } else {
    // Error state safety lockout
    duty = 0.0f;
    acc = 0.0f;
    if (pwm_ssr) {
      pwm_ssr->setPWM(PIN_SSR, PWM_FREQUENCY, 0.0f);
    }
  }

  return true;
}

void set_desired_temp(int temp) {
  if (temp < MIN_TEMP) temp = MIN_TEMP;
  if (temp > MAX_TEMP) temp = MAX_TEMP;
  set_temp = temp;
}

void change_desired_temp(int delta) {
  set_desired_temp(set_temp + delta);
}

void toggle_heater() {
  set_heater(!heater);
}

void set_heater(bool state) {
  if (error_state && state) return; // Do not turn on if in error state

  heater = state;
  if (heater) {
    heater_turned_on = millis();
    last_safety_check = millis();
    last_safety_temp = measured_temp;
  }
}

float get_measured_temp() {
  return measured_temp;
}

int get_raw_adc() {
  return adc_raw;
}

float get_measured_resistance() {
  return measured_resistance;
}

int get_desired_temp() {
  return set_temp;
}

float get_reference_temp() {
  return reference_temp;
}

float get_duty_cycle() {
  return duty;
}

bool is_heater_on() {
  return heater;
}

bool is_error_state() {
  return error_state;
}

HeatbedStatus get_system_status() {
  if (error_state) return STATUS_NTC_ERROR;
  if (heater) return STATUS_HEATING;
  return STATUS_IDLE;
}
