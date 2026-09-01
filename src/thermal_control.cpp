#include "thermal_control.h"
#include <math.h>

// Global hardware instances
#if !SSR_TIME_PROPORTIONING
static RP2040_PWM *pwm_ssr = nullptr;
#endif

// Internal state variables (volatile for thread/ISR safe access)
static volatile int set_temp = 0;
static volatile float reference_temp = 0.0f;
static volatile float measured_temp = 0.0f;  // Composite (average) temperature
static volatile float measured_temp1 = 0.0f; // NTC 1 temperature
static volatile float measured_temp2 = 0.0f; // NTC 2 temperature
static volatile float measured_resistance1 = 0.0f;
static volatile float measured_resistance2 = 0.0f;
static volatile int adc_raw1 = 0;
static volatile int adc_raw2 = 0;

static volatile float duty = 0.0f;
static volatile float acc = 0.0f;
static volatile float error = 0.0f;

static volatile bool heater = false;
static volatile uint32_t heater_turned_on = 0;

static volatile float last_safety_temp = 0.0f;
static volatile uint32_t last_safety_check = 0;
static volatile bool error_state = false;

static uint8_t divergence_fault_count = 0;
static uint32_t window_start_time = 0;
static uint32_t last_control_time = 0;
static bool first_sample = true;

/**
 * @brief Computes thermistor resistance and Steinhart-Hart/Beta temperature from raw ADC.
 */
static float calculate_ntc_temperature(int raw_adc, float &out_resistance) {
  // Clamp ADC input to valid non-zero, non-saturated range
  if (raw_adc <= 0) raw_adc = 1;
  if (raw_adc >= 4095) raw_adc = 4094;

  // Voltage divider resistance calculation (12-bit ADC full scale: 4095 counts)
  // NTC connected between 3.3V and ADC pin; R_DIVIDER connected between ADC pin and GND
  float resistance = R_DIVIDER * (4095.0f / (float)raw_adc - 1.0f);
  if (resistance <= 0.001f) resistance = 0.001f;
  out_resistance = resistance;

  // Standard Steinhart-Hart / Beta equation: 1/T = 1/T0 + (1/Beta) * ln(R / R0)
  float steinhart = (1.0f / T0_KELVIN) + (1.0f / BETA_COEFF) * logf(resistance / R0_THERMISTOR);
  float temp_c = (1.0f / steinhart) - 273.15f;

  return temp_c;
}

/**
 * @brief Low-level SSR driver supporting both AC Time-Proportioning and Hardware PWM.
 */
static void update_ssr_actuation(uint32_t now) {
  if (error_state || !heater || duty <= MIN_DUTY) {
#if SSR_TIME_PROPORTIONING
    digitalWrite(PIN_SSR, LOW);
#else
    if (pwm_ssr) pwm_ssr->setPWM(PIN_SSR, PWM_FREQUENCY, 0.0f);
#endif
    return;
  }

#if SSR_TIME_PROPORTIONING
  if (now - window_start_time >= SSR_WINDOW_MS) {
    window_start_time = now;
  }
  uint32_t elapsed = now - window_start_time;
  uint32_t on_time = (uint32_t)((duty / 100.0f) * (float)SSR_WINDOW_MS);

  if (elapsed < on_time) {
    digitalWrite(PIN_SSR, HIGH);
  } else {
    digitalWrite(PIN_SSR, LOW);
  }
#else
  if (pwm_ssr) {
    pwm_ssr->setPWM(PIN_SSR, (float)PWM_FREQUENCY, duty);
  }
#endif
}

void thermal_control_init() {
  pinMode(PIN_SSR, OUTPUT);
  digitalWrite(PIN_SSR, LOW);
  pinMode(PIN_NTC1, INPUT);
  pinMode(PIN_NTC2, INPUT);
  analogReadResolution(12);

#if !SSR_TIME_PROPORTIONING
  // Initialize RP2040 PWM driver for SSR
  pwm_ssr = new RP2040_PWM(PIN_SSR, PWM_FREQUENCY, 0.0f);
  if (pwm_ssr) {
    pwm_ssr->setPWM();
  }
#endif

  // Initial sensor measurement so system starts with valid temperature
  first_sample = true;
  measure_temperature();
  reference_temp = measured_temp;
  window_start_time = millis();
  last_control_time = millis();
}

/**
 * @brief Reads RP2040 ADC with 32x oversampling and trimmed-mean outlier rejection.
 * Eliminates high-frequency power rail ripple, DVI line noise, and random ADC glitch pulses.
 */
static int read_oversampled_adc(uint8_t pin) {
  // Discard first conversion after multiplexer switch to settle S&H capacitor
  (void)analogRead(pin);

  constexpr int TOTAL_SAMPLES = 32;
  constexpr int TRIM_EACH_SIDE = 6; // Discard 6 highest and 6 lowest outlier readings
  constexpr int KEPT_SAMPLES = TOTAL_SAMPLES - (TRIM_EACH_SIDE * 2); // 20 middle samples

  uint16_t samples[TOTAL_SAMPLES];
  for (int i = 0; i < TOTAL_SAMPLES; i++) {
    samples[i] = (uint16_t)analogRead(pin);
    delayMicroseconds(4);
  }

  // Fast insertion sort on small 32-element array
  for (int i = 1; i < TOTAL_SAMPLES; i++) {
    uint16_t key = samples[i];
    int j = i - 1;
    while (j >= 0 && samples[j] > key) {
      samples[j + 1] = samples[j];
      j--;
    }
    samples[j + 1] = key;
  }

  uint32_t sum = 0;
  for (int i = TRIM_EACH_SIDE; i < TOTAL_SAMPLES - TRIM_EACH_SIDE; i++) {
    sum += samples[i];
  }
  return (int)((sum + (KEPT_SAMPLES / 2)) / KEPT_SAMPLES);
}

float measure_temperature() {
  adc_raw1 = read_oversampled_adc(PIN_NTC1);
  adc_raw2 = read_oversampled_adc(PIN_NTC2);

  float res1 = 0.0f;
  float res2 = 0.0f;
  float raw_t1 = calculate_ntc_temperature(adc_raw1, res1);
  float raw_t2 = calculate_ntc_temperature(adc_raw2, res2);

  measured_resistance1 = res1;
  measured_resistance2 = res2;

  // Ultra-smooth filtering: EMA low-pass (alpha = 0.08) + Physical Slew Limiter
  // Provides stable, continuous temperature tracking with zero sudden multi-degree jumps
  if (first_sample) {
    measured_temp1 = raw_t1;
    measured_temp2 = raw_t2;
    first_sample = false;
  } else {
    constexpr float EMA_ALPHA = 0.08f;
    float target1 = EMA_ALPHA * raw_t1 + (1.0f - EMA_ALPHA) * measured_temp1;
    float target2 = EMA_ALPHA * raw_t2 + (1.0f - EMA_ALPHA) * measured_temp2;

    // Slew rate limit: max 0.25 C change per 100ms (equivalent to 2.5 C / sec max physical rise/fall)
    constexpr float MAX_SLEW_PER_STEP = 0.25f;

    float delta1 = target1 - measured_temp1;
    if (delta1 > MAX_SLEW_PER_STEP) delta1 = MAX_SLEW_PER_STEP;
    if (delta1 < -MAX_SLEW_PER_STEP) delta1 = -MAX_SLEW_PER_STEP;
    measured_temp1 += delta1;

    float delta2 = target2 - measured_temp2;
    if (delta2 > MAX_SLEW_PER_STEP) delta2 = MAX_SLEW_PER_STEP;
    if (delta2 < -MAX_SLEW_PER_STEP) delta2 = -MAX_SLEW_PER_STEP;
    measured_temp2 += delta2;
  }

  // Sensor physical validity bounds (detect disconnected thermistor / short)
  bool ntc1_valid = (measured_temp1 >= NTC_MIN_VALID_TEMP && measured_temp1 <= NTC_MAX_VALID_TEMP);
  bool ntc2_valid = (measured_temp2 >= NTC_MIN_VALID_TEMP && measured_temp2 <= NTC_MAX_VALID_TEMP);

  if (!ntc1_valid || !ntc2_valid) {
    error_state = true;
  }

  // Thermal gradient / sensor divergence check during active heating (debounced)
  if (heater && fabsf(measured_temp1 - measured_temp2) > MAX_NTC_DIFF) {
    divergence_fault_count++;
    if (divergence_fault_count >= 5) {
      error_state = true;
    }
  } else {
    if (divergence_fault_count > 0) {
      divergence_fault_count--;
    }
  }

  // Composite controlled temperature (average of both NTCs)
  measured_temp = (measured_temp1 + measured_temp2) / 2.0f;

  return measured_temp;
}

void thermal_control_update() {
  uint32_t now = millis();

  // 1. Refresh SSR physical output state (called frequently for high timing resolution)
  update_ssr_actuation(now);

  // 2. Control loop rate limiting (runs every CONTROL_PERIOD_MS, e.g. 100 ms / 10 Hz)
  if (now - last_control_time < CONTROL_PERIOD_MS) {
    return;
  }
  uint32_t dt_ms = now - last_control_time;
  last_control_time = now;
  float dt = (float)dt_ms / 1000.0f;
  if (dt > 1.0f) dt = 1.0f; // Clamp delta time in case of scheduling delays

  // Sample sensors
  measure_temperature();

  // Emergency over-temperature shutdown
  if (measured_temp > OVERTEMP_SHUTDOWN || measured_temp1 > OVERTEMP_SHUTDOWN || measured_temp2 > OVERTEMP_SHUTDOWN) {
    error_state = true;
    heater = false;
    duty = 0.0f;
    acc = 0.0f;
    update_ssr_actuation(now);
    return;
  }

  if (heater && !error_state) {
    // Reference ramping (soft-start)
    float target_f = (float)set_temp;
    float max_ramp_step = RAMP_RATE_DEG_PER_SEC * dt;

    if (reference_temp < target_f) {
      reference_temp += max_ramp_step;
      if (reference_temp > target_f) {
        reference_temp = target_f;
      }
    } else if (reference_temp > target_f) {
      reference_temp -= max_ramp_step;
      if (reference_temp < target_f) {
        reference_temp = target_f;
      }
    }

    // PI Controller
    error = reference_temp - measured_temp;

    // Proportional term
    float p_term = KP_GAIN * error;

    // Integral term with time-scaled integration
    acc += error * dt;
    float i_term = KI_GAIN * acc;

    float raw_duty = p_term + i_term;

    // Duty cycle clamping and anti-windup
    if (raw_duty > MAX_DUTY) {
      duty = MAX_DUTY;
      if (error > 0.0f) {
        acc -= error * dt; // Freeze accumulator growth when saturated at upper limit
      }
    } else if (raw_duty < MIN_DUTY) {
      duty = MIN_DUTY;
      if (error < 0.0f) {
        acc -= error * dt; // Freeze accumulator reduction when saturated at lower limit
      }
    } else {
      duty = raw_duty;
    }

    // Thermal runaway safety check:
    // Only enforce minimum temperature rise when driving substantial power
    // and there is an actual temperature deficit to close.
    if (duty >= 20.0f && (reference_temp - measured_temp) > 10.0f) {
      if (now - last_safety_check > SAFETY_PERIOD) {
        last_safety_check = now;
        if ((measured_temp - last_safety_temp) < SAFETY_THRESHOLD) {
          // Temperature failed to rise sufficiently under active heating -> Thermal Error
          error_state = true;
          heater = false;
          duty = 0.0f;
          acc = 0.0f;
        }
        last_safety_temp = measured_temp;
      }
    } else {
      // In steady-state or holding temperature, reset safety baseline timer
      last_safety_check = now;
      last_safety_temp = measured_temp;
    }

  } else {
    // Idle or Error state
    acc = 0.0f;
    duty = 0.0f;
    last_safety_check = now;
    last_safety_temp = measured_temp;
    if (!heater) {
      reference_temp = measured_temp;
    }
  }

  // Refresh SSR output with newly calculated duty
  update_ssr_actuation(now);
}

bool regulator_isr(struct repeating_timer *t) {
  (void)t;
  thermal_control_update();
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
    measure_temperature();
    reference_temp = measured_temp;
    heater_turned_on = millis();
    last_safety_check = millis();
    last_safety_temp = measured_temp;
    window_start_time = millis();
    acc = 0.0f;
  } else {
    duty = 0.0f;
    acc = 0.0f;
    update_ssr_actuation(millis());
  }
}

void reset_error_state() {
  first_sample = true;
  measure_temperature();
  bool ntc1_valid = (measured_temp1 >= NTC_MIN_VALID_TEMP && measured_temp1 <= NTC_MAX_VALID_TEMP);
  bool ntc2_valid = (measured_temp2 >= NTC_MIN_VALID_TEMP && measured_temp2 <= NTC_MAX_VALID_TEMP);

  if (ntc1_valid && ntc2_valid && measured_temp <= OVERTEMP_SHUTDOWN) {
    error_state = false;
    divergence_fault_count = 0;
    acc = 0.0f;
    duty = 0.0f;
    last_safety_check = millis();
    last_safety_temp = measured_temp;
  }
}

float get_measured_temp() {
  return measured_temp;
}

float get_measured_temp_ntc1() {
  return measured_temp1;
}

float get_measured_temp_ntc2() {
  return measured_temp2;
}

float get_ntc_delta() {
  return fabsf(measured_temp1 - measured_temp2);
}

int get_raw_adc() {
  return adc_raw1;
}

int get_raw_adc_ntc1() {
  return adc_raw1;
}

int get_raw_adc_ntc2() {
  return adc_raw2;
}

float get_measured_resistance() {
  return measured_resistance1;
}

float get_measured_resistance_ntc1() {
  return measured_resistance1;
}

float get_measured_resistance_ntc2() {
  return measured_resistance2;
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


