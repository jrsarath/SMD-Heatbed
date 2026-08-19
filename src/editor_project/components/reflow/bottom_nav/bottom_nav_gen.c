/**
 * @file bottom_nav_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "bottom_nav_gen.h"
#include "../../../src.h"

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

lv_obj_t * bottom_nav_create(lv_obj_t * parent, int32_t active_tab)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if SRC_CHECK_COMPILE_TARGET(SRC_TARGET_ALL)
    if (src_check_target(SRC_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "bottom_nav_#");
        lv_obj_set_width(lv_obj_0, lv_pct(100));
        lv_obj_set_height(lv_obj_0, 40);
        lv_obj_set_flex_flow(lv_obj_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_0, LV_FLEX_ALIGN_SPACE_AROUND, 0);
        lv_obj_set_style_pad_hor(lv_obj_0, 2, 0);
        lv_obj_set_style_bg_color(lv_obj_0, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_border_color(lv_obj_0, COLOR_BORDER, 0);
        lv_obj_set_style_border_width(lv_obj_0, 1, 0);
        lv_obj_set_style_border_side(lv_obj_0, LV_BORDER_SIDE_TOP, 0);

        lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
        lv_obj_set_width(lv_obj_1, 44);
        lv_obj_set_height(lv_obj_1, 34);
        lv_obj_set_flex_flow(lv_obj_1, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_1, RADIUS_DEFAULT, 0);
        lv_obj_set_style_bg_color(lv_obj_1, COLOR_SURFACE_ELEVATED, 0);
        lv_obj_set_style_border_color(lv_obj_1, COLOR_ACCENT, 0);
        lv_obj_set_style_border_width(lv_obj_1, 1, 0);
        lv_obj_t * lv_image_0 = lv_image_create(lv_obj_1);
        lv_image_set_src(lv_image_0, icon_home);
        lv_obj_set_style_image_recolor(lv_image_0, COLOR_ACCENT, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_0, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_0, "HOME");
        lv_obj_set_style_text_color(lv_label_0, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_0, font_body, 0);

        lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_0);
        lv_obj_set_width(lv_obj_2, 44);
        lv_obj_set_height(lv_obj_2, 34);
        lv_obj_set_flex_flow(lv_obj_2, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_2, RADIUS_DEFAULT, 0);
        lv_obj_t * lv_image_1 = lv_image_create(lv_obj_2);
        lv_image_set_src(lv_image_1, icon_layers);
        lv_obj_set_style_image_recolor(lv_image_1, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_1, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_2);
        lv_label_set_text(lv_label_1, "PROF");
        lv_obj_set_style_text_color(lv_label_1, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_1, font_body, 0);

        lv_obj_t * lv_obj_3 = lv_obj_create(lv_obj_0);
        lv_obj_set_width(lv_obj_3, 44);
        lv_obj_set_height(lv_obj_3, 34);
        lv_obj_set_flex_flow(lv_obj_3, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_3, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_3, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_3, RADIUS_DEFAULT, 0);
        lv_obj_t * lv_image_2 = lv_image_create(lv_obj_3);
        lv_image_set_src(lv_image_2, icon_sliders);
        lv_obj_set_style_image_recolor(lv_image_2, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_2, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_2 = lv_label_create(lv_obj_3);
        lv_label_set_text(lv_label_2, "MAN");
        lv_obj_set_style_text_color(lv_label_2, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_2, font_body, 0);

        lv_obj_t * lv_obj_4 = lv_obj_create(lv_obj_0);
        lv_obj_set_width(lv_obj_4, 44);
        lv_obj_set_height(lv_obj_4, 34);
        lv_obj_set_flex_flow(lv_obj_4, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_4, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_4, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_4, RADIUS_DEFAULT, 0);
        lv_obj_t * lv_image_3 = lv_image_create(lv_obj_4);
        lv_image_set_src(lv_image_3, icon_settings);
        lv_obj_set_style_image_recolor(lv_image_3, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_3, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_3 = lv_label_create(lv_obj_4);
        lv_label_set_text(lv_label_3, "SETT");
        lv_obj_set_style_text_color(lv_label_3, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_3, font_body, 0);

        lv_obj_t * lv_obj_5 = lv_obj_create(lv_obj_0);
        lv_obj_set_width(lv_obj_5, 44);
        lv_obj_set_height(lv_obj_5, 34);
        lv_obj_set_flex_flow(lv_obj_5, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_5, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_5, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_5, RADIUS_DEFAULT, 0);
        lv_obj_t * lv_image_4 = lv_image_create(lv_obj_5);
        lv_image_set_src(lv_image_4, icon_info);
        lv_obj_set_style_image_recolor(lv_image_4, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_4, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_4 = lv_label_create(lv_obj_5);
        lv_label_set_text(lv_label_4, "INFO");
        lv_obj_set_style_text_color(lv_label_4, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_4, font_body, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

