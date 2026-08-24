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

lv_obj_t * navigation_bar_create(lv_obj_t * parent, int32_t grow, bool active_home, bool active_profiles, bool active_manual, bool active_info)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_nav_bar;

    static bool style_inited = false;

    if (!style_inited) {
        /*Init all styles*/
        lv_style_init(&style_nav_bar);

        lv_style_set_width(&style_nav_bar, lv_pct(100));
        lv_style_set_height(&style_nav_bar, 40);
        lv_style_set_pad_hor(&style_nav_bar, SPACE_XS);
        lv_style_set_pad_ver(&style_nav_bar, SPACE_XS);
        lv_style_set_pad_gap(&style_nav_bar, SPACE_XS);
        lv_style_set_flex_flow(&style_nav_bar, LV_FLEX_FLOW_ROW);
        lv_style_set_flex_cross_place(&style_nav_bar, LV_FLEX_ALIGN_CENTER);
        lv_style_set_flex_main_place(&style_nav_bar, LV_FLEX_ALIGN_SPACE_EVENLY);
        lv_style_set_radius(&style_nav_bar, 0);
        lv_style_set_border_width(&style_nav_bar, 1);
        lv_style_set_bg_color(&style_nav_bar, COLOR_NAV_BG);
        lv_style_set_bg_opa(&style_nav_bar, (255 * 100 / 100));
        lv_style_set_border_color(&style_nav_bar, COLOR_NAV_BORDER);
        lv_style_set_border_opa(&style_nav_bar, (255 * 100 / 100));

        style_inited = true;
    }


    lv_obj_t * the_root = NULL;

    #if LVGL_UI_CHECK_COMPILE_TARGET(LVGL_UI_TARGET_ALL)
    if (lvgl_ui_check_target(LVGL_UI_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "navigation_bar_#");
        lv_obj_set_flex_flow(lv_obj_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_width(lv_obj_0, lv_pct(100));
        lv_obj_set_height(lv_obj_0, 40);
        lv_obj_set_flex_grow(lv_obj_0, grow);

        lv_obj_add_style(lv_obj_0, &style_nav_bar, 0);
        lv_obj_t * nav_btn_home = navigation_button_create(lv_obj_0, "Home", active_home, 1);
        lv_obj_set_name(nav_btn_home, "nav_btn_home");
        lv_obj_add_screen_create_event(nav_btn_home, LV_EVENT_CLICKED, home_create, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);

        lv_obj_t * nav_btn_profiles = navigation_button_create(lv_obj_0, "Profiles", active_profiles, 1);
        lv_obj_set_name(nav_btn_profiles, "nav_btn_profiles");
        lv_obj_add_screen_create_event(nav_btn_profiles, LV_EVENT_CLICKED, profiles_create, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);

        lv_obj_t * nav_btn_manual = navigation_button_create(lv_obj_0, "Manual", active_manual, 1);
        lv_obj_set_name(nav_btn_manual, "nav_btn_manual");
        lv_obj_add_screen_create_event(nav_btn_manual, LV_EVENT_CLICKED, manual_create, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);

        lv_obj_t * nav_btn_info = navigation_button_create(lv_obj_0, "Info", active_info, 1);
        lv_obj_set_name(nav_btn_info, "nav_btn_info");
        lv_obj_add_screen_create_event(nav_btn_info, LV_EVENT_CLICKED, info_create, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

