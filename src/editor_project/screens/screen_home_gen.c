/**
 * @file screen_home_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "screen_home_gen.h"
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

lv_obj_t * screen_home_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if SRC_CHECK_COMPILE_TARGET(SRC_TARGET_ALL)
    if (src_check_target(SRC_TARGET_ALL)) {
        if (screen_home == NULL) screen_home = lv_obj_create(NULL);
        lv_obj_t * lv_obj_0 = screen_home;
        lv_obj_set_name_static(lv_obj_0, "screen_home_#");
        lv_obj_set_width(lv_obj_0, 240);
        lv_obj_set_height(lv_obj_0, 320);

        lv_obj_add_style(lv_obj_0, &style_screen_dark, 0);
        lv_obj_t * column_0 = column_create(lv_obj_0, 0, 3, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        header_create(column_0, "REFLOW OVEN", "12:45", icon_flame);

        lv_obj_t * lv_obj_1 = lv_obj_create(column_0);
        lv_obj_set_width(lv_obj_1, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_1, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_hor(lv_obj_1, SPACE_SM, 0);
        lv_obj_set_style_pad_ver(lv_obj_1, 2, 0);
        lv_obj_set_style_pad_row(lv_obj_1, 3, 0);
        temp_display_create(lv_obj_1, "183°C", "217°C");

        lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_1);
        lv_obj_set_width(lv_obj_2, lv_pct(100));
        lv_obj_set_height(lv_obj_2, 30);
        lv_obj_set_flex_flow(lv_obj_2, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(lv_obj_2, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_t * lv_obj_3 = lv_obj_create(lv_obj_2);
        lv_obj_set_width(lv_obj_3, 114);
        lv_obj_set_height(lv_obj_3, 30);
        lv_obj_set_flex_flow(lv_obj_3, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(lv_obj_3, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_3, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_hor(lv_obj_3, SPACE_SM, 0);
        lv_obj_set_style_bg_color(lv_obj_3, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_border_color(lv_obj_3, COLOR_BORDER, 0);
        lv_obj_set_style_border_width(lv_obj_3, 1, 0);
        lv_obj_set_style_radius(lv_obj_3, RADIUS_CARD, 0);
        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_3);
        lv_label_set_text(lv_label_0, "STAGE");
        lv_obj_set_style_text_color(lv_label_0, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_0, font_body, 0);

        lv_obj_t * lv_obj_4 = lv_obj_create(lv_obj_3);
        lv_obj_set_flex_flow(lv_obj_4, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_4, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_hor(lv_obj_4, 6, 0);
        lv_obj_set_style_pad_ver(lv_obj_4, 1, 0);
        lv_obj_set_style_bg_color(lv_obj_4, COLOR_ACCENT, 0);
        lv_obj_set_style_radius(lv_obj_4, RADIUS_PILL, 0);
        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_4);
        lv_label_set_text(lv_label_1, "REFLOW");
        lv_obj_set_style_text_color(lv_label_1, COLOR_ACCENT_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_1, font_h5, 0);

        lv_obj_t * lv_obj_5 = lv_obj_create(lv_obj_2);
        lv_obj_set_width(lv_obj_5, 114);
        lv_obj_set_height(lv_obj_5, 30);
        lv_obj_set_flex_flow(lv_obj_5, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(lv_obj_5, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_5, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_hor(lv_obj_5, SPACE_SM, 0);
        lv_obj_set_style_bg_color(lv_obj_5, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_border_color(lv_obj_5, COLOR_BORDER, 0);
        lv_obj_set_style_border_width(lv_obj_5, 1, 0);
        lv_obj_set_style_radius(lv_obj_5, RADIUS_CARD, 0);
        lv_obj_t * lv_label_2 = lv_label_create(lv_obj_5);
        lv_label_set_text(lv_label_2, "HEATER");
        lv_obj_set_style_text_color(lv_label_2, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_2, font_body, 0);

        lv_obj_t * lv_obj_6 = lv_obj_create(lv_obj_5);
        lv_obj_set_flex_flow(lv_obj_6, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_6, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_column(lv_obj_6, 4, 0);
        lv_obj_t * bar_0 = bar_create(lv_obj_6, &subject_heater_output, 0, 100, COLOR_ACCENT);
        lv_obj_set_width(bar_0, 36);
        lv_obj_set_height(bar_0, 8);

        lv_obj_t * lv_label_3 = lv_label_create(lv_obj_6);
        lv_label_bind_text(lv_label_3, &subject_heater_output, "%d%%");
        lv_obj_set_style_text_color(lv_label_3, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_3, font_h5, 0);

        lv_obj_t * lv_obj_7 = lv_obj_create(lv_obj_1);
        lv_obj_set_width(lv_obj_7, lv_pct(100));
        lv_obj_set_height(lv_obj_7, 66);
        lv_obj_set_flex_flow(lv_obj_7, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_all(lv_obj_7, 4, 0);
        lv_obj_set_style_pad_row(lv_obj_7, 2, 0);
        lv_obj_set_style_bg_color(lv_obj_7, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_border_color(lv_obj_7, COLOR_BORDER, 0);
        lv_obj_set_style_border_width(lv_obj_7, 1, 0);
        lv_obj_set_style_radius(lv_obj_7, RADIUS_CARD, 0);
        lv_obj_t * lv_obj_8 = lv_obj_create(lv_obj_7);
        lv_obj_set_width(lv_obj_8, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_8, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(lv_obj_8, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_8, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_hor(lv_obj_8, 2, 0);
        lv_obj_t * lv_label_4 = lv_label_create(lv_obj_8);
        lv_label_set_text(lv_label_4, "PROFILE TEMP CURVE (°C)");
        lv_obj_set_style_text_color(lv_label_4, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_4, font_body, 0);

        lv_obj_t * lv_label_5 = lv_label_create(lv_obj_8);
        lv_label_set_text(lv_label_5, "245°C PEAK");
        lv_obj_set_style_text_color(lv_label_5, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_5, font_body, 0);

        lv_obj_t * lv_chart_0 = lv_chart_create(lv_obj_7);
        lv_obj_set_width(lv_chart_0, lv_pct(100));
        lv_obj_set_height(lv_chart_0, 46);
        lv_chart_set_type(lv_chart_0, LV_CHART_TYPE_LINE);
        lv_chart_set_point_count(lv_chart_0, 12);
        lv_obj_set_style_bg_color(lv_chart_0, COLOR_DARK_BG, 0);
        lv_obj_set_style_border_color(lv_chart_0, COLOR_BORDER, 0);
        lv_obj_set_style_border_width(lv_chart_0, 1, 0);
        lv_obj_set_style_radius(lv_chart_0, 4, 0);

        stage_timeline_create(lv_obj_1, 2);

        lv_obj_t * lv_obj_9 = lv_obj_create(lv_obj_1);
        lv_obj_set_width(lv_obj_9, lv_pct(100));
        lv_obj_set_height(lv_obj_9, 26);
        lv_obj_set_flex_flow(lv_obj_9, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(lv_obj_9, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_9, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_hor(lv_obj_9, SPACE_SM, 0);
        lv_obj_set_style_bg_color(lv_obj_9, COLOR_SURFACE_ELEVATED, 0);
        lv_obj_set_style_border_color(lv_obj_9, COLOR_BORDER, 0);
        lv_obj_set_style_border_width(lv_obj_9, 1, 0);
        lv_obj_set_style_radius(lv_obj_9, RADIUS_CARD, 0);
        lv_obj_set_flag(lv_obj_9, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_screen_load_event(lv_obj_9, LV_EVENT_CLICKED, screen_profiles, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);
        lv_obj_t * lv_obj_10 = lv_obj_create(lv_obj_9);
        lv_obj_set_flex_flow(lv_obj_10, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_10, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_column(lv_obj_10, SPACE_XS, 0);
        lv_obj_t * lv_image_0 = lv_image_create(lv_obj_10);
        lv_image_set_src(lv_image_0, icon_layers);
        lv_obj_set_style_image_recolor(lv_image_0, COLOR_ACCENT, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_0, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_6 = lv_label_create(lv_obj_10);
        lv_label_set_text(lv_label_6, "PROFILE:");
        lv_obj_set_style_text_color(lv_label_6, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_6, font_body, 0);

        lv_obj_t * lv_label_7 = lv_label_create(lv_obj_10);
        lv_label_set_text(lv_label_7, "SAC305 Lead Free");
        lv_obj_set_style_text_color(lv_label_7, COLOR_TEXT_PRIMARY, 0);
        lv_obj_set_style_text_font(lv_label_7, font_h5, 0);

        lv_obj_t * lv_image_1 = lv_image_create(lv_obj_9);
        lv_image_set_src(lv_image_1, icon_chevron_right);
        lv_obj_set_style_image_recolor(lv_image_1, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_1, (255 * 100 / 100), 0);

        lv_obj_t * lv_obj_11 = lv_obj_create(lv_obj_1);
        lv_obj_set_width(lv_obj_11, lv_pct(100));
        lv_obj_set_height(lv_obj_11, 32);
        lv_obj_set_flex_flow(lv_obj_11, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(lv_obj_11, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_11, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_column(lv_obj_11, SPACE_XS, 0);
        button_create(lv_obj_11, "PAUSE", icon_pause, COLOR_DARK_PANEL, COLOR_TEXT_PRIMARY, RADIUS_DEFAULT);

        button_create(lv_obj_11, "STOP", icon_close, COLOR_DANGER, COLOR_ACCENT_TEXT, RADIUS_DEFAULT);

        button_create(lv_obj_11, "GRAPH", icon_chart, COLOR_DARK_PANEL, COLOR_TEXT_PRIMARY, RADIUS_DEFAULT);

        lv_obj_t * lv_obj_12 = lv_obj_create(column_0);
        lv_obj_set_width(lv_obj_12, lv_pct(100));
        lv_obj_set_height(lv_obj_12, 40);
        lv_obj_set_flex_flow(lv_obj_12, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_12, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_12, LV_FLEX_ALIGN_SPACE_AROUND, 0);
        lv_obj_set_style_pad_hor(lv_obj_12, 2, 0);
        lv_obj_set_style_bg_color(lv_obj_12, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_border_color(lv_obj_12, COLOR_BORDER, 0);
        lv_obj_set_style_border_width(lv_obj_12, 1, 0);
        lv_obj_set_style_border_side(lv_obj_12, LV_BORDER_SIDE_TOP, 0);
        lv_obj_t * lv_obj_13 = lv_obj_create(lv_obj_12);
        lv_obj_set_width(lv_obj_13, 44);
        lv_obj_set_height(lv_obj_13, 34);
        lv_obj_set_flex_flow(lv_obj_13, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_13, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_13, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_13, RADIUS_DEFAULT, 0);
        lv_obj_set_style_bg_color(lv_obj_13, COLOR_SURFACE_ELEVATED, 0);
        lv_obj_set_style_border_color(lv_obj_13, COLOR_ACCENT, 0);
        lv_obj_set_style_border_width(lv_obj_13, 1, 0);
        lv_obj_set_flag(lv_obj_13, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_t * lv_image_2 = lv_image_create(lv_obj_13);
        lv_image_set_src(lv_image_2, icon_home);
        lv_obj_set_style_image_recolor(lv_image_2, COLOR_ACCENT, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_2, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_8 = lv_label_create(lv_obj_13);
        lv_label_set_text(lv_label_8, "HOME");
        lv_obj_set_style_text_color(lv_label_8, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_8, font_body, 0);

        lv_obj_t * lv_obj_14 = lv_obj_create(lv_obj_12);
        lv_obj_set_width(lv_obj_14, 44);
        lv_obj_set_height(lv_obj_14, 34);
        lv_obj_set_flex_flow(lv_obj_14, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_14, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_14, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_14, RADIUS_DEFAULT, 0);
        lv_obj_set_flag(lv_obj_14, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_screen_load_event(lv_obj_14, LV_EVENT_CLICKED, screen_profiles, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);
        lv_obj_t * lv_image_3 = lv_image_create(lv_obj_14);
        lv_image_set_src(lv_image_3, icon_layers);
        lv_obj_set_style_image_recolor(lv_image_3, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_3, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_9 = lv_label_create(lv_obj_14);
        lv_label_set_text(lv_label_9, "PROF");
        lv_obj_set_style_text_color(lv_label_9, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_9, font_body, 0);

        lv_obj_t * lv_obj_15 = lv_obj_create(lv_obj_12);
        lv_obj_set_width(lv_obj_15, 44);
        lv_obj_set_height(lv_obj_15, 34);
        lv_obj_set_flex_flow(lv_obj_15, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_15, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_15, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_15, RADIUS_DEFAULT, 0);
        lv_obj_set_flag(lv_obj_15, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_screen_load_event(lv_obj_15, LV_EVENT_CLICKED, screen_manual, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);
        lv_obj_t * lv_image_4 = lv_image_create(lv_obj_15);
        lv_image_set_src(lv_image_4, icon_sliders);
        lv_obj_set_style_image_recolor(lv_image_4, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_4, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_10 = lv_label_create(lv_obj_15);
        lv_label_set_text(lv_label_10, "MAN");
        lv_obj_set_style_text_color(lv_label_10, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_10, font_body, 0);

        lv_obj_t * lv_obj_16 = lv_obj_create(lv_obj_12);
        lv_obj_set_width(lv_obj_16, 44);
        lv_obj_set_height(lv_obj_16, 34);
        lv_obj_set_flex_flow(lv_obj_16, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_16, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_16, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_16, RADIUS_DEFAULT, 0);
        lv_obj_set_flag(lv_obj_16, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_screen_load_event(lv_obj_16, LV_EVENT_CLICKED, screen_settings, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);
        lv_obj_t * lv_image_5 = lv_image_create(lv_obj_16);
        lv_image_set_src(lv_image_5, icon_settings);
        lv_obj_set_style_image_recolor(lv_image_5, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_5, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_11 = lv_label_create(lv_obj_16);
        lv_label_set_text(lv_label_11, "SETT");
        lv_obj_set_style_text_color(lv_label_11, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_11, font_body, 0);

        lv_obj_t * lv_obj_17 = lv_obj_create(lv_obj_12);
        lv_obj_set_width(lv_obj_17, 44);
        lv_obj_set_height(lv_obj_17, 34);
        lv_obj_set_flex_flow(lv_obj_17, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_17, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_17, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_17, RADIUS_DEFAULT, 0);
        lv_obj_set_flag(lv_obj_17, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_screen_load_event(lv_obj_17, LV_EVENT_CLICKED, screen_info, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);
        lv_obj_t * lv_image_6 = lv_image_create(lv_obj_17);
        lv_image_set_src(lv_image_6, icon_info);
        lv_obj_set_style_image_recolor(lv_image_6, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_6, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_12 = lv_label_create(lv_obj_17);
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

