/**
 * @file stage_timeline_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "stage_timeline_gen.h"
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

lv_obj_t * stage_timeline_create(lv_obj_t * parent, int32_t active_stage)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if SRC_CHECK_COMPILE_TARGET(SRC_TARGET_ALL)
    if (src_check_target(SRC_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "stage_timeline_#");
        lv_obj_set_width(lv_obj_0, lv_pct(100));
        lv_obj_set_height(lv_obj_0, 32);
        lv_obj_set_flex_flow(lv_obj_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_0, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_pad_hor(lv_obj_0, SPACE_XS, 0);
        lv_obj_set_style_pad_ver(lv_obj_0, SPACE_XS, 0);
        lv_obj_set_style_bg_color(lv_obj_0, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_border_color(lv_obj_0, COLOR_BORDER, 0);
        lv_obj_set_style_border_width(lv_obj_0, 1, 0);
        lv_obj_set_style_radius(lv_obj_0, RADIUS_CARD, 0);

        lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
        lv_obj_set_flex_flow(lv_obj_1, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_column(lv_obj_1, 2, 0);
        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_0, "✓");
        lv_obj_set_style_text_color(lv_label_0, COLOR_SUCCESS, 0);
        lv_obj_set_style_text_font(lv_label_0, font_body, 0);

        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_1, "PRE");
        lv_obj_set_style_text_color(lv_label_1, COLOR_SUCCESS, 0);
        lv_obj_set_style_text_font(lv_label_1, font_body, 0);

        lv_obj_t * lv_label_2 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_2, "›");
        lv_obj_set_style_text_color(lv_label_2, COLOR_TEXT_MUTED, 0);

        lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_0);
        lv_obj_set_flex_flow(lv_obj_2, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_column(lv_obj_2, 2, 0);
        lv_obj_t * lv_label_3 = lv_label_create(lv_obj_2);
        lv_label_set_text(lv_label_3, "✓");
        lv_obj_set_style_text_color(lv_label_3, COLOR_SUCCESS, 0);
        lv_obj_set_style_text_font(lv_label_3, font_body, 0);

        lv_obj_t * lv_label_4 = lv_label_create(lv_obj_2);
        lv_label_set_text(lv_label_4, "SOAK");
        lv_obj_set_style_text_color(lv_label_4, COLOR_SUCCESS, 0);
        lv_obj_set_style_text_font(lv_label_4, font_body, 0);

        lv_obj_t * lv_label_5 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_5, "›");
        lv_obj_set_style_text_color(lv_label_5, COLOR_TEXT_MUTED, 0);

        lv_obj_t * lv_obj_3 = lv_obj_create(lv_obj_0);
        lv_obj_set_flex_flow(lv_obj_3, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_3, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_column(lv_obj_3, 2, 0);
        lv_obj_set_style_pad_hor(lv_obj_3, SPACE_XS, 0);
        lv_obj_set_style_pad_ver(lv_obj_3, 2, 0);
        lv_obj_set_style_bg_color(lv_obj_3, COLOR_ACCENT, 0);
        lv_obj_set_style_radius(lv_obj_3, RADIUS_PILL, 0);
        lv_obj_t * lv_label_6 = lv_label_create(lv_obj_3);
        lv_label_set_text(lv_label_6, "●");
        lv_obj_set_style_text_color(lv_label_6, COLOR_ACCENT_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_6, font_body, 0);

        lv_obj_t * lv_label_7 = lv_label_create(lv_obj_3);
        lv_label_set_text(lv_label_7, "REFLOW");
        lv_obj_set_style_text_color(lv_label_7, COLOR_ACCENT_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_7, font_h5, 0);

        lv_obj_t * lv_label_8 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_8, "›");
        lv_obj_set_style_text_color(lv_label_8, COLOR_TEXT_MUTED, 0);

        lv_obj_t * lv_obj_4 = lv_obj_create(lv_obj_0);
        lv_obj_set_flex_flow(lv_obj_4, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_4, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_column(lv_obj_4, 2, 0);
        lv_obj_t * lv_label_9 = lv_label_create(lv_obj_4);
        lv_label_set_text(lv_label_9, "COOL");
        lv_obj_set_style_text_color(lv_label_9, COLOR_COOLING, 0);
        lv_obj_set_style_text_font(lv_label_9, font_body, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

