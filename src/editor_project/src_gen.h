/**
 * @file src_gen.h
 */

#ifndef LVGL_PRO_SRC_GEN_H
#define LVGL_PRO_SRC_GEN_H

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

void src_set_target(uint32_t target);
uint32_t src_get_target(void);
bool src_check_target(uint32_t target);

/*********************
 *      DEFINES
 *********************/

#define SRC_TARGET_UNDEFINED  (0 << 1)
#define SRC_TARGET_TARGET1    (1 << 1)
#define SRC_TARGET_ALL        0x0FFFFFFF

/* By default compile for all targets, allowing to switch to any targets at runtime */
#ifndef SRC_COMPILE_TARGET
#define SRC_COMPILE_TARGET SRC_TARGET_ALL
#endif

#define SRC_CHECK_COMPILE_TARGET(target) (SRC_COMPILE_TARGET & (target) ? 1 : 0)

/**
 * Smallest spacing unit
 */
#define SPACE_XS 2
/**
 * Small spacing unit
 */
#define SPACE_SM 4
/**
 * Default spacing unit
 */
#define SPACE_MD 8
/**
 * Large spacing unit
 */
#define SPACE_LG 12
/**
 * Extra-large spacing unit
 */
#define SPACE_XL 16
/**
 * Default corner radius
 */
#define RADIUS_DEFAULT 8
/**
 * Card corner radius
 */
#define RADIUS_CARD 10
/**
 * Pill / Badge corner radius
 */
#define RADIUS_PILL 16
/**
 * Default border width
 */
#define BORDER_WIDTH 1
/**
 * Default icon size
 */
#define ICON_SIZE 16
/**
 * Large icon size
 */
#define ICON_SIZE_LG 20
/**
 * Opacity for muted elements
 */
#define OPA_MUTED (255 * 45 / 100)
/**
 * Background: Dark charcoal / near-black
 */
#define COLOR_DARK_BG lv_color_hex(0x0D1117)
/**
 * Surface: Cards / panel background
 */
#define COLOR_DARK_PANEL lv_color_hex(0x171C23)
/**
 * Elevated Surface: High-contrast cards
 */
#define COLOR_SURFACE_ELEVATED lv_color_hex(0x1D232C)
/**
 * Subtle panel border
 */
#define COLOR_BORDER lv_color_hex(0x303743)
/**
 * Primary Accent: Thermal Orange
 */
#define COLOR_ACCENT lv_color_hex(0xFF7A00)
/**
 * Text on thermal accent
 */
#define COLOR_ACCENT_TEXT lv_color_hex(0xFFFFFF)
/**
 * Success: Completed stage / ok
 */
#define COLOR_SUCCESS lv_color_hex(0x65D84A)
/**
 * Danger: STOP / over-temp / alert
 */
#define COLOR_DANGER lv_color_hex(0xE53935)
/**
 * Cooling: Cyan / Blue stage
 */
#define COLOR_COOLING lv_color_hex(0x29A9E8)
/**
 * Warning: Sensor notice / amber
 */
#define COLOR_WARNING lv_color_hex(0xFFB300)
/**
 * High contrast primary text
 */
#define COLOR_TEXT_PRIMARY lv_color_hex(0xF2F4F7)
/**
 * Secondary text
 */
#define COLOR_TEXT_SECONDARY lv_color_hex(0xB7BEC8)
/**
 * Muted caption text
 */
#define COLOR_TEXT_MUTED lv_color_hex(0x737C88)
#define COLOR_LIGHT_BG lv_color_hex(0x0D1117)
#define COLOR_LIGHT_PANEL lv_color_hex(0x171C23)
#define COLOR_LIGHT_TEXT lv_color_hex(0xF2F4F7)
#define COLOR_DARK_TEXT lv_color_hex(0xF2F4F7)
#define COLOR_TRACK lv_color_hex(0x303743)


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

extern lv_obj_t * screen_home;
extern lv_obj_t * screen_info;
extern lv_obj_t * screen_manual;
extern lv_obj_t * screen_profiles;
extern lv_obj_t * screen_settings;

/*----------------
 * Global styles
 *----------------*/

extern lv_style_t style_screen_light;
extern lv_style_t style_screen_dark;
extern lv_style_t style_panel_light;
extern lv_style_t style_panel_dark;
extern lv_style_t style_panel_elevated;
extern lv_style_t style_text_accent;
extern lv_style_t style_text_success;
extern lv_style_t style_text_danger;
extern lv_style_t style_text_cooling;
extern lv_style_t style_text_warning;
extern lv_style_t style_text_secondary;
extern lv_style_t style_text_muted;
extern lv_style_t style_hero_temp;
extern lv_style_t style_nav_active;
extern lv_style_t style_btn_stop;
extern lv_style_t style_scrollbar;

/*----------------
 * Fonts
 *----------------*/

/* Targets: any */
extern lv_font_t * font_body_symbols;
extern lv_font_t * font_body;
extern lv_font_t * font_h5;
extern lv_font_t * font_h4;
extern lv_font_t * font_h3;
extern lv_font_t * font_h2;
extern lv_font_t * font_h1;


/*----------------
 * Images
 *----------------*/

/* Targets: any */
extern const void * icon_arrow_down;
extern const void * icon_arrow_left;
extern const void * icon_arrow_right;
extern const void * icon_arrow_up;
extern const void * icon_battery;
extern const void * icon_battery_full;
extern const void * icon_bell;
extern const void * icon_bluetooth;
extern const void * icon_calendar;
extern const void * icon_camera;
extern const void * icon_check;
extern const void * icon_chevron_down;
extern const void * icon_chevron_left;
extern const void * icon_chevron_right;
extern const void * icon_chevron_up;
extern const void * icon_clock;
extern const void * icon_close;
extern const void * icon_download;
extern const void * icon_edit;
extern const void * icon_heart;
extern const void * icon_home;
extern const void * icon_info;
extern const void * icon_lock;
extern const void * icon_mail;
extern const void * icon_menu;
extern const void * icon_minus;
extern const void * icon_moon;
extern const void * icon_pause;
extern const void * icon_play;
extern const void * icon_plus;
extern const void * icon_power;
extern const void * icon_refresh;
extern const void * icon_search;
extern const void * icon_settings;
extern const void * icon_signal;
extern const void * icon_star;
extern const void * icon_sun;
extern const void * icon_trash;
extern const void * icon_unlock;
extern const void * icon_upload;
extern const void * icon_user;
extern const void * icon_volume;
extern const void * icon_wifi;
extern const void * icon_wifi_high;
extern const void * icon_wifi_low;
extern const void * icon_wifi_zero;
extern const void * icon_flame;
extern const void * icon_thermometer;
extern const void * icon_chart;
extern const void * icon_layers;
extern const void * icon_sliders;
extern const void * icon_snowflake;

/*----------------
 * Subjects
 *----------------*/

extern lv_subject_t subject_theme_dark;
extern lv_subject_t subject_active_tab;
extern lv_subject_t subject_current_temp;
extern lv_subject_t subject_target_temp;
extern lv_subject_t subject_heater_output;
extern lv_subject_t subject_stage_index;
extern lv_subject_t subject_heater_active;
extern lv_subject_t subject_brightness;
extern lv_subject_t subject_beeper;
extern lv_subject_t subject_manual_setpoint;
extern lv_subject_t subject_show_keyboard;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*----------------
 * Event Callbacks
 *----------------*/

/**
 * Initialize the component library
 */

void src_init_gen(const char * asset_path);

/**********************
 *      MACROS
 **********************/

/**********************
 *   POST INCLUDES
 **********************/

/*Include all the widgets, components and screens of this library*/
#include "components/controls/arc/arc_gen.h"
#include "components/controls/bar/bar_gen.h"
#include "components/controls/button/button_gen.h"
#include "components/controls/checkbox/checkbox_gen.h"
#include "components/controls/dropdown/dropdown_gen.h"
#include "components/controls/keyboard/keyboard_gen.h"
#include "components/controls/slider/slider_gen.h"
#include "components/controls/switch/switch_gen.h"
#include "components/controls/text_box/text_box_gen.h"
#include "components/controls/text_input/text_input_gen.h"
#include "components/images/image/image_gen.h"
#include "components/images/monoicon/monoicon_gen.h"
#include "components/layout/base_box/base_box_gen.h"
#include "components/layout/column/column_gen.h"
#include "components/layout/container/container_gen.h"
#include "components/layout/panel/panel_gen.h"
#include "components/layout/row/row_gen.h"
#include "components/list/list_item/list_item_gen.h"
#include "components/list/list_section/list_section_gen.h"
#include "components/list/list_separator/list_separator_gen.h"
#include "components/list/list/list_gen.h"
#include "components/reflow/bottom_nav/bottom_nav_gen.h"
#include "components/reflow/header/header_gen.h"
#include "components/reflow/stage_timeline/stage_timeline_gen.h"
#include "components/reflow/temp_display/temp_display_gen.h"
#include "components/typography/h1/h1_gen.h"
#include "components/typography/h2/h2_gen.h"
#include "components/typography/h3/h3_gen.h"
#include "components/typography/h4/h4_gen.h"
#include "components/typography/h5/h5_gen.h"
#include "components/typography/text/text_gen.h"
#include "screens/screen_home_gen.h"
#include "screens/screen_info_gen.h"
#include "screens/screen_manual_gen.h"
#include "screens/screen_profiles_gen.h"
#include "screens/screen_settings_gen.h"

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_PRO_SRC_GEN_H*/