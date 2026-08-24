#ifndef TOUCH_H_
#define TOUCH_H_

#include <Arduino.h>

/*******************************************************************************
 * Touch libraries:
 * FT6X36: https://github.com/strange-v/FT6X36.git
 * GT911: https://github.com/TAMCTec/gt911-arduino.git
 * XPT2046: https://github.com/PaulStoffregen/XPT2046_Touchscreen.git
 ******************************************************************************/

/* uncomment for FT6X36 */
// #define TOUCH_FT6X36
// #define TOUCH_FT6X36_SCL 21
// #define TOUCH_FT6X36_SDA 20
// #define TOUCH_FT6X36_INT -1
// #define TOUCH_SWAP_XY
// #define TOUCH_MAP_X1 400
// #define TOUCH_MAP_X2 0
// #define TOUCH_MAP_Y1 0
// #define TOUCH_MAP_Y2 240

/* uncomment for GT911 */
#define TOUCH_GT911
#define TOUCH_GT911_SCL 21
#define TOUCH_GT911_SDA 20
#define TOUCH_GT911_INT 25
#define TOUCH_GT911_RST 29
#define TOUCH_GT911_ROTATION ROTATION_NORMAL
#define TOUCH_MAP_X1 800
#define TOUCH_MAP_X2 0
#define TOUCH_MAP_Y1 480
#define TOUCH_MAP_Y2 0

static uint16_t touchWidth = 240;
static uint16_t touchHeight = 320;

inline int touch_last_x = 0;
inline int touch_last_y = 0;

#if defined(TOUCH_FT6X36)
#include <FT6X36.h>
#include <Wire.h>
static FT6X36 ts(&Wire, TOUCH_FT6X36_INT);
static bool touch_touched_flag = true, touch_released_flag = true;

#elif defined(TOUCH_GT911)
#include <TAMC_GT911.h>
#include <Wire.h>
static TAMC_GT911 ts = TAMC_GT911(
    TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT, TOUCH_GT911_RST,
    max(TOUCH_MAP_X1, TOUCH_MAP_X2), max(TOUCH_MAP_Y1, TOUCH_MAP_Y2));

#elif defined(TOUCH_XPT2046)
#include <SPI.h>
#include <XPT2046_Touchscreen.h>
static XPT2046_Touchscreen ts(TOUCH_XPT2046_CS, TOUCH_XPT2046_INT);
#endif

#if defined(TOUCH_FT6X36)
inline void touch(TPoint p, TEvent e) {
  if (e != TEvent::Tap && e != TEvent::DragStart && e != TEvent::DragMove &&
      e != TEvent::DragEnd) {
    return;
  }

#if defined(TOUCH_SWAP_XY)
  touch_last_x = map(p.y, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, touchWidth);
  touch_last_y = map(p.x, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, touchHeight);
#else
  touch_last_x = map(p.x, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, touchWidth);
  touch_last_y = map(p.y, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, touchHeight);
#endif

  switch (e) {
  case TEvent::Tap:
    touch_touched_flag = true;
    touch_released_flag = true;
    break;
  case TEvent::DragStart:
  case TEvent::DragMove:
    touch_touched_flag = true;
    break;
  case TEvent::DragEnd:
    touch_released_flag = true;
    break;
  default:
    break;
  }
}
#endif

/**
 * @brief Initializes the touch controller with the given screen dimensions
 */
inline void touch_init(uint16_t width, uint16_t height) {
  touchWidth = width;
  touchHeight = height;
#if defined(TOUCH_FT6X36)
  Wire.setSDA(TOUCH_FT6X36_SDA);
  Wire.setSCL(TOUCH_FT6X36_SCL);
  Wire.begin();
  ts.begin();
  ts.registerTouchHandler(touch);

#elif defined(TOUCH_GT911)
  ts.begin();
  ts.setRotation(TOUCH_GT911_ROTATION);

#elif defined(TOUCH_XPT2046)
  SPI.begin(TOUCH_XPT2046_SCK, TOUCH_XPT2046_MISO, TOUCH_XPT2046_MOSI,
            TOUCH_XPT2046_CS);
  ts.begin();
  ts.setRotation(TOUCH_XPT2046_ROTATION);
#endif
}

/**
 * @brief Checks if the touch controller has detected any touch signal
 */
inline bool touch_has_signal() {
#if defined(TOUCH_FT6X36)
  ts.loop();
  return touch_touched_flag || touch_released_flag;
#elif defined(TOUCH_GT911)
  return true;
#elif defined(TOUCH_XPT2046)
  return ts.tirqTouched();
#else
  return false;
#endif
}

/**
 * @brief Checks if the touch controller has detected a touch event
 */
inline bool touch_touched() {
#if defined(TOUCH_FT6X36)
  if (touch_touched_flag) {
    touch_touched_flag = false;
    return true;
  }
  return false;

#elif defined(TOUCH_GT911)
  ts.read();
  if (ts.isTouched) {
    int16_t rx = ts.points[0].x;
    int16_t ry = ts.points[0].y;

    static uint32_t last_raw_log = 0;
    if (millis() - last_raw_log > 200) {
      last_raw_log = millis();
      String rawMsg = "[Raw Touch] isTouched: " + String(ts.isTouched) +
                      " touches: " + String(ts.touches) + " rx: " + String(rx) +
                      " ry: " + String(ry);
      Serial.println(rawMsg);
      Serial1.println(rawMsg);
    }

#if defined(TOUCH_SWAP_XY)
    touch_last_x = map(ry, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, touchWidth - 1);
    touch_last_y = map(rx, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, touchHeight - 1);
#else
    touch_last_x = map(rx, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, touchWidth - 1);
    touch_last_y = map(ry, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, touchHeight - 1);
#endif

    touch_last_x = constrain(touch_last_x, 0, touchWidth - 1);
    touch_last_y = constrain(touch_last_y, 0, touchHeight - 1);

    return true;
  }
  return false;

#elif defined(TOUCH_XPT2046)
  if (ts.touched()) {
    TS_Point p = ts.getPoint();
#if defined(TOUCH_SWAP_XY)
    touch_last_x = map(p.y, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, touchWidth - 1);
    touch_last_y = map(p.x, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, touchHeight - 1);
#else
    touch_last_x = map(p.x, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, touchWidth - 1);
    touch_last_y = map(p.y, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, touchHeight - 1);
#endif
    return true;
  }
  return false;

#else
  return false;
#endif
}

/**
 * @brief Checks if the touch has been released
 */
inline bool touch_released() {
#if defined(TOUCH_FT6X36)
  if (touch_released_flag) {
    touch_released_flag = false;
    return true;
  }
  return false;
#else
  return true;
#endif
}

#endif // TOUCH_H_
