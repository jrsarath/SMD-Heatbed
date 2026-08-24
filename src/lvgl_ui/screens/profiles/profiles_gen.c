/**
 * @file profiles_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "profiles_gen.h"
#include "../../lvgl_ui.h"

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

lv_obj_t * profiles_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if LVGL_UI_CHECK_COMPILE_TARGET(LVGL_UI_TARGET_ALL)
    if (lvgl_ui_check_target(LVGL_UI_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "profiles_#");
        lv_obj_set_width(lv_obj_0, lv_pct(100));
        lv_obj_set_height(lv_obj_0, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_0, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_bg_color(lv_obj_0, COLOR_DARK_BG, 0);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);

        header_create(lv_obj_0, "Reflow Profiles", "Idle", 0);

        lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
        lv_obj_set_width(lv_obj_1, lv_pct(100));
        lv_obj_set_flex_grow(lv_obj_1, 1);
        lv_obj_set_flex_flow(lv_obj_1, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_bg_opa(lv_obj_1, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(lv_obj_1, 0, 0);
        lv_obj_set_style_pad_all(lv_obj_1, SPACE_SM, 0);
        lv_obj_set_style_pad_gap(lv_obj_1, SPACE_SM, 0);

        lv_obj_t * nav_bar = navigation_bar_create(lv_obj_0, 0, false, true, false, false);
        lv_obj_set_name(nav_bar, "nav_bar");

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

