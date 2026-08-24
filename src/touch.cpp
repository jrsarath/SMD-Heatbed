#include "touch.h"
#include "config.h"

int touch_last_x = 0;
int touch_last_y = 0;

#if defined(TOUCH_FT6X36)

#include <FT6X36.h>
#include <Wire.h>

FT6X36 ts(&Wire, TOUCH_FT6X36_INT);

bool touch_touched_flag = true;
bool touch_released_flag = true;

#elif defined(TOUCH_GT911)

#include <TAMC_GT911.h>
#include <Wire.h>

TAMC_GT911 ts = TAMC_GT911(TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT,
                           TOUCH_GT911_RST, max(TOUCH_MAP_X1, TOUCH_MAP_X2),
                           max(TOUCH_MAP_Y1, TOUCH_MAP_Y2));

#elif defined(TOUCH_XPT2046)

#include <SPI.h>
#include <XPT2046_Touchscreen.h>

XPT2046_Touchscreen ts(TOUCH_XPT2046_CS, TOUCH_XPT2046_INT);

#endif

#if defined(TOUCH_FT6X36)

void touch(TPoint p, TEvent e) {
  if (e != TEvent::Tap && e != TEvent::DragStart && e != TEvent::DragMove &&
      e != TEvent::DragEnd) {
    return;
  }

  // Translation logic depends on screen rotation
#if defined(TOUCH_SWAP_XY)

  touch_last_x = map(p.y, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, lcd.width());

  touch_last_y = map(p.x, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, lcd.height());

#else

  touch_last_x = map(p.x, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, lcd.width());

  touch_last_y = map(p.y, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, lcd.height());

#endif

  switch (e) {
  case TEvent::Tap:
    Serial.println("Tap");
    touch_touched_flag = true;
    touch_released_flag = true;
    break;

  case TEvent::DragStart:
    Serial.println("DragStart");
    touch_touched_flag = true;
    break;

  case TEvent::DragMove:
    Serial.println("DragMove");
    touch_touched_flag = true;
    break;

  case TEvent::DragEnd:
    Serial.println("DragEnd");
    touch_released_flag = true;
    break;

  default:
    Serial.println("UNKNOWN");
    break;
  }
}

#endif

void touch_init() {
#if defined(TOUCH_FT6X36)

  Wire.begin(TOUCH_FT6X36_SDA, TOUCH_FT6X36_SCL);

  ts.begin();
  ts.registerTouchHandler(touch);

#elif defined(TOUCH_GT911)

  // Wire.setSDA(TOUCH_GT911_SDA);
  // Wire.setSCL(TOUCH_GT911_SCL);
  // Wire.begin();
  // Wire1.begin(TOUCH_GT911_SDA, TOUCH_GT911_SCL);

  ts.begin();
  ts.setRotation(TOUCH_GT911_ROTATION);

#elif defined(TOUCH_XPT2046)

  SPI.begin(TOUCH_XPT2046_SCK, TOUCH_XPT2046_MISO, TOUCH_XPT2046_MOSI,
            TOUCH_XPT2046_CS);

  ts.begin();
  ts.setRotation(TOUCH_XPT2046_ROTATION);

#endif
}

bool touch_has_signal() {
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

bool touch_touched() {
#if defined(TOUCH_FT6X36)

  if (touch_touched_flag) {
    touch_touched_flag = false;
    return true;
  }

  return false;

#elif defined(TOUCH_GT911)

  ts.read();

  if (ts.isTouched) {
    /*
     * GT911 raw coordinate system:
     *
     *     800 x 480
     *
     * Physical display:
     *
     *     320 x 240 landscape
     *
     * PicoDVI:
     *
     *     setRotation(3)
     *
     * LVGL:
     *
     *     240 x 320 portrait
     *
     * First convert GT911 coordinates to the physical
     * 320x240 display space, then apply the 270-degree
     * rotation to produce LVGL coordinates.
     */

    int raw_x = ts.points[0].x;
    int raw_y = ts.points[0].y;

    // Reverse GT911 axes to match the existing panel orientation.
    int physical_x = map(800 - raw_x, 0, 800, 0, DISPLAY_WIDTH - 1);

    int physical_y = map(480 - raw_y, 0, 480, 0, DISPLAY_HEIGHT - 1);

    /*
     * Rotate physical 320x240 coordinates 270 degrees.
     *
     * Physical:
     *   X = 0..319
     *   Y = 0..239
     *
     * LVGL:
     *   X = 0..239
     *   Y = 0..319
     */
    touch_last_x = (DISPLAY_HEIGHT - 1) - physical_y;
    touch_last_y = physical_x;

    // Ensure coordinates stay inside LVGL bounds.
    touch_last_x = constrain(touch_last_x, 0, SCREEN_WIDTH - 1);

    touch_last_y = constrain(touch_last_y, 0, SCREEN_HEIGHT - 1);

    return true;
  }

  return false;

#elif defined(TOUCH_XPT2046)

  if (ts.touched()) {
    TS_Point p = ts.getPoint();

#if defined(TOUCH_SWAP_XY)

    touch_last_x = map(p.y, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, lcd.width() - 1);

    touch_last_y = map(p.x, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, lcd.height() - 1);

#else

    touch_last_x = map(p.x, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, lcd.width() - 1);

    touch_last_y = map(p.y, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, lcd.height() - 1);

#endif

    return true;
  }

  return false;

#else

  return false;

#endif
}

bool touch_released() {
#if defined(TOUCH_FT6X36)

  if (touch_released_flag) {
    touch_released_flag = false;
    return true;
  }

  return false;

#elif defined(TOUCH_GT911)

  return true;

#elif defined(TOUCH_XPT2046)

  return true;

#else

  return false;

#endif
}