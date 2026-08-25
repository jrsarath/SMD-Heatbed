/**
 * @file info_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "info_gen.h"
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

lv_obj_t * info_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if LVGL_UI_CHECK_COMPILE_TARGET(LVGL_UI_TARGET_ALL)
    if (lvgl_ui_check_target(LVGL_UI_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "info_#");
        lv_obj_set_width(lv_obj_0, lv_pct(100));
        lv_obj_set_height(lv_obj_0, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_0, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_bg_color(lv_obj_0, COLOR_DARK_BG, 0);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);

        header_create(lv_obj_0, "Information", "Idle", 0);

        lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
        lv_obj_set_width(lv_obj_1, lv_pct(100));
        lv_obj_set_flex_grow(lv_obj_1, 1);
        lv_obj_set_flex_flow(lv_obj_1, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_bg_opa(lv_obj_1, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(lv_obj_1, 0, 0);
        lv_obj_set_style_pad_all(lv_obj_1, SPACE_SM, 0);
        lv_obj_set_style_pad_gap(lv_obj_1, SPACE_SM, 0);
        lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_1);
        lv_obj_set_width(lv_obj_2, lv_pct(100));
        lv_obj_set_height(lv_obj_2, LV_SIZE_CONTENT);
        lv_obj_set_flex_flow(lv_obj_2, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_flag(lv_obj_2, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_bg_color(lv_obj_2, COLOR_CARD_BG, 0);
        lv_obj_set_style_bg_opa(lv_obj_2, (255 * 100 / 100), 0);
        lv_obj_set_style_border_width(lv_obj_2, 1, 0);
        lv_obj_set_style_border_color(lv_obj_2, COLOR_CARD_BORDER, 0);
        lv_obj_set_style_border_opa(lv_obj_2, (255 * 100 / 100), 0);
        lv_obj_set_style_radius(lv_obj_2, RADIUS_MD, 0);
        lv_obj_set_style_pad_hor(lv_obj_2, SPACE_SM, 0);
        lv_obj_set_style_pad_ver(lv_obj_2, SPACE_SM, 0);
        lv_obj_set_style_pad_gap(lv_obj_2, SPACE_XS, 0);
        info_row_create(lv_obj_2, "Device Name", "SMD Heatbed", true);

        info_row_create(lv_obj_2, "Model", "HB-01", true);

        info_row_create(lv_obj_2, "Firmware Version", "v1.0.3", true);

        info_row_create(lv_obj_2, "UI Version", "v1.0.0", false);

        lv_obj_t * nav_bar = navigation_bar_create(lv_obj_0, 0, false, false, false, true);
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

