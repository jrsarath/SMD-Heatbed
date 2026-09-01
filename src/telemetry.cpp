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
  float temp1 = get_measured_temp_ntc1();
  float temp2 = get_measured_temp_ntc2();
  int raw_adc1 = get_raw_adc_ntc1();
  int raw_adc2 = get_raw_adc_ntc2();
  float res1 = get_measured_resistance_ntc1();
  float res2 = get_measured_resistance_ntc2();
  int set = get_desired_temp();
  float ref = get_reference_temp();
  float duty = get_duty_cycle();
  HeatbedStatus status = get_system_status();

  const char *status_str = "IDLE";
  if (status == STATUS_HEATING)
    status_str = "HEATING";
  else if (status == STATUS_NTC_ERROR)
    status_str = "NTC_ERROR";

  String logLine = "NTC1: " + String(temp1, 1) + "C (ADC:" + String(raw_adc1) + ", " + String(res1, 0) + "R) | " +
                   "NTC2: " + String(temp2, 1) + "C (ADC:" + String(raw_adc2) + ", " + String(res2, 0) + "R) | " +
                   "Avg: " + String(meas, 1) + "C, Ref: " + String(ref, 1) + "C, Target: " + String(set) + "C, " +
                   "Duty: " + String(duty, 1) + "%, Status: " + String(status_str) +
                   ", Heap: " + String(rp2040.getFreeHeap()) + "B";
  Serial.println(logLine);
  Serial1.println(logLine);
}

