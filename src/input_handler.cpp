#include "input_handler.h"

static volatile int btn_press_time = 0;
static volatile int last_btn_state = 1;
static volatile bool btn_short = false;
static volatile bool btn_long = false;

static volatile int enca = 0;
static volatile int encb = 0;
static volatile int lasta = 0;
static volatile int lastb = 0;
static volatile int enc_count = 0;
static volatile int last_enc = 0;

void input_init() {
  pinMode(PIN_ENA, INPUT);
  pinMode(PIN_ENB, INPUT);
  pinMode(PIN_EBT, INPUT);

  // Turn pullup resistors on
  digitalWrite(PIN_ENA, HIGH);
  digitalWrite(PIN_ENB, HIGH);
}

bool acquisition_isr(struct repeating_timer *t) {
  (void)t;

  // Push-Button Reading & Debouncing
  int current_btn = digitalRead(PIN_EBT);

  // Button pressed (Active LOW)
  if (current_btn == 0 && last_btn_state == 1) {
    last_btn_state = 0;
    btn_press_time = millis();
  }

  // Button released
  if (current_btn == 1 && last_btn_state == 0) {
    last_btn_state = 1;
    uint32_t hold_duration = millis() - btn_press_time;
    if (hold_duration >= BTN_LONG_PRESS) {
      btn_long = true;
    } else if (hold_duration >= BTN_SHORT_PRESS) {
      btn_short = true;
    }
  }

  // Handle button actions
  if (btn_short) {
    btn_short = false;
    toggle_heater();
  }

  if (btn_long) {
    btn_long = false;
    if (is_error_state()) {
      // Re-enable controller from error state if desired
    }
  }

  // Quadrature Encoder Decoding
  enca = digitalRead(PIN_ENA);
  encb = digitalRead(PIN_ENB);

  if (enca == 1 && lasta == 0 && encb == 0) enc_count++;
  if (encb == 1 && lastb == 0 && enca == 0) enc_count--;
  lasta = enca;
  lastb = encb;

  // Sync with desired temperature setpoint when changed
  if (enc_count != last_enc) {
    last_enc = enc_count;
    if (enc_count < MIN_TEMP) enc_count = MIN_TEMP;
    if (enc_count > MAX_TEMP) enc_count = MAX_TEMP;
    set_desired_temp(enc_count);
  } else {
    int desired = get_desired_temp();
    if (enc_count != desired) {
      enc_count = desired;
      last_enc = enc_count;
    }
  }

  return true;
}

int get_encoder_count() {
  return enc_count;
}

void set_encoder_count(int count) {
  enc_count = count;
  last_enc = count;
}
