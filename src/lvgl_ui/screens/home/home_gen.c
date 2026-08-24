/**
 * @file home_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "home_gen.h"
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

lv_obj_t * home_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if LVGL_UI_CHECK_COMPILE_TARGET(LVGL_UI_TARGET_ALL)
    if (lvgl_ui_check_target(LVGL_UI_TARGET_ALL)) {
        if (home == NULL) home = lv_obj_create(NULL);
        lv_obj_t * lv_obj_0 = home;
        lv_obj_set_name_static(lv_obj_0, "home_#");

        lv_obj_add_style(lv_obj_0, &style_screen_light, 0);
        lv_obj_bind_style(lv_obj_0, &style_screen_dark, 0, &subject_theme_dark, 1);
        lv_obj_add_style(lv_obj_0, &style_scrollbar, LV_PART_SCROLLBAR);
        lv_obj_t * column_0 = column_create(lv_obj_0, 0, 0, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_START);
        lv_obj_set_width(column_0, lv_pct(100));
        lv_obj_set_height(column_0, lv_pct(100));
        lv_obj_t * container_0 = container_create(column_0, SPACE_LG, SPACE_MD, LV_FLEX_FLOW_COLUMN, 1);
        lv_obj_set_width(container_0, lv_pct(100));
        lv_obj_t * row_0 = row_create(container_0, 0, SPACE_MD, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_set_width(row_0, lv_pct(100));
        h4_create(row_0, "Dashboard", "");

        container_create(row_0, 8, 0, LV_FLEX_FLOW_COLUMN, 1);

        switch_create(row_0, &subject_theme_dark, COLOR_ACCENT);

        lv_obj_t * panel_0 = panel_create(container_0, SPACE_LG, SPACE_MD, LV_FLEX_FLOW_COLUMN, 0);
        lv_obj_set_width(panel_0, lv_pct(100));
        h5_create(panel_0, "Welcome to SMD Heatbed", "");

        lv_obj_t * text_0 = text_create(panel_0, "Reflow & SMT Soldering Controller UI with modular LVGL Pro XML navigation.");
        lv_obj_set_width(text_0, lv_pct(100));

        navigation_bar_create(column_0, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

