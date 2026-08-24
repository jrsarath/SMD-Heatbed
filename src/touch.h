#pragma once

/*******************************************************************************
Touch libraries:
FT6X36: https://github.com/strange-v/FT6X36.git
GT911: https://github.com/TAMCTec/gt911-arduino.git
XPT2046: https://github.com/PaulStoffregen/XPT2046_Touchscreen.git
******************************************************************************/

/* uncomment for FT6X36 */
// #define TOUCH_FT6X36
// #define TOUCH_FT6X36_SCL 19
// #define TOUCH_FT6X36_SDA 18
// #define TOUCH_FT6X36_INT 39
// #define TOUCH_SWAP_XY
// #define TOUCH_MAP_X1 480
// #define TOUCH_MAP_X2 0
// #define TOUCH_MAP_Y1 0
// #define TOUCH_MAP_Y2 320

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

/* uncomment for XPT2046 */
// #define TOUCH_XPT2046
// #define TOUCH_XPT2046_SCK 12
// #define TOUCH_XPT2046_MISO 13
// #define TOUCH_XPT2046_MOSI 11
// #define TOUCH_XPT2046_CS 38
// #define TOUCH_XPT2046_INT 18
// #define TOUCH_XPT2046_ROTATION 0
// #define TOUCH_MAP_X1 4000
// #define TOUCH_MAP_X2 100
// #define TOUCH_MAP_Y1 100
// #define TOUCH_MAP_Y2 4000

// Public touch state
extern int touch_last_x;
extern int touch_last_y;

// Public touch API
void touch_init();
bool touch_has_signal();
bool touch_touched();
bool touch_released();