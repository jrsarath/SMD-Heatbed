/**
 * @file navigation_bar_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "navigation_bar_gen.h"
#include "../../../lvgl_ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * navigation_bar_create(lv_obj_t * parent, int32_t grow)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_nav_bar;
    static lv_style_t style_nav_bar_light;
    static lv_style_t style_nav_bar_dark;

    static bool style_inited = false;

    if (!style_inited) {
        /*Init all styles*/
        lv_style_init(&style_nav_bar);
        lv_style_init(&style_nav_bar_light);
        lv_style_init(&style_nav_bar_dark);

        lv_style_set_width(&style_nav_bar, lv_pct(100));
        lv_style_set_height(&style_nav_bar, 40);
        lv_style_set_pad_hor(&style_nav_bar, SPACE_XS);
        lv_style_set_pad_ver(&style_nav_bar, SPACE_XS);
        lv_style_set_pad_gap(&style_nav_bar, SPACE_XS);
        lv_style_set_flex_flow(&style_nav_bar, LV_FLEX_FLOW_ROW);
        lv_style_set_flex_cross_place(&style_nav_bar, LV_FLEX_ALIGN_CENTER);
        lv_style_set_flex_main_place(&style_nav_bar, LV_FLEX_ALIGN_SPACE_EVENLY);
        lv_style_set_radius(&style_nav_bar, 0);
        lv_style_set_border_width(&style_nav_bar, BORDER_WIDTH);
        lv_style_set_bg_color(&style_nav_bar_light, COLOR_LIGHT_PANEL);
        lv_style_set_bg_opa(&style_nav_bar_light, (255 * 100 / 100));
        lv_style_set_border_color(&style_nav_bar_light, COLOR_LIGHT_TEXT);
        lv_style_set_border_opa(&style_nav_bar_light, (255 * 20 / 100));
        lv_style_set_bg_color(&style_nav_bar_dark, COLOR_DARK_PANEL);
        lv_style_set_bg_opa(&style_nav_bar_dark, (255 * 100 / 100));
        lv_style_set_border_color(&style_nav_bar_dark, COLOR_DARK_TEXT);
        lv_style_set_border_opa(&style_nav_bar_dark, (255 * 20 / 100));

        style_inited = true;
    }


    lv_obj_t * the_root = NULL;

    #if LVGL_UI_CHECK_COMPILE_TARGET(LVGL_UI_TARGET_ALL)
    if (lvgl_ui_check_target(LVGL_UI_TARGET_ALL)) {
        lv_obj_t * container_0 = container_create(parent, 0, 0, LV_FLEX_FLOW_ROW, grow);
        lv_obj_set_name_static(container_0, "navigation_bar_#");
        lv_obj_set_width(container_0, lv_pct(100));
        lv_obj_set_height(container_0, 40);

        lv_obj_add_style(container_0, &style_nav_bar, 0);
        lv_obj_add_style(container_0, &style_nav_bar_light, 0);
        lv_obj_bind_style(container_0, &style_nav_bar_dark, 0, &subject_theme_dark, 1);
        lv_obj_t * nav_btn_home = navigation_button_create(container_0, "Home", icon_home, true, 1);
        lv_obj_set_name(nav_btn_home, "nav_btn_home");

        lv_obj_t * nav_btn_profile = navigation_button_create(container_0, "Profile", icon_search, false, 1);
        lv_obj_set_name(nav_btn_profile, "nav_btn_profile");

        lv_obj_t * nav_btn_manual = navigation_button_create(container_0, "Manual", icon_star, false, 1);
        lv_obj_set_name(nav_btn_manual, "nav_btn_manual");

        lv_obj_t * nav_btn_settings = navigation_button_create(container_0, "Settings", icon_settings, false, 1);
        lv_obj_set_name(nav_btn_settings, "nav_btn_settings");

        lv_obj_t * nav_btn_info = navigation_button_create(container_0, "Info", icon_info, false, 1);
        lv_obj_set_name(nav_btn_info, "nav_btn_info");

        the_root = container_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

