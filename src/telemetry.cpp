#include "telemetry.h"

static uint32_t last_telemetry_time = 0;

void telemetry_init() {
  Serial.begin(SERIAL_BAUD);
  Serial1.setRX(SERIAL_RX);
  Serial1.setTX(SERIAL_TX);
  Serial1.begin(SERIAL_BAUD);
  Serial.println("=== Tejasvini Firmware Initialized ===");
  Serial1.println("=== Tejasvini Firmware Initialized ===");
}

void telemetry_update() {
  uint32_t now = millis();
  if (now - last_telemetry_time < TELEMETRY_PERIOD) {
    return;
  }
  last_telemetry_time = now;

  // Sample NTC temperature (guarantees update even if timer ISR is inactive)
  measure_temperature();

  float meas = get_measured_temp();
  int raw_adc = get_raw_adc();
  float res = get_measured_resistance();
  int set = get_desired_temp();
  float ref = get_reference_temp();
  float duty = get_duty_cycle();
  HeatbedStatus status = get_system_status();

  const char *status_str = "IDLE";
  if (status == STATUS_HEATING)
    status_str = "HEATING";
  else if (status == STATUS_NTC_ERROR)
    status_str = "NTC_ERROR";

  String logLine = "NTC ADC: " + String(raw_adc) +
                   ", Res: " + String(res, 1) + " Ohm" +
                   ", Temp: " + String(meas, 1) + " C" +
                   ", Ref: " + String(ref, 1) + " C" +
                   ", Target: " + String(set) + " C" +
                   ", Duty: " + String(duty, 1) + "%" +
                   ", Status: " + String(status_str) +
                   ", Heap: " + String(rp2040.getFreeHeap()) + "B";
  Serial.println(logLine);
  Serial1.println(logLine);
}

