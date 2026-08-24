#ifndef TOUCH_H_
#define TOUCH_H_

#include <Arduino.h>

/*******************************************************************************
 * Touch Controller Abstraction (GT911 / FT6X36 / XPT2046)
 ******************************************************************************/

/* Driver Selection: default GT911 for Elecrow 4.3" Pico Display */
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

static uint16_t touchWidth = 320;
static uint16_t touchHeight = 240;

inline int touch_last_x = 0;
inline int touch_last_y = 0;

#if defined(TOUCH_FT6X36)
#include <Wire.h>
#include <FT6X36.h>
static FT6X36 ts(&Wire, TOUCH_FT6X36_INT);
static bool touch_touched_flag = true;
static bool touch_released_flag = true;

#elif defined(TOUCH_GT911)
#include <Wire.h>
#include <TAMC_GT911.h>
static TAMC_GT911 ts = TAMC_GT911(TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT, TOUCH_GT911_RST, max(TOUCH_MAP_X1, TOUCH_MAP_X2), max(TOUCH_MAP_Y1, TOUCH_MAP_Y2));

#elif defined(TOUCH_XPT2046)
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
static XPT2046_Touchscreen ts(TOUCH_XPT2046_CS, TOUCH_XPT2046_INT);
#endif

#if defined(TOUCH_FT6X36)
inline void touch_callback(TPoint p, TEvent e) {
  if (e != TEvent::Tap && e != TEvent::DragStart && e != TEvent::DragMove && e != TEvent::DragEnd) {
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
 * @brief Initializes the touch controller with screen dimensions.
 */
inline void touch_init(uint16_t width, uint16_t height) {
  touchWidth = width;
  touchHeight = height;
  #if defined(TOUCH_FT6X36)
    Wire.setSDA(TOUCH_FT6X36_SDA);
    Wire.setSCL(TOUCH_FT6X36_SCL);
    Wire.begin();
    ts.begin();
    ts.registerTouchHandler(touch_callback);

  #elif defined(TOUCH_GT911)
    ts.begin();
    ts.setRotation(TOUCH_GT911_ROTATION);

  #elif defined(TOUCH_XPT2046)
    SPI.begin(TOUCH_XPT2046_SCK, TOUCH_XPT2046_MISO, TOUCH_XPT2046_MOSI, TOUCH_XPT2046_CS);
    ts.begin();
    ts.setRotation(TOUCH_XPT2046_ROTATION);
  #endif
}

/**
 * @brief Checks if touch hardware signal is available.
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
 * @brief Checks if screen is currently touched and updates touch_last_x / touch_last_y.
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
      #if defined(TOUCH_SWAP_XY)
          touch_last_x = map(ts.points[0].y, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, touchWidth - 1);
          touch_last_y = map(ts.points[0].x, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, touchHeight - 1);
      #else
          touch_last_x = map(ts.points[0].x, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, touchWidth - 1);
          touch_last_y = map(ts.points[0].y, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, touchHeight - 1);
      #endif
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
 * @brief Checks if touch release event occurred.
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
