#include <PicoDVI.h>
#include <lvgl.h>
#include <Wire.h>
#include "touch.h"
#include "RPi_Pico_TimerInterrupt.h"
#include "RP2040_PWM.h"
#include "ui.h"

// PINS
#define PIN_ENA 2
#define PIN_ENB 3
#define PIN_EBT 27
#define PIN_SSR 22
#define PIN_NTC 28

// PARAMETERS
#define BTN_SHORT_PRESS   100     // [ms]
#define BTN_LONG_PRESS    1000    // [ms]
#define PWM_FREQUENCY     1000    // [Hz]
#define MIN_TEMP          0       // [C]
#define MAX_TEMP          250     // [C]
#define R                 2200    // [Ohm]
#define R0                100000  // [Ohm]
#define BETA              3950    // [#]
#define T0                298.15  // [K]
#define E                 2.71828 // [#]
#define REF_STEP          0.05    // [C]
#define MAX_DUTY          40      // [%]
#define MIN_DUTY          0       // [%]
#define LCD_PERIOD        1000    // [ms]
#define SAFETY_PERIOD     18000   // [ms]
#define SAFETY_THRESHOLD  2       // [C]

// Screen Dimension
#define screenWidth     320
#define screenHeight    240

static lv_disp_draw_buf_t draw_buf;
static lv_color_t disp_draw_buf1[screenWidth * screenHeight / 10];
static lv_disp_drv_t disp_drv;

DVIGFX16 display(DVI_RES_320x240p60, picodvi_dvi_cfg);

RPI_PICO_Timer      TimerMain(0);     
RPI_PICO_Timer      TimerLED(1);      // Timer for the heartbeat LED                          - Frequency set in setup() - Default 10 Hz 
RPI_PICO_Timer      TimerAcqusition(2);
RPI_PICO_Timer      TimerLCD(3);
RP2040_PWM*         PWM_Instance[1];  // PWM for the Pico


byte Degrees[8] = {
  0b01110,
  0b01010,
  0b01110,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

float duty = 0.00;
float kp = 0.2;
float ki = 0.00001;
volatile float acc = 0.00;
volatile float error = 0.00;

// Encoder Variables
int btn_hold_time = 0;
volatile int btn_press_time = 0;
volatile int last_btn_state = 0;
bool btn_long = false;
bool btn_short = false;
volatile int enca = 0;
volatile int encb = 0;
volatile int lasta = 0;
volatile int lastb = 0;
volatile int enc_count = 0;
volatile int last_enc = 0;

// LCD Variables
bool init_done = false;
bool updateLCDmeasure = false;
volatile int last_update = 0;

// Temperature Variables
volatile int    set_temp            = 0;
volatile float  reference_temp      = 0.00;
volatile float  measured_temp       = 0.00;
volatile float  measured_resistance = 0.00;
volatile int    adc_raw             = 0;
volatile int    temp_reading        = 0;
volatile int    last_measured_temp  = 0;

// Heater Variables
bool heater = false;
int heater_turned_on = 0;

// Safety Variables
float last_safety_temp  = 0.00;
int last_safety_check = 0;
bool error_state = false;

// UI update flags/values (set from ISRs, consumed in main loop)
volatile int ui_status_state = 0; // 0=idle, 1=heating, 2=ntc_error
volatile int ui_temp_to_display = 0; // arc / measured temp
volatile int ui_set_temp_to_display = 0; // desired temp label
volatile bool ui_needs_update = false;

/**
 * @brief Toggles the heater state
 * 
 */
void toggleHeater() {
  if (heater == false) {
    Serial1.println("Heater turned ON");
    heater_turned_on = millis();
    last_safety_check = millis();
    lv_obj_add_state(ui_Switch1, LV_STATE_CHECKED);
    heater = true;
  } else {
    Serial1.println("Heater turned OFF");
    lv_obj_clear_state(ui_Switch1, LV_STATE_CHECKED);
    heater = false;
  }
  return;
}

/**
 * @brief Set the desired temperature directly (degrees C)
 *
 * This updates the global `set_temp` and `enc_count`, clamps to
 * `MIN_TEMP`/`MAX_TEMP`, and updates the UI label if initialized.
 * 
 * @param temp Desired temperature in degrees Celsius
 */
void setDesiredTemp(int temp) {
  if (temp < MIN_TEMP) temp = MIN_TEMP;
  if (temp > MAX_TEMP) temp = MAX_TEMP;

  set_temp = temp;
  enc_count = temp;

  if (init_done) {
    lv_label_set_text(ui_Label1, String(set_temp).c_str());
  }
}

/**
 * @brief Change desired temperature by delta (can be negative)
 */
static void changeDesiredTempBy(int delta) {
  int newTemp = set_temp + delta;
  setDesiredTemp(newTemp);
}

/**
 * @brief Increase desired temperature by 1
 */
void incDesiredTemp() {
  changeDesiredTempBy(1);
}

/**
 * @brief Decrease desired temperature by 1
 */
void decDesiredTemp() {
  changeDesiredTempBy(-1);
}

/**
 * @brief Measures the temperature from the NTC thermistor
 * 
 * @return int 
 */
int measureTemp() {
  // Raw reading from the ADC of the NTC voltage divider
  adc_raw = analogRead(PIN_NTC);
  // Calculating the resistance of the NTC
  measured_resistance = R * (4086.00 / adc_raw - 1);
  // Calculating the temperature from the measured resistance of the NTC
  measured_temp = BETA / log (measured_resistance / (R0 * pow(E, - BETA / T0))) - 273.15;
  // Returning the measured temperature
  bool test = false;
  if (test == true) {
    Serial1.print("ADC Reading: ");
    Serial1.println(adc_raw);
    Serial1.print("Measured Resistance: ");
    Serial1.println(measured_resistance);
    Serial1.print("Measured Temperature: ");
    Serial1.println(measured_temp);
  } 
  // Return the temperature and exit the function
  return int(measured_temp);
}

/**
 * @brief Handles the regulator logic for temperature control
 * 
 * @param t 
 * @return true 
 * @return false 
 */
bool regulatorHandler(struct repeating_timer *t) {
  (void) t;
  // Measure the temperature
  temp_reading = measureTemp();
  
  if (heater == true && error_state == false) {
    // Updating the status message
    // Request UI update (do UI operations in main loop, not in ISR)
    ui_status_state = 1; // heating
    ui_needs_update = true;


    // Updating the reference temperature
    if (set_temp > reference_temp) reference_temp += REF_STEP;
    if (set_temp < reference_temp) reference_temp = set_temp;
    
    // PI controller
    // Calculate the error
    error = reference_temp - measured_temp;
    
    // Update the accumulator
    acc += error;
    
    // Calculate the duty cycle for the PWM
    duty = kp * error + ki * acc;

    if (error < 10 && millis() - heater_turned_on > 10000) duty = 0;
    if (error < 5 && millis() - heater_turned_on < 10000) duty = 0;
    
    // Overshoot regulation
    if (duty > MAX_DUTY) {
      duty = MAX_DUTY;
      acc -= error;
    }
    
    // Undershoot regulation
    if (duty < MIN_DUTY) {
      duty = MIN_DUTY;
      acc -= error;
    }

    // Reset the safety check timer if the duty cycle is at 0%
    if (duty == MIN_DUTY) last_safety_check = millis();

    // Safety check
    if (millis() - last_safety_check > SAFETY_PERIOD) {
      last_safety_check = millis();
      if (measured_temp - last_safety_temp < SAFETY_THRESHOLD) {
        // This is the case where the temperature hasn't increased, and we need to go into the error state
        error_state = true;
        // Request UI update (do UI operations in main loop, not in ISR)
        ui_status_state = 2; // ntc error
        ui_needs_update = true;

        // Reset the duty to 0% 
        duty = 0.00;
        acc = 0;
      }
      last_safety_temp = measured_temp;
    }

    // Update the PWM
    PWM_Instance[0]->setPWM(PIN_SSR, PWM_FREQUENCY, duty);
    
  } else if (error_state == false) {
    // Updating the status message
    // Request UI update (do UI operations in main loop, not in ISR)
    ui_status_state = 0; // idle
    ui_needs_update = true;
    // Reset the accumulator for the PI controller
    acc = 0;
    // Reset the duty cycle
    duty = 0;
    // Update the safety check timer
    last_safety_check = millis();
  }
  return true;
}

/**
 * @brief Handles the printing of data to the Serial Monitor
 * 
 * @param t 
 * @return true 
 * @return false 
 */
bool printHandler(struct repeating_timer *t) {
  (void) t;
  // Serial1.print("ReferenceTemp:");
  // Serial1.print(reference_temp);
  // Serial1.print(",MeasuredTemp:");
  // Serial1.print(measured_temp);
  // Serial1.print(",");
  // Serial1.print("Duty:");
  // Serial1.print(duty);
  // Serial1.println("");
  if (last_measured_temp != temp_reading && millis() - last_update > LCD_PERIOD) {
    last_measured_temp = temp_reading;
    last_update = millis();
    // Request UI update instead of calling LVGL from ISR
    ui_temp_to_display = temp_reading;
    ui_needs_update = true;
  }
  return true;
}

/**
 * @brief 
 * 
 * @param t 
 * @return true 
 * @return false 
 */
bool LCDHandler(struct repeating_timer *t) {
  (void) t;
  //if (mos_flag == true) updateLCDmeasure = true;
  return true;
}

/**
 * @brief Handles the acquisition of input data from the encoder and button
 * 
 * @param t 
 * @return true 
 * @return false 
 */
bool acquisitionHandler(struct repeating_timer *t) {
  (void) t;

  // Encoder Button Reading

  // This is the case where the button is pushed
  if (digitalRead(PIN_EBT) == 0 && last_btn_state == 0) {
    last_btn_state = 1;
    btn_press_time = millis();
  }

  // This is the case where the button is released
  if (digitalRead(PIN_EBT) == 1 && last_btn_state == 1) {
    // Update last button state
    last_btn_state = 0;
    if (millis() - btn_press_time >= BTN_LONG_PRESS) {
      Serial1.println("Button LONG press.");
      btn_long = true;
    } else if (millis() - btn_press_time >= BTN_SHORT_PRESS) {
      Serial1.println("Button SHORT press.");
      btn_short = true;
    }
  }

  if (btn_short == true) {
    btn_short = false;
    toggleHeater();
  }

  // Encoder rotation
  enca = digitalRead(PIN_ENA);
  encb = digitalRead(PIN_ENB);
  
  if (enca == 1 && lasta == 0 && encb == 0) enc_count++;
  if (encb == 1 && lastb == 0 && enca == 0) enc_count--;
  lasta = enca;
  lastb = encb;
  
  // LCD Updating
  if (enc_count != last_enc) {
    last_enc = enc_count;
    set_temp = enc_count;
    if (set_temp < MIN_TEMP) set_temp = MIN_TEMP;
    if (set_temp > MAX_TEMP) set_temp = MAX_TEMP;

    // Request UI update instead of calling LVGL from ISR
    ui_set_temp_to_display = set_temp;
    ui_needs_update = true;
  }
  
  return true;
}

/**
 * @brief Flushes the content of the internal buffer to the display
 * 
 * @param disp 
 * @param area 
 * @param color_p 
 */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
   uint32_t w = ( area->x2 - area->x1 + 1 );
   uint32_t h = ( area->y2 - area->y1 + 1 );

   display.drawRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
   lv_disp_flush_ready( disp );
}

/**
 * @brief Reads the touchpad input and updates the input device data
 * 
 * @param indev_driver 
 * @param data 
 */
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  if (touch_has_signal()) {
    if (touch_touched()) {
      data->state = LV_INDEV_STATE_PRESSED;

      // Set the coordinates
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
      // avoid heavy serial printing here (called from LVGL polling)
    } else if (touch_released()) {
      data->state = LV_INDEV_STATE_RELEASED;
    }
  } else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

/**
 * @brief Setup function
 * 
 */
void setup() {
  Serial1.setRX(1);
  Serial1.setTX(0);
  Serial1.begin(115200);
  Serial1.println("Beginning setup");

  // PINS Setup
  pinMode(24, OUTPUT);
  pinMode(PIN_ENA, INPUT);
  pinMode(PIN_ENB, INPUT);
  pinMode(PIN_EBT, INPUT);
  pinMode(PIN_SSR, OUTPUT);
  pinMode(PIN_NTC, INPUT);
  
  // Pullups
  digitalWrite(PIN_ENA, HIGH); // Turn pullup resistor on
  digitalWrite(PIN_ENB, HIGH); // Turn pullup resistor on
  digitalWrite(24, LOW); // Enable backlight

  // LED Timer - Frequency set in the Parameters section
  if (TimerMain.attachInterruptInterval(2000, regulatorHandler)) {
    Serial1.print("Starting LED Timer OK, millis() = ");
    Serial1.println(String(millis()));
  } else {
    Serial1.println("Can't set LED Timer. Select another freq. or timer");
  }

  // LED Timer - Frequency set in the Parameters section
  if (TimerLED.attachInterruptInterval(10000, printHandler)) {
    Serial1.print("Starting LED Timer OK, millis() = ");
    Serial1.println(String(millis()));
  } else {
    Serial1.println("Can't set LED Timer. Select another freq. or timer");
  }

  // Acquisition Timer - Frequency set in the Parameters section
  if (TimerAcqusition.attachInterruptInterval(200, acquisitionHandler)) {
    Serial1.print("Starting Acquisition Timer OK, millis() = ");
    Serial1.println(String(millis()));
  } else {
    Serial1.println("Can't set LED Timer. Select another freq. or timer");
  }

  // LED Timer - Frequency set in the Parameters section
  if (TimerLCD.attachInterruptInterval(300000, LCDHandler)) {
    Serial1.print("Starting LED Timer OK, millis() = ");
    Serial1.println(String(millis()));
  } else {
    Serial1.println("Can't set LED Timer. Select another freq. or timer");
  }

  analogReadResolution(12);

  // Setting up PWM
  PWM_Instance[0] = new RP2040_PWM(PIN_SSR, PWM_FREQUENCY, 0.00f);
  PWM_Instance[0]->setPWM();


  // LCD Init
  display.begin();
  Serial1.println("Display setup");

  // Touch Init
  touch_init(320, 240);
  Serial1.println("Touch setup");
  
  // Takes effect on next drawing command
  display.setRotation(0);

  // LVGL Init
  lv_init();
  Serial1.println("LVGL setup");
  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf1, NULL, screenWidth * screenHeight / 10 );
  
  // Initialize the display
  lv_disp_drv_init(&disp_drv);

  // Change the following line to your display resolution
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.full_refresh = 0;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  // Initialize the (dummy) input device driver
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  // lv_demo_widgets();
  ui_init();
  Serial1.println("UI setup");

  init_done = true;
  Serial1.println( "Setup finished" );
}

/**
 * @brief Main loop
 * 
 */
void loop() {
  lv_timer_handler();

  // Perform UI updates here (safe, non-ISR context)
  if (init_done && ui_needs_update) {
    // copy volatile values to locals
    int status = ui_status_state;
    int disp_temp = ui_temp_to_display;
    int disp_set = ui_set_temp_to_display;

    // clear flag early to avoid missing new requests while updating
    ui_needs_update = false;

    static int last_displayed_temp = -32768;
    static int last_displayed_set = -32768;
    static int last_status = -1;

    // Update measured temperature (arc + label6) only if changed
    if (disp_temp != last_displayed_temp) {
      lv_arc_set_value(ui_Arc2, disp_temp);
      lv_label_set_text(ui_Label6, String(disp_temp).c_str());
      last_displayed_temp = disp_temp;
    }

    // Update desired/set temperature label only if changed
    if (disp_set != last_displayed_set) {
      lv_label_set_text(ui_Label1, String(disp_set).c_str());
      last_displayed_set = disp_set;
    }

    // Update status (Label9 / Image / styles) only if changed
    if (status != last_status) {
      if (status == 1) {
        lv_label_set_text(ui_Label9, "Heating");
        lv_img_set_src(ui_Image1, &ui_img_heating_png);
        ui_object_set_themeable_style_property(ui_Container9, LV_PART_MAIN| LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR, _ui_theme_color_danger);
        ui_object_set_themeable_style_property(ui_Label9, LV_PART_MAIN| LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR, _ui_theme_color_danger);
      } else if (status == 2) {
        lv_label_set_text(ui_Label9, "NTC Error");
        lv_img_set_src(ui_Image1, &ui_img_alert_png);
        ui_object_set_themeable_style_property(ui_Container9, LV_PART_MAIN| LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR, _ui_theme_color_danger);
        ui_object_set_themeable_style_property(ui_Label9, LV_PART_MAIN| LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR, _ui_theme_color_danger);
      } else {
        lv_label_set_text(ui_Label9, "Idle");
        lv_img_set_src(ui_Image1, &ui_img_sleeping_png);
        ui_object_set_themeable_style_property(ui_Container9, LV_PART_MAIN| LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR, _ui_theme_color_info);
        ui_object_set_themeable_style_property(ui_Label9, LV_PART_MAIN| LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR, _ui_theme_color_info);
      }
      last_status = status;
    }
  }

  delay(5);
}


