#include "input_handler.h"
#include "display_manager.h"

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
    handle_ui_toggle_heating();
  }

  if (btn_long) {
    btn_long = false;
    if (is_error_state()) {
      reset_error_state();
    }
  }

  // Quadrature Encoder Decoding
  enca = digitalRead(PIN_ENA);
  encb = digitalRead(PIN_ENB);

  if (enca == 1 && lasta == 0 && encb == 0) {
    change_desired_temp(1);
    enc_count = get_desired_temp();
    last_enc = enc_count;
  }
  if (encb == 1 && lastb == 0 && enca == 0) {
    change_desired_temp(-1);
    enc_count = get_desired_temp();
    last_enc = enc_count;
  }
  lasta = enca;
  lastb = encb;

  return true;
}

int get_encoder_count() {
  return get_desired_temp();
}

void set_encoder_count(int count) {
  set_desired_temp(count);
  enc_count = get_desired_temp();
  last_enc = enc_count;
}

void input_handler_update() {
  acquisition_isr(nullptr);
}
