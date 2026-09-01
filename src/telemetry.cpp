#include "telemetry.h"
#include "thermal_control.h"
#include "ui/vars.h"
#include <stdarg.h>

static uint32_t last_telemetry_time = 0;

void log_println(const char *msg) {
  if (msg) {
    Serial.println(msg);
    Serial1.println(msg);
  }
}

void log_printf(const char *fmt, ...) {
  if (!fmt)
    return;
  char buf[256];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buf, sizeof(buf), fmt, args);
  va_end(args);
  log_println(buf);
}

void telemetry_print_banner() {
  log_println(
      "======================================================================");
  log_println("  _____ _____      _    _    ____  __     __ ___  _   _  ___ ");
  log_println(
      " |_   _|| ____|    | |  / \\  / ___| \\ \\   / /|_ _|| \\ | ||_ _|");
  log_println(
      "   | |  |  _|   _  | | / _ \\ \\___ \\  \\ \\ / /  | | |  \\| | | | ");
  log_println(
      "   | |  | |___ | |_| |/ ___ \\ ___) |  \\ V /   | | | |\\  | | | ");
  log_println(
      "   |_|  |_____| \\___//_/   \\_\\____/    \\_/   |___||_| \\_||___|");
  log_println(
      "======================================================================");
  log_println(" Open-Source Heatplate Controller for SMT Reflow Soldering");
  log_printf(" Firmware:    %s (%s)", FIRMWARE_NAME, FIRMWARE_VERSION);
  log_printf(" Build Date:  %s %s", __DATE__, __TIME__);
  log_printf(" Author:      %s", FIRMWARE_AUTHOR);
  log_printf(" GitHub:      %s", FIRMWARE_GITHUB);
  log_printf(" MCU / Freq:  RP2040 @ %lu MHz | Free Heap: %lu B",
             (unsigned long)(rp2040.f_cpu() / 1000000),
             (unsigned long)rp2040.getFreeHeap());
  log_printf(" Telemetry:   USB CDC (Serial) & UART0 (Serial1 @ %d baud)",
             SERIAL_BAUD);
  log_println(
      "======================================================================");
}

void telemetry_init() {
  Serial.begin(SERIAL_BAUD);
  Serial1.setRX(SERIAL_RX);
  Serial1.setTX(SERIAL_TX);
  Serial1.begin(SERIAL_BAUD);

  // Wait up to 2.5s for USB CDC Serial Monitor to connect after reset/reboot
  uint32_t start = millis();
  while (!Serial && (millis() - start < 2500)) {
    delay(10);
  }
  delay(150); // Allow host terminal buffer to settle

  telemetry_print_banner();
}

void telemetry_update() {
  // Check for interactive user commands from Serial or Serial1 (press Enter,
  // 'b', or '?' to reprint banner)
  if (Serial.available()) {
    bool trigger = false;
    while (Serial.available()) {
      char c = (char)Serial.read();
      if (c == 'b' || c == 'B' || c == 'h' || c == 'H' || c == '?' ||
          c == '\n' || c == '\r') {
        trigger = true;
      }
    }
    if (trigger) {
      telemetry_print_banner();
    }
  }
  if (Serial1.available()) {
    bool trigger = false;
    while (Serial1.available()) {
      char c = (char)Serial1.read();
      if (c == 'b' || c == 'B' || c == 'h' || c == 'H' || c == '?' ||
          c == '\n' || c == '\r') {
        trigger = true;
      }
    }
    if (trigger) {
      telemetry_print_banner();
    }
  }

  uint32_t now = millis();
  if (now - last_telemetry_time < TELEMETRY_PERIOD) {
    return;
  }
  last_telemetry_time = now;

  // Telemetry reads the continuously filtered temperatures updated by
  // thermal_control_update()
  float meas = get_measured_temp();
  float temp1 = get_measured_temp_ntc1();
  float temp2 = get_measured_temp_ntc2();
  float delta = get_ntc_delta();
  int raw_adc1 = get_raw_adc_ntc1();
  int raw_adc2 = get_raw_adc_ntc2();
  float res1 = get_measured_resistance_ntc1();
  float res2 = get_measured_resistance_ntc2();
  int set = get_desired_temp();
  float ref = get_reference_temp();
  float duty = get_duty_cycle();

  const char *profile_str = get_var_profile_str();
  const char *status_str = get_var_status();
  if (!profile_str)
    profile_str = "MANUAL";
  if (!status_str)
    status_str = "IDLE";

  char res1_buf[16];
  char res2_buf[16];
  if (res1 >= 1000.0f) {
    snprintf(res1_buf, sizeof(res1_buf), "%.1fk", res1 / 1000.0f);
  } else {
    snprintf(res1_buf, sizeof(res1_buf), "%.0fR", res1);
  }
  if (res2 >= 1000.0f) {
    snprintf(res2_buf, sizeof(res2_buf), "%.1fk", res2 / 1000.0f);
  } else {
    snprintf(res2_buf, sizeof(res2_buf), "%.0fR", res2);
  }

  // Structured, tagged, and human-readable periodic telemetry log
  char buf[256];
  snprintf(buf, sizeof(buf),
           "[Telemetry] Temp: %.1fC (T1: %.1f, T2: %.1f, dT: %.1f) | "
           "Target: %dC (Ref: %.1f) | Duty: %.1f%% | "
           "Status: %s [%s] | ADC: [%d/%s, %d/%s] | Heap: %luB",
           meas, temp1, temp2, delta, set, ref, duty, status_str, profile_str,
           raw_adc1, res1_buf, raw_adc2, res2_buf,
           (unsigned long)rp2040.getFreeHeap());
  log_println(buf);
}
