#include "telemetry.h"

static uint32_t last_telemetry_time = 0;

void telemetry_init() {
  Serial1.setRX(SERIAL_RX);
  Serial1.setTX(SERIAL_TX);
  Serial1.begin(SERIAL_BAUD);
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

  const char* status_str = "IDLE";
  if (status == STATUS_HEATING) status_str = "HEATING";
  else if (status == STATUS_NTC_ERROR) status_str = "NTC_ERROR";

  Serial1.print("ReferenceTemp:");
  Serial1.print(ref, 2);
  Serial1.print(",MeasuredTemp:");
  Serial1.print(meas, 2);
  Serial1.print(",TargetTemp:");
  Serial1.print(set);
  Serial1.print(",Duty:");
  Serial1.print(duty, 2);
  Serial1.print(",Status:");
  Serial1.println(status_str);
}
