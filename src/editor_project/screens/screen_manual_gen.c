/**
 * @file screen_manual_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "screen_manual_gen.h"
#include "../src.h"

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

lv_obj_t * screen_manual_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if SRC_CHECK_COMPILE_TARGET(SRC_TARGET_ALL)
    if (src_check_target(SRC_TARGET_ALL)) {
        if (screen_manual == NULL) screen_manual = lv_obj_create(NULL);
        lv_obj_t * lv_obj_0 = screen_manual;
        lv_obj_set_name_static(lv_obj_0, "screen_manual_#");
        lv_obj_set_width(lv_obj_0, 240);
        lv_obj_set_height(lv_obj_0, 320);

        lv_obj_add_style(lv_obj_0, &style_screen_dark, 0);
        lv_obj_t * column_0 = column_create(lv_obj_0, 0, 2, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        header_create(column_0, "MANUAL MODE", "12:45", icon_sliders);

        lv_obj_t * lv_obj_1 = lv_obj_create(column_0);
        lv_obj_set_width(lv_obj_1, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_1, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_hor(lv_obj_1, SPACE_SM, 0);
        lv_obj_set_style_pad_ver(lv_obj_1, 2, 0);
        lv_obj_set_style_pad_row(lv_obj_1, 4, 0);
        lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_1);
        lv_obj_set_width(lv_obj_2, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_2, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(lv_obj_2, SPACE_SM, 0);
        lv_obj_set_style_pad_column(lv_obj_2, SPACE_XS, 0);
        lv_obj_set_style_bg_color(lv_obj_2, COLOR_SURFACE_ELEVATED, 0);
        lv_obj_set_style_border_color(lv_obj_2, COLOR_WARNING, 0);
        lv_obj_set_style_border_width(lv_obj_2, 1, 0);
        lv_obj_set_style_radius(lv_obj_2, RADIUS_CARD, 0);
        lv_obj_t * lv_image_0 = lv_image_create(lv_obj_2);
        lv_image_set_src(lv_image_0, icon_info);
        lv_obj_set_style_image_recolor(lv_image_0, COLOR_WARNING, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_0, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_2);
        lv_label_set_text(lv_label_0, "CAUTION: Manual mode bypasses profile safety timer limits. Maintain active supervision.");
        lv_obj_set_width(lv_label_0, 190);
        lv_obj_set_style_text_color(lv_label_0, COLOR_WARNING, 0);
        lv_obj_set_style_text_font(lv_label_0, font_body, 0);

        lv_obj_t * lv_obj_3 = lv_obj_create(lv_obj_1);
        lv_obj_set_width(lv_obj_3, lv_pct(100));
        lv_obj_set_height(lv_obj_3, 52);
        lv_obj_set_flex_flow(lv_obj_3, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(lv_obj_3, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_3, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_t * lv_obj_4 = lv_obj_create(lv_obj_3);
        lv_obj_set_width(lv_obj_4, 114);
        lv_obj_set_height(lv_obj_4, 52);
        lv_obj_set_flex_flow(lv_obj_4, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(lv_obj_4, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_4, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(lv_obj_4, SPACE_XS, 0);
        lv_obj_set_style_bg_color(lv_obj_4, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_border_color(lv_obj_4, COLOR_BORDER, 0);
        lv_obj_set_style_border_width(lv_obj_4, 1, 0);
        lv_obj_set_style_radius(lv_obj_4, RADIUS_CARD, 0);
        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_4);
        lv_label_set_text(lv_label_1, "CURRENT TEMP");
        lv_obj_set_style_text_color(lv_label_1, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_1, font_body, 0);

        lv_obj_t * lv_label_2 = lv_label_create(lv_obj_4);
        lv_label_bind_text(lv_label_2, &subject_current_temp, "%d°C");
        lv_obj_set_style_text_color(lv_label_2, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_2, font_h2, 0);

        lv_obj_t * lv_obj_5 = lv_obj_create(lv_obj_3);
        lv_obj_set_width(lv_obj_5, 114);
        lv_obj_set_height(lv_obj_5, 52);
        lv_obj_set_flex_flow(lv_obj_5, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(lv_obj_5, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_5, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(lv_obj_5, SPACE_XS, 0);
        lv_obj_set_style_bg_color(lv_obj_5, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_border_color(lv_obj_5, COLOR_BORDER, 0);
        lv_obj_set_style_border_width(lv_obj_5, 1, 0);
        lv_obj_set_style_radius(lv_obj_5, RADIUS_CARD, 0);
        lv_obj_t * lv_label_3 = lv_label_create(lv_obj_5);
        lv_label_set_text(lv_label_3, "HEATER OUTPUT");
        lv_obj_set_style_text_color(lv_label_3, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_3, font_body, 0);

        lv_obj_t * lv_label_4 = lv_label_create(lv_obj_5);
        lv_label_bind_text(lv_label_4, &subject_heater_output, "%d%%");
        lv_obj_set_style_text_color(lv_label_4, COLOR_TEXT_PRIMARY, 0);
        lv_obj_set_style_text_font(lv_label_4, font_h2, 0);

        lv_obj_t * lv_obj_6 = lv_obj_create(lv_obj_1);
        lv_obj_set_width(lv_obj_6, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_6, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_6, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(lv_obj_6, SPACE_SM, 0);
        lv_obj_set_style_pad_row(lv_obj_6, SPACE_XS, 0);
        lv_obj_set_style_bg_color(lv_obj_6, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_border_color(lv_obj_6, COLOR_BORDER, 0);
        lv_obj_set_style_border_width(lv_obj_6, 1, 0);
        lv_obj_set_style_radius(lv_obj_6, RADIUS_CARD, 0);
        lv_obj_t * lv_label_5 = lv_label_create(lv_obj_6);
        lv_label_set_text(lv_label_5, "MANUAL TARGET SETPOINT");
        lv_obj_set_style_text_color(lv_label_5, COLOR_TEXT_SECONDARY, 0);
        lv_obj_set_style_text_font(lv_label_5, font_body, 0);
        lv_obj_set_style_text_letter_space(lv_label_5, 1, 0);

        lv_obj_t * lv_obj_7 = lv_obj_create(lv_obj_6);
        lv_obj_set_width(lv_obj_7, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_7, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(lv_obj_7, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_7, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_ver(lv_obj_7, SPACE_XS, 0);
        button_create(lv_obj_7, "-", NULL, COLOR_SURFACE_ELEVATED, COLOR_TEXT_PRIMARY, RADIUS_DEFAULT);

        lv_obj_t * lv_obj_8 = lv_obj_create(lv_obj_7);
        lv_obj_set_flex_flow(lv_obj_8, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_8, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_row(lv_obj_8, 0, 0);
        lv_obj_t * lv_label_6 = lv_label_create(lv_obj_8);
        lv_label_bind_text(lv_label_6, &subject_manual_setpoint, "%d°C");
        lv_obj_set_style_text_color(lv_label_6, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_6, font_h2, 0);

        lv_obj_t * lv_label_7 = lv_label_create(lv_obj_8);
        lv_label_set_text(lv_label_7, "SETPOINT");
        lv_obj_set_style_text_color(lv_label_7, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_7, font_body, 0);

        button_create(lv_obj_7, "+", NULL, COLOR_SURFACE_ELEVATED, COLOR_TEXT_PRIMARY, RADIUS_DEFAULT);

        lv_obj_t * slider_0 = slider_create(lv_obj_6, &subject_manual_setpoint, 0, 100, COLOR_ACCENT);
        lv_obj_set_width(slider_0, lv_pct(100));
        lv_obj_set_height(slider_0, 12);

        button_create(lv_obj_1, "START HEATING CYCLE", icon_flame, COLOR_ACCENT, COLOR_ACCENT_TEXT, RADIUS_DEFAULT);

        lv_obj_t * lv_obj_9 = lv_obj_create(column_0);
        lv_obj_set_width(lv_obj_9, lv_pct(100));
        lv_obj_set_height(lv_obj_9, 40);
        lv_obj_set_flex_flow(lv_obj_9, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_9, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_9, LV_FLEX_ALIGN_SPACE_AROUND, 0);
        lv_obj_set_style_pad_hor(lv_obj_9, 2, 0);
        lv_obj_set_style_bg_color(lv_obj_9, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_border_color(lv_obj_9, COLOR_BORDER, 0);
        lv_obj_set_style_border_width(lv_obj_9, 1, 0);
        lv_obj_set_style_border_side(lv_obj_9, LV_BORDER_SIDE_TOP, 0);
        lv_obj_t * lv_obj_10 = lv_obj_create(lv_obj_9);
        lv_obj_set_width(lv_obj_10, 44);
        lv_obj_set_height(lv_obj_10, 34);
        lv_obj_set_flex_flow(lv_obj_10, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_10, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_10, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_10, RADIUS_DEFAULT, 0);
        lv_obj_set_flag(lv_obj_10, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_screen_load_event(lv_obj_10, LV_EVENT_CLICKED, screen_home, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);
        lv_obj_t * lv_image_1 = lv_image_create(lv_obj_10);
        lv_image_set_src(lv_image_1, icon_home);
        lv_obj_set_style_image_recolor(lv_image_1, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_1, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_8 = lv_label_create(lv_obj_10);
        lv_label_set_text(lv_label_8, "HOME");
        lv_obj_set_style_text_color(lv_label_8, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_8, font_body, 0);

        lv_obj_t * lv_obj_11 = lv_obj_create(lv_obj_9);
        lv_obj_set_width(lv_obj_11, 44);
        lv_obj_set_height(lv_obj_11, 34);
        lv_obj_set_flex_flow(lv_obj_11, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_11, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_11, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_11, RADIUS_DEFAULT, 0);
        lv_obj_set_flag(lv_obj_11, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_screen_load_event(lv_obj_11, LV_EVENT_CLICKED, screen_profiles, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);
        lv_obj_t * lv_image_2 = lv_image_create(lv_obj_11);
        lv_image_set_src(lv_image_2, icon_layers);
        lv_obj_set_style_image_recolor(lv_image_2, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_2, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_9 = lv_label_create(lv_obj_11);
        lv_label_set_text(lv_label_9, "PROF");
        lv_obj_set_style_text_color(lv_label_9, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_9, font_body, 0);

        lv_obj_t * lv_obj_12 = lv_obj_create(lv_obj_9);
        lv_obj_set_width(lv_obj_12, 44);
        lv_obj_set_height(lv_obj_12, 34);
        lv_obj_set_flex_flow(lv_obj_12, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_12, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_12, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_12, RADIUS_DEFAULT, 0);
        lv_obj_set_style_bg_color(lv_obj_12, COLOR_SURFACE_ELEVATED, 0);
        lv_obj_set_style_border_color(lv_obj_12, COLOR_ACCENT, 0);
        lv_obj_set_style_border_width(lv_obj_12, 1, 0);
        lv_obj_set_flag(lv_obj_12, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_t * lv_image_3 = lv_image_create(lv_obj_12);
        lv_image_set_src(lv_image_3, icon_sliders);
        lv_obj_set_style_image_recolor(lv_image_3, COLOR_ACCENT, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_3, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_10 = lv_label_create(lv_obj_12);
        lv_label_set_text(lv_label_10, "MAN");
        lv_obj_set_style_text_color(lv_label_10, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_10, font_body, 0);

        lv_obj_t * lv_obj_13 = lv_obj_create(lv_obj_9);
        lv_obj_set_width(lv_obj_13, 44);
        lv_obj_set_height(lv_obj_13, 34);
        lv_obj_set_flex_flow(lv_obj_13, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_13, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_13, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_13, RADIUS_DEFAULT, 0);
        lv_obj_set_flag(lv_obj_13, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_screen_load_event(lv_obj_13, LV_EVENT_CLICKED, screen_settings, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);
        lv_obj_t * lv_image_4 = lv_image_create(lv_obj_13);
        lv_image_set_src(lv_image_4, icon_settings);
        lv_obj_set_style_image_recolor(lv_image_4, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_4, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_11 = lv_label_create(lv_obj_13);
        lv_label_set_text(lv_label_11, "SETT");
        lv_obj_set_style_text_color(lv_label_11, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_11, font_body, 0);

        lv_obj_t * lv_obj_14 = lv_obj_create(lv_obj_9);
        lv_obj_set_width(lv_obj_14, 44);
        lv_obj_set_height(lv_obj_14, 34);
        lv_obj_set_flex_flow(lv_obj_14, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_14, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_14, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_14, RADIUS_DEFAULT, 0);
        lv_obj_set_flag(lv_obj_14, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_screen_load_event(lv_obj_14, LV_EVENT_CLICKED, screen_info, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);
        lv_obj_t * lv_image_5 = lv_image_create(lv_obj_14);
        lv_image_set_src(lv_image_5, icon_info);
        lv_obj_set_style_image_recolor(lv_image_5, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_5, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_12 = lv_label_create(lv_obj_14);
        lv_label_set_text(lv_label_12, "INFO");
        lv_obj_set_style_text_color(lv_label_12, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_12, font_body, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

