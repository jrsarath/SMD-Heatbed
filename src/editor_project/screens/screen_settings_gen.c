/**
 * @file screen_settings_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "screen_settings_gen.h"
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

lv_obj_t * screen_settings_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if SRC_CHECK_COMPILE_TARGET(SRC_TARGET_ALL)
    if (src_check_target(SRC_TARGET_ALL)) {
        if (screen_settings == NULL) screen_settings = lv_obj_create(NULL);
        lv_obj_t * lv_obj_0 = screen_settings;
        lv_obj_set_name_static(lv_obj_0, "screen_settings_#");
        lv_obj_set_width(lv_obj_0, 240);
        lv_obj_set_height(lv_obj_0, 320);

        lv_obj_add_style(lv_obj_0, &style_screen_dark, 0);
        lv_obj_t * column_0 = column_create(lv_obj_0, 0, 2, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        header_create(column_0, "SETTINGS", "12:45", icon_settings);

        lv_obj_t * lv_obj_1 = lv_obj_create(column_0);
        lv_obj_set_width(lv_obj_1, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_1, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_hor(lv_obj_1, SPACE_SM, 0);
        lv_obj_set_style_pad_ver(lv_obj_1, 2, 0);
        lv_obj_set_style_pad_row(lv_obj_1, 4, 0);
        lv_obj_t * list_0 = list_create(lv_obj_1, 0, 0);
        lv_obj_set_width(list_0, lv_pct(100));
        lv_obj_set_style_bg_color(list_0, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_border_color(list_0, COLOR_BORDER, 0);
        lv_obj_set_style_radius(list_0, RADIUS_CARD, 0);
        list_section_create(list_0, "DISPLAY & CONTROL");

        lv_obj_t * list_item_0 = list_item_create(list_0, "Backlight", "Display intensity", icon_settings);
        lv_obj_t * list_item_0_trailing = list_item_get_trailing(list_item_0);
        if (list_item_0_trailing) {
        lv_obj_t * lv_obj_2 = lv_obj_create(list_item_0_trailing);
        lv_obj_set_flex_flow(lv_obj_2, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_column(lv_obj_2, SPACE_XS, 0);
        lv_obj_t * slider_0 = slider_create(lv_obj_2, &subject_brightness, 0, 100, COLOR_ACCENT);
        lv_obj_set_width(slider_0, 60);
        lv_obj_set_height(slider_0, 10);

        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_2);
        lv_label_bind_text(lv_label_0, &subject_brightness, "%d%%");
        lv_obj_set_style_text_color(lv_label_0, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_0, font_body, 0);
        } else {
        LV_LOG_WARN("`trailing` slot of `list_item_0` doesn't exist");
        }

        lv_obj_t * list_item_1 = list_item_create(list_0, "Beeper Sound", "Audible alerts", icon_info);
        lv_obj_t * list_item_1_trailing = list_item_get_trailing(list_item_1);
        if (list_item_1_trailing) {
        switch_create(list_item_1_trailing, &subject_beeper, COLOR_ACCENT);
        } else {
        LV_LOG_WARN("`trailing` slot of `list_item_1` doesn't exist");
        }

        list_separator_create(list_0);

        list_section_create(list_0, "THERMAL SAFETY");

        lv_obj_t * list_item_2 = list_item_create(list_0, "Overtemp Limit", "Hardware cutoff", icon_flame);
        lv_obj_t * list_item_2_trailing = list_item_get_trailing(list_item_2);
        if (list_item_2_trailing) {
        lv_obj_t * lv_label_1 = lv_label_create(list_item_2_trailing);
        lv_label_set_text(lv_label_1, "250°C");
        lv_obj_set_style_text_color(lv_label_1, COLOR_DANGER, 0);
        lv_obj_set_style_text_font(lv_label_1, font_h5, 0);
        } else {
        LV_LOG_WARN("`trailing` slot of `list_item_2` doesn't exist");
        }

        lv_obj_t * list_item_3 = list_item_create(list_0, "NTC Offset", "Beta 3950 calibration", icon_thermometer);
        lv_obj_t * list_item_3_trailing = list_item_get_trailing(list_item_3);
        if (list_item_3_trailing) {
        lv_obj_t * lv_label_2 = lv_label_create(list_item_3_trailing);
        lv_label_set_text(lv_label_2, "0.0°C");
        lv_obj_set_style_text_color(lv_label_2, COLOR_TEXT_PRIMARY, 0);
        lv_obj_set_style_text_font(lv_label_2, font_h5, 0);
        } else {
        LV_LOG_WARN("`trailing` slot of `list_item_3` doesn't exist");
        }

        lv_obj_t * list_item_4 = list_item_create(list_0, "Thermal Guard", "18s / 2°C threshold", icon_check);
        lv_obj_t * list_item_4_trailing = list_item_get_trailing(list_item_4);
        if (list_item_4_trailing) {
        lv_obj_t * lv_label_3 = lv_label_create(list_item_4_trailing);
        lv_label_set_text(lv_label_3, "ENABLED");
        lv_obj_set_style_text_color(lv_label_3, COLOR_SUCCESS, 0);
        lv_obj_set_style_text_font(lv_label_3, font_h5, 0);
        } else {
        LV_LOG_WARN("`trailing` slot of `list_item_4` doesn't exist");
        }

        lv_obj_t * lv_obj_3 = lv_obj_create(column_0);
        lv_obj_set_width(lv_obj_3, lv_pct(100));
        lv_obj_set_height(lv_obj_3, 40);
        lv_obj_set_flex_flow(lv_obj_3, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_3, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_3, LV_FLEX_ALIGN_SPACE_AROUND, 0);
        lv_obj_set_style_pad_hor(lv_obj_3, 2, 0);
        lv_obj_set_style_bg_color(lv_obj_3, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_border_color(lv_obj_3, COLOR_BORDER, 0);
        lv_obj_set_style_border_width(lv_obj_3, 1, 0);
        lv_obj_set_style_border_side(lv_obj_3, LV_BORDER_SIDE_TOP, 0);
        lv_obj_t * lv_obj_4 = lv_obj_create(lv_obj_3);
        lv_obj_set_width(lv_obj_4, 44);
        lv_obj_set_height(lv_obj_4, 34);
        lv_obj_set_flex_flow(lv_obj_4, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_4, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_4, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_4, RADIUS_DEFAULT, 0);
        lv_obj_set_flag(lv_obj_4, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_screen_load_event(lv_obj_4, LV_EVENT_CLICKED, screen_home, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);
        lv_obj_t * lv_image_0 = lv_image_create(lv_obj_4);
        lv_image_set_src(lv_image_0, icon_home);
        lv_obj_set_style_image_recolor(lv_image_0, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_0, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_4 = lv_label_create(lv_obj_4);
        lv_label_set_text(lv_label_4, "HOME");
        lv_obj_set_style_text_color(lv_label_4, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_4, font_body, 0);

        lv_obj_t * lv_obj_5 = lv_obj_create(lv_obj_3);
        lv_obj_set_width(lv_obj_5, 44);
        lv_obj_set_height(lv_obj_5, 34);
        lv_obj_set_flex_flow(lv_obj_5, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_5, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_5, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_5, RADIUS_DEFAULT, 0);
        lv_obj_set_flag(lv_obj_5, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_screen_load_event(lv_obj_5, LV_EVENT_CLICKED, screen_profiles, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);
        lv_obj_t * lv_image_1 = lv_image_create(lv_obj_5);
        lv_image_set_src(lv_image_1, icon_layers);
        lv_obj_set_style_image_recolor(lv_image_1, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_1, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_5 = lv_label_create(lv_obj_5);
        lv_label_set_text(lv_label_5, "PROF");
        lv_obj_set_style_text_color(lv_label_5, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_5, font_body, 0);

        lv_obj_t * lv_obj_6 = lv_obj_create(lv_obj_3);
        lv_obj_set_width(lv_obj_6, 44);
        lv_obj_set_height(lv_obj_6, 34);
        lv_obj_set_flex_flow(lv_obj_6, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_6, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_6, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_6, RADIUS_DEFAULT, 0);
        lv_obj_set_flag(lv_obj_6, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_screen_load_event(lv_obj_6, LV_EVENT_CLICKED, screen_manual, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);
        lv_obj_t * lv_image_2 = lv_image_create(lv_obj_6);
        lv_image_set_src(lv_image_2, icon_sliders);
        lv_obj_set_style_image_recolor(lv_image_2, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_2, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_6 = lv_label_create(lv_obj_6);
        lv_label_set_text(lv_label_6, "MAN");
        lv_obj_set_style_text_color(lv_label_6, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_6, font_body, 0);

        lv_obj_t * lv_obj_7 = lv_obj_create(lv_obj_3);
        lv_obj_set_width(lv_obj_7, 44);
        lv_obj_set_height(lv_obj_7, 34);
        lv_obj_set_flex_flow(lv_obj_7, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_7, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_7, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_7, RADIUS_DEFAULT, 0);
        lv_obj_set_style_bg_color(lv_obj_7, COLOR_SURFACE_ELEVATED, 0);
        lv_obj_set_style_border_color(lv_obj_7, COLOR_ACCENT, 0);
        lv_obj_set_style_border_width(lv_obj_7, 1, 0);
        lv_obj_set_flag(lv_obj_7, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_t * lv_image_3 = lv_image_create(lv_obj_7);
        lv_image_set_src(lv_image_3, icon_settings);
        lv_obj_set_style_image_recolor(lv_image_3, COLOR_ACCENT, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_3, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_7 = lv_label_create(lv_obj_7);
        lv_label_set_text(lv_label_7, "SETT");
        lv_obj_set_style_text_color(lv_label_7, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_7, font_body, 0);

        lv_obj_t * lv_obj_8 = lv_obj_create(lv_obj_3);
        lv_obj_set_width(lv_obj_8, 44);
        lv_obj_set_height(lv_obj_8, 34);
        lv_obj_set_flex_flow(lv_obj_8, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_8, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_8, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_8, RADIUS_DEFAULT, 0);
        lv_obj_set_flag(lv_obj_8, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_screen_load_event(lv_obj_8, LV_EVENT_CLICKED, screen_info, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);
        lv_obj_t * lv_image_4 = lv_image_create(lv_obj_8);
        lv_image_set_src(lv_image_4, icon_info);
        lv_obj_set_style_image_recolor(lv_image_4, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_4, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_8 = lv_label_create(lv_obj_8);
        lv_label_set_text(lv_label_8, "INFO");
        lv_obj_set_style_text_color(lv_label_8, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_8, font_body, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

