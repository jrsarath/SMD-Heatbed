#include "input_handler.h"
#include "display_manager.h"
#include "telemetry.h"

static uint32_t btn_press_time = 0;
static uint8_t last_btn_state = 1;

static int enca = 0;
static int encb = 0;
static int lasta = 1;
static int lastb = 1;

void input_init() {
  // Configure encoder pins with internal pullup resistors to avoid floating inputs
  pinMode(PIN_ENA, INPUT_PULLUP);
  pinMode(PIN_ENB, INPUT_PULLUP);
  pinMode(PIN_EBT, INPUT_PULLUP);

  lasta = digitalRead(PIN_ENA);
  lastb = digitalRead(PIN_ENB);
  last_btn_state = digitalRead(PIN_EBT);

  log_printf("[Input] Rotary encoder & button initialized with pullups (ENA: GPIO %d, ENB: GPIO %d, EBT: GPIO %d).",
             PIN_ENA, PIN_ENB, PIN_EBT);
}

bool acquisition_isr(struct repeating_timer *t) {
  (void)t;

  // 1. Push-Button Reading & Debouncing (Active LOW with internal pullup)
  int current_btn = digitalRead(PIN_EBT);

  // Button pressed transition (1 -> 0)
  if (current_btn == 0 && last_btn_state == 1) {
    last_btn_state = 0;
    btn_press_time = millis();
  }
  // Button released transition (0 -> 1)
  else if (current_btn == 1 && last_btn_state == 0) {
    last_btn_state = 1;
    uint32_t hold_duration = millis() - btn_press_time;
    if (hold_duration >= BTN_LONG_PRESS) {
      log_println("[Input] Encoder button LONG press -> Requesting error state reset.");
      if (is_error_state()) {
        reset_error_state();
      }
    } else if (hold_duration >= BTN_SHORT_PRESS) {
      log_println("[Input] Encoder button SHORT press -> Toggling heater / action.");
      handle_ui_toggle_heating();
    }
  }

  // 2. Quadrature Encoder Decoding (Phase A edge detection)
  enca = digitalRead(PIN_ENA);
  encb = digitalRead(PIN_ENB);

  if (enca != lasta) {
    if (enca == 1) { // Rising edge on Phase A
      if (encb == 0) {
        change_desired_temp(1);
      } else {
        change_desired_temp(-1);
      }
    }
    lasta = enca;
  }
  lastb = encb;

  return true;
}

int get_encoder_count() {
  return get_desired_temp();
}

void set_encoder_count(int count) {
  set_desired_temp(count);
}

void input_handler_update() {
  acquisition_isr(nullptr);
}
