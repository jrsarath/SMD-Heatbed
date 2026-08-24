/**
 * @file lvgl_ui_gen.h
 */

#ifndef LVGL_PRO_LVGL_UI_GEN_H
#define LVGL_PRO_LVGL_UI_GEN_H

#ifndef UI_SUBJECT_STRING_LENGTH
#define UI_SUBJECT_STRING_LENGTH 256
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
    #include "lvgl_private.h"
#else
    #include "lvgl/lvgl.h"
    #include "lvgl/lvgl_private.h"
#endif

#if defined(LV_USE_XML) && LV_USE_XML
    #include "lv_xml/lv_xml.h"
#endif



/* Prototypes for target functions, needed by responsive const definitions */

void lvgl_ui_set_target(uint32_t target);
uint32_t lvgl_ui_get_target(void);
bool lvgl_ui_check_target(uint32_t target);

/*********************
 *      DEFINES
 *********************/

#define LVGL_UI_TARGET_UNDEFINED  (0 << 1)
#define LVGL_UI_TARGET_TARGET1    (1 << 1)
#define LVGL_UI_TARGET_ALL        0x0FFFFFFF

/* By default compile for all targets, allowing to switch to any targets at runtime */
#ifndef LVGL_UI_COMPILE_TARGET
#define LVGL_UI_COMPILE_TARGET LVGL_UI_TARGET_ALL
#endif

#define LVGL_UI_CHECK_COMPILE_TARGET(target) (LVGL_UI_COMPILE_TARGET & (target) ? 1 : 0)

/**
 * Dark screen background
 */
#define COLOR_DARK_BG lv_color_hex(0x12151C)
/**
 * Navigation bar background
 */
#define COLOR_NAV_BG lv_color_hex(0x1E232E)
/**
 * Navigation bar border
 */
#define COLOR_NAV_BORDER lv_color_hex(0x2A303C)
/**
 * Inactive nav text color
 */
#define COLOR_NAV_TEXT lv_color_hex(0x8A92A6)
/**
 * Accent cyan color
 */
#define COLOR_ACCENT lv_color_hex(0x00FFCC)
/**
 * Accent text color
 */
#define COLOR_ACCENT_TEXT lv_color_hex(0x000000)
/**
 * Accent pressed color
 */
#define COLOR_ACCENT_PRESSED lv_color_hex(0x00B38F)
/**
 * Card container background
 */
#define COLOR_CARD_BG lv_color_hex(0x1A1F2B)
/**
 * Card container border
 */
#define COLOR_CARD_BORDER lv_color_hex(0x2A3245)
/**
 * Primary text color
 */
#define COLOR_TEXT_PRIMARY lv_color_hex(0xFFFFFF)
/**
 * Muted secondary text color
 */
#define COLOR_TEXT_MUTED lv_color_hex(0x94A3B8)
/**
 * Danger red color
 */
#define COLOR_DANGER lv_color_hex(0xFF4D4D)
/**
 * Warning amber color
 */
#define COLOR_WARNING lv_color_hex(0xFFB800)
/**
 * Success green color
 */
#define COLOR_SUCCESS lv_color_hex(0x10B981)
/**
 * Extra small spacing
 */
#define SPACE_XS 4
/**
 * Small spacing
 */
#define SPACE_SM 8
/**
 * Medium spacing
 */
#define SPACE_MD 12
/**
 * Large spacing
 */
#define SPACE_LG 16
/**
 * Small corner radius
 */
#define RADIUS_SM 4
/**
 * Medium corner radius
 */
#define RADIUS_MD 8


#ifndef LV_XML_EVAL_STRING_BUF_SIZE
    #define LV_XML_EVAL_STRING_BUF_SIZE 256
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL VARIABLES
 **********************/

/*-------------------
 * Permanent screens
 *------------------*/

/*----------------
 * Global styles
 *----------------*/

/*----------------
 * Fonts
 *----------------*/

/* Targets: any */
extern lv_font_t * font_xs;
extern lv_font_t * font_sm;
extern lv_font_t * font_md;
extern lv_font_t * font_lg;


/*----------------
 * Images
 *----------------*/



/*----------------
 * Subjects
 *----------------*/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*----------------
 * Event Callbacks
 *----------------*/

/**
 * Initialize the component library
 */

void lvgl_ui_init_gen(const char * asset_path);

/**********************
 *      MACROS
 **********************/

/**********************
 *   POST INCLUDES
 **********************/

/*Include all the widgets, components and screens of this library*/
#include "components/navigation/navigation_bar/navigation_bar_gen.h"
#include "components/navigation/navigation_button/navigation_button_gen.h"
#include "screens/home/home_gen.h"
#include "screens/info/info_gen.h"
#include "screens/manual/manual_gen.h"
#include "screens/profiles/profiles_gen.h"

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_PRO_LVGL_UI_GEN_H*/