#include "telemetry.h"

static uint32_t last_telemetry_time = 0;

void telemetry_init() {
  Serial.begin(SERIAL_BAUD);
  Serial1.setRX(SERIAL_RX);
  Serial1.setTX(SERIAL_TX);
  Serial1.begin(SERIAL_BAUD);
  Serial.println("=== SMD Heatbed Firmware Initialized ===");
  Serial1.println("=== SMD Heatbed Firmware Initialized ===");
}

void telemetry_update() {
  uint32_t now = millis();
  if (now - last_telemetry_time < TELEMETRY_PERIOD) {
    return;
  }
  last_telemetry_time = now;

  float meas = get_measured_temp();
  int set = get_desired_temp();
  float ref = get_reference_temp();
  float duty = get_duty_cycle();
  HeatbedStatus status = get_system_status();

  const char *status_str = "IDLE";
  if (status == STATUS_HEATING)
    status_str = "HEATING";
  else if (status == STATUS_NTC_ERROR)
    status_str = "NTC_ERROR";

  String logLine = "Ref:" + String(ref, 1) + " C, Meas:" + String(meas, 1) +
                   " C, Target:" + String(set) + " C, Duty:" + String(duty, 1) +
                   "%, Status:" + String(status_str) +
                   ", Heap:" + String(rp2040.getFreeHeap()) + "B";
  Serial.println(logLine);
  Serial1.println(logLine);
}

