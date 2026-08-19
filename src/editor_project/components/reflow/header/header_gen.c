/**
 * @file header_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "header_gen.h"
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

lv_obj_t * header_create(lv_obj_t * parent, const char * title, const char * time, const void * icon)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if SRC_CHECK_COMPILE_TARGET(SRC_TARGET_ALL)
    if (src_check_target(SRC_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "header_#");
        lv_obj_set_width(lv_obj_0, lv_pct(100));
        lv_obj_set_height(lv_obj_0, 28);
        lv_obj_set_flex_flow(lv_obj_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_hor(lv_obj_0, SPACE_MD, 0);
        lv_obj_set_style_pad_column(lv_obj_0, SPACE_XS, 0);
        lv_obj_set_style_bg_color(lv_obj_0, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_border_color(lv_obj_0, COLOR_BORDER, 0);
        lv_obj_set_style_border_width(lv_obj_0, 1, 0);
        lv_obj_set_style_border_side(lv_obj_0, LV_BORDER_SIDE_BOTTOM, 0);

        lv_obj_t * lv_image_0 = lv_image_create(lv_obj_0);
        lv_image_set_src(lv_image_0, icon);
        lv_obj_set_style_image_recolor(lv_image_0, COLOR_ACCENT, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_0, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_0, title);
        lv_obj_set_style_text_color(lv_label_0, COLOR_TEXT_PRIMARY, 0);
        lv_obj_set_style_text_font(lv_label_0, font_h5, 0);
        lv_obj_set_style_text_letter_space(lv_label_0, 1, 0);

        container_create(lv_obj_0, 8, 0, LV_FLEX_FLOW_COLUMN, 1);

        lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
        lv_obj_set_width(lv_obj_1, 6);
        lv_obj_set_height(lv_obj_1, 6);
        lv_obj_set_style_bg_color(lv_obj_1, COLOR_SUCCESS, 0);
        lv_obj_set_style_radius(lv_obj_1, 3, 0);

        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_1, time);
        lv_obj_set_style_text_color(lv_label_1, COLOR_TEXT_SECONDARY, 0);
        lv_obj_set_style_text_font(lv_label_1, font_body, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

