/**
 * @file screen_profiles_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "screen_profiles_gen.h"
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

lv_obj_t * screen_profiles_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if SRC_CHECK_COMPILE_TARGET(SRC_TARGET_ALL)
    if (src_check_target(SRC_TARGET_ALL)) {
        if (screen_profiles == NULL) screen_profiles = lv_obj_create(NULL);
        lv_obj_t * lv_obj_0 = screen_profiles;
        lv_obj_set_name_static(lv_obj_0, "screen_profiles_#");
        lv_obj_set_width(lv_obj_0, 240);
        lv_obj_set_height(lv_obj_0, 320);

        lv_obj_add_style(lv_obj_0, &style_screen_dark, 0);
        lv_obj_t * column_0 = column_create(lv_obj_0, 0, 2, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        header_create(column_0, "REFLOW PROFILES", "12:45", icon_layers);

        lv_obj_t * lv_obj_1 = lv_obj_create(column_0);
        lv_obj_set_width(lv_obj_1, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_1, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_hor(lv_obj_1, SPACE_SM, 0);
        lv_obj_set_style_pad_ver(lv_obj_1, 2, 0);
        lv_obj_set_style_pad_row(lv_obj_1, 4, 0);
        lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_1);
        lv_obj_set_width(lv_obj_2, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_2, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_all(lv_obj_2, SPACE_SM, 0);
        lv_obj_set_style_pad_row(lv_obj_2, 2, 0);
        lv_obj_set_style_bg_color(lv_obj_2, COLOR_SURFACE_ELEVATED, 0);
        lv_obj_set_style_border_color(lv_obj_2, COLOR_ACCENT, 0);
        lv_obj_set_style_border_width(lv_obj_2, 1, 0);
        lv_obj_set_style_radius(lv_obj_2, RADIUS_CARD, 0);
        lv_obj_t * lv_obj_3 = lv_obj_create(lv_obj_2);
        lv_obj_set_width(lv_obj_3, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_3, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(lv_obj_3, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_3, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_t * lv_obj_4 = lv_obj_create(lv_obj_3);
        lv_obj_set_flex_flow(lv_obj_4, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_4, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_column(lv_obj_4, SPACE_XS, 0);
        lv_obj_t * lv_image_0 = lv_image_create(lv_obj_4);
        lv_image_set_src(lv_image_0, icon_check);
        lv_obj_set_style_image_recolor(lv_image_0, COLOR_SUCCESS, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_0, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_4);
        lv_label_set_text(lv_label_0, "ACTIVE PROFILE");
        lv_obj_set_style_text_color(lv_label_0, COLOR_SUCCESS, 0);
        lv_obj_set_style_text_font(lv_label_0, font_h5, 0);

        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_3);
        lv_label_set_text(lv_label_1, "SAC305");
        lv_obj_set_style_text_color(lv_label_1, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_1, font_h4, 0);

        lv_obj_t * lv_obj_5 = lv_obj_create(lv_obj_2);
        lv_obj_set_width(lv_obj_5, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_5, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(lv_obj_5, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_5, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_ver(lv_obj_5, 2, 0);
        lv_obj_t * lv_obj_6 = lv_obj_create(lv_obj_5);
        lv_obj_set_flex_flow(lv_obj_6, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_row(lv_obj_6, 0, 0);
        lv_obj_t * lv_label_2 = lv_label_create(lv_obj_6);
        lv_label_set_text(lv_label_2, "SOAK TEMP");
        lv_obj_set_style_text_color(lv_label_2, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_2, font_body, 0);

        lv_obj_t * lv_label_3 = lv_label_create(lv_obj_6);
        lv_label_set_text(lv_label_3, "150 - 180°C");
        lv_obj_set_style_text_color(lv_label_3, COLOR_TEXT_PRIMARY, 0);
        lv_obj_set_style_text_font(lv_label_3, font_h5, 0);

        lv_obj_t * lv_obj_7 = lv_obj_create(lv_obj_5);
        lv_obj_set_flex_flow(lv_obj_7, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_row(lv_obj_7, 0, 0);
        lv_obj_t * lv_label_4 = lv_label_create(lv_obj_7);
        lv_label_set_text(lv_label_4, "REFLOW");
        lv_obj_set_style_text_color(lv_label_4, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_4, font_body, 0);

        lv_obj_t * lv_label_5 = lv_label_create(lv_obj_7);
        lv_label_set_text(lv_label_5, ">217°C (60s)");
        lv_obj_set_style_text_color(lv_label_5, COLOR_TEXT_PRIMARY, 0);
        lv_obj_set_style_text_font(lv_label_5, font_h5, 0);

        lv_obj_t * lv_obj_8 = lv_obj_create(lv_obj_5);
        lv_obj_set_flex_flow(lv_obj_8, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_row(lv_obj_8, 0, 0);
        lv_obj_t * lv_label_6 = lv_label_create(lv_obj_8);
        lv_label_set_text(lv_label_6, "PEAK TEMP");
        lv_obj_set_style_text_color(lv_label_6, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_6, font_body, 0);

        lv_obj_t * lv_label_7 = lv_label_create(lv_obj_8);
        lv_label_set_text(lv_label_7, "245°C");
        lv_obj_set_style_text_color(lv_label_7, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_7, font_h5, 0);

        lv_obj_t * lv_label_8 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_8, "AVAILABLE PRESETS");
        lv_obj_set_style_text_color(lv_label_8, COLOR_TEXT_SECONDARY, 0);
        lv_obj_set_style_text_font(lv_label_8, font_body, 0);
        lv_obj_set_style_text_letter_space(lv_label_8, 1, 0);

        lv_obj_t * lv_obj_9 = lv_obj_create(lv_obj_1);
        lv_obj_set_width(lv_obj_9, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_9, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_row(lv_obj_9, SPACE_XS, 0);
        lv_obj_t * lv_obj_10 = lv_obj_create(lv_obj_9);
        lv_obj_set_width(lv_obj_10, lv_pct(100));
        lv_obj_set_height(lv_obj_10, 32);
        lv_obj_set_flex_flow(lv_obj_10, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(lv_obj_10, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_10, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_hor(lv_obj_10, SPACE_SM, 0);
        lv_obj_set_style_bg_color(lv_obj_10, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_border_color(lv_obj_10, COLOR_ACCENT, 0);
        lv_obj_set_style_border_width(lv_obj_10, 2, 0);
        lv_obj_set_style_radius(lv_obj_10, RADIUS_CARD, 0);
        lv_obj_t * lv_obj_11 = lv_obj_create(lv_obj_10);
        lv_obj_set_flex_flow(lv_obj_11, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_11, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_column(lv_obj_11, SPACE_XS, 0);
        lv_obj_t * lv_image_1 = lv_image_create(lv_obj_11);
        lv_image_set_src(lv_image_1, icon_layers);
        lv_obj_set_style_image_recolor(lv_image_1, COLOR_ACCENT, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_1, (255 * 100 / 100), 0);

        lv_obj_t * lv_obj_12 = lv_obj_create(lv_obj_11);
        lv_obj_set_flex_flow(lv_obj_12, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_row(lv_obj_12, 0, 0);
        lv_obj_t * lv_label_9 = lv_label_create(lv_obj_12);
        lv_label_set_text(lv_label_9, "SAC305 Lead Free");
        lv_obj_set_style_text_color(lv_label_9, COLOR_TEXT_PRIMARY, 0);
        lv_obj_set_style_text_font(lv_label_9, font_h5, 0);

        lv_obj_t * lv_label_10 = lv_label_create(lv_obj_12);
        lv_label_set_text(lv_label_10, "Sn96.5 / Ag3.0 / Cu0.5 (Peak 245°C)");
        lv_obj_set_style_text_color(lv_label_10, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_10, font_body, 0);

        lv_obj_t * lv_label_11 = lv_label_create(lv_obj_10);
        lv_label_set_text(lv_label_11, "●");
        lv_obj_set_style_text_color(lv_label_11, COLOR_ACCENT, 0);

        lv_obj_t * lv_obj_13 = lv_obj_create(lv_obj_9);
        lv_obj_set_width(lv_obj_13, lv_pct(100));
        lv_obj_set_height(lv_obj_13, 32);
        lv_obj_set_flex_flow(lv_obj_13, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(lv_obj_13, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_13, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_hor(lv_obj_13, SPACE_SM, 0);
        lv_obj_set_style_bg_color(lv_obj_13, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_border_color(lv_obj_13, COLOR_BORDER, 0);
        lv_obj_set_style_border_width(lv_obj_13, 1, 0);
        lv_obj_set_style_radius(lv_obj_13, RADIUS_CARD, 0);
        lv_obj_t * lv_obj_14 = lv_obj_create(lv_obj_13);
        lv_obj_set_flex_flow(lv_obj_14, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_14, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_column(lv_obj_14, SPACE_XS, 0);
        lv_obj_t * lv_image_2 = lv_image_create(lv_obj_14);
        lv_image_set_src(lv_image_2, icon_layers);
        lv_obj_set_style_image_recolor(lv_image_2, COLOR_TEXT_SECONDARY, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_2, (255 * 100 / 100), 0);

        lv_obj_t * lv_obj_15 = lv_obj_create(lv_obj_14);
        lv_obj_set_flex_flow(lv_obj_15, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_row(lv_obj_15, 0, 0);
        lv_obj_t * lv_label_12 = lv_label_create(lv_obj_15);
        lv_label_set_text(lv_label_12, "Sn63 / Pb37 Leaded");
        lv_obj_set_style_text_color(lv_label_12, COLOR_TEXT_PRIMARY, 0);
        lv_obj_set_style_text_font(lv_label_12, font_h5, 0);

        lv_obj_t * lv_label_13 = lv_label_create(lv_obj_15);
        lv_label_set_text(lv_label_13, "Standard Eutectic (Peak 215°C)");
        lv_obj_set_style_text_color(lv_label_13, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_13, font_body, 0);

        lv_obj_t * lv_label_14 = lv_label_create(lv_obj_13);
        lv_label_set_text(lv_label_14, "○");
        lv_obj_set_style_text_color(lv_label_14, COLOR_TEXT_MUTED, 0);

        lv_obj_t * lv_obj_16 = lv_obj_create(lv_obj_9);
        lv_obj_set_width(lv_obj_16, lv_pct(100));
        lv_obj_set_height(lv_obj_16, 32);
        lv_obj_set_flex_flow(lv_obj_16, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(lv_obj_16, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_16, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_hor(lv_obj_16, SPACE_SM, 0);
        lv_obj_set_style_bg_color(lv_obj_16, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_border_color(lv_obj_16, COLOR_BORDER, 0);
        lv_obj_set_style_border_width(lv_obj_16, 1, 0);
        lv_obj_set_style_radius(lv_obj_16, RADIUS_CARD, 0);
        lv_obj_t * lv_obj_17 = lv_obj_create(lv_obj_16);
        lv_obj_set_flex_flow(lv_obj_17, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_17, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_column(lv_obj_17, SPACE_XS, 0);
        lv_obj_t * lv_image_3 = lv_image_create(lv_obj_17);
        lv_image_set_src(lv_image_3, icon_layers);
        lv_obj_set_style_image_recolor(lv_image_3, COLOR_TEXT_SECONDARY, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_3, (255 * 100 / 100), 0);

        lv_obj_t * lv_obj_18 = lv_obj_create(lv_obj_17);
        lv_obj_set_flex_flow(lv_obj_18, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_row(lv_obj_18, 0, 0);
        lv_obj_t * lv_label_15 = lv_label_create(lv_obj_18);
        lv_label_set_text(lv_label_15, "Low Temp Bi58Sn42");
        lv_obj_set_style_text_color(lv_label_15, COLOR_TEXT_PRIMARY, 0);
        lv_obj_set_style_text_font(lv_label_15, font_h5, 0);

        lv_obj_t * lv_label_16 = lv_label_create(lv_obj_18);
        lv_label_set_text(lv_label_16, "Bismuth Alloy (Peak 165°C)");
        lv_obj_set_style_text_color(lv_label_16, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_16, font_body, 0);

        lv_obj_t * lv_label_17 = lv_label_create(lv_obj_16);
        lv_label_set_text(lv_label_17, "○");
        lv_obj_set_style_text_color(lv_label_17, COLOR_TEXT_MUTED, 0);

        lv_obj_t * lv_obj_19 = lv_obj_create(lv_obj_9);
        lv_obj_set_width(lv_obj_19, lv_pct(100));
        lv_obj_set_height(lv_obj_19, 32);
        lv_obj_set_flex_flow(lv_obj_19, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(lv_obj_19, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_19, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_hor(lv_obj_19, SPACE_SM, 0);
        lv_obj_set_style_bg_color(lv_obj_19, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_border_color(lv_obj_19, COLOR_BORDER, 0);
        lv_obj_set_style_border_width(lv_obj_19, 1, 0);
        lv_obj_set_style_radius(lv_obj_19, RADIUS_CARD, 0);
        lv_obj_t * lv_obj_20 = lv_obj_create(lv_obj_19);
        lv_obj_set_flex_flow(lv_obj_20, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_20, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_column(lv_obj_20, SPACE_XS, 0);
        lv_obj_t * lv_image_4 = lv_image_create(lv_obj_20);
        lv_image_set_src(lv_image_4, icon_sliders);
        lv_obj_set_style_image_recolor(lv_image_4, COLOR_TEXT_SECONDARY, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_4, (255 * 100 / 100), 0);

        lv_obj_t * lv_obj_21 = lv_obj_create(lv_obj_20);
        lv_obj_set_flex_flow(lv_obj_21, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_row(lv_obj_21, 0, 0);
        lv_obj_t * lv_label_18 = lv_label_create(lv_obj_21);
        lv_label_set_text(lv_label_18, "Custom Profile 1");
        lv_obj_set_style_text_color(lv_label_18, COLOR_TEXT_PRIMARY, 0);
        lv_obj_set_style_text_font(lv_label_18, font_h5, 0);

        lv_obj_t * lv_label_19 = lv_label_create(lv_obj_21);
        lv_label_set_text(lv_label_19, "User Defined Ramp/Soak");
        lv_obj_set_style_text_color(lv_label_19, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_19, font_body, 0);

        lv_obj_t * lv_label_20 = lv_label_create(lv_obj_19);
        lv_label_set_text(lv_label_20, "○");
        lv_obj_set_style_text_color(lv_label_20, COLOR_TEXT_MUTED, 0);

        lv_obj_t * lv_obj_22 = lv_obj_create(lv_obj_1);
        lv_obj_set_width(lv_obj_22, lv_pct(100));
        lv_obj_set_height(lv_obj_22, 32);
        lv_obj_set_flex_flow(lv_obj_22, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(lv_obj_22, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_22, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_column(lv_obj_22, SPACE_SM, 0);
        button_create(lv_obj_22, "LOAD PROFILE", icon_check, COLOR_ACCENT, COLOR_ACCENT_TEXT, RADIUS_DEFAULT);

        button_create(lv_obj_22, "EDIT PROFILE", icon_sliders, COLOR_DARK_PANEL, COLOR_TEXT_PRIMARY, RADIUS_DEFAULT);

        lv_obj_t * lv_obj_23 = lv_obj_create(column_0);
        lv_obj_set_width(lv_obj_23, lv_pct(100));
        lv_obj_set_height(lv_obj_23, 40);
        lv_obj_set_flex_flow(lv_obj_23, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(lv_obj_23, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_23, LV_FLEX_ALIGN_SPACE_AROUND, 0);
        lv_obj_set_style_pad_hor(lv_obj_23, 2, 0);
        lv_obj_set_style_bg_color(lv_obj_23, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_border_color(lv_obj_23, COLOR_BORDER, 0);
        lv_obj_set_style_border_width(lv_obj_23, 1, 0);
        lv_obj_set_style_border_side(lv_obj_23, LV_BORDER_SIDE_TOP, 0);
        lv_obj_t * lv_obj_24 = lv_obj_create(lv_obj_23);
        lv_obj_set_width(lv_obj_24, 44);
        lv_obj_set_height(lv_obj_24, 34);
        lv_obj_set_flex_flow(lv_obj_24, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_24, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_24, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_24, RADIUS_DEFAULT, 0);
        lv_obj_set_flag(lv_obj_24, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_screen_load_event(lv_obj_24, LV_EVENT_CLICKED, screen_home, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);
        lv_obj_t * lv_image_5 = lv_image_create(lv_obj_24);
        lv_image_set_src(lv_image_5, icon_home);
        lv_obj_set_style_image_recolor(lv_image_5, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_5, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_21 = lv_label_create(lv_obj_24);
        lv_label_set_text(lv_label_21, "HOME");
        lv_obj_set_style_text_color(lv_label_21, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_21, font_body, 0);

        lv_obj_t * lv_obj_25 = lv_obj_create(lv_obj_23);
        lv_obj_set_width(lv_obj_25, 44);
        lv_obj_set_height(lv_obj_25, 34);
        lv_obj_set_flex_flow(lv_obj_25, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_25, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_25, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_25, RADIUS_DEFAULT, 0);
        lv_obj_set_style_bg_color(lv_obj_25, COLOR_SURFACE_ELEVATED, 0);
        lv_obj_set_style_border_color(lv_obj_25, COLOR_ACCENT, 0);
        lv_obj_set_style_border_width(lv_obj_25, 1, 0);
        lv_obj_set_flag(lv_obj_25, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_t * lv_image_6 = lv_image_create(lv_obj_25);
        lv_image_set_src(lv_image_6, icon_layers);
        lv_obj_set_style_image_recolor(lv_image_6, COLOR_ACCENT, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_6, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_22 = lv_label_create(lv_obj_25);
        lv_label_set_text(lv_label_22, "PROF");
        lv_obj_set_style_text_color(lv_label_22, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_22, font_body, 0);

        lv_obj_t * lv_obj_26 = lv_obj_create(lv_obj_23);
        lv_obj_set_width(lv_obj_26, 44);
        lv_obj_set_height(lv_obj_26, 34);
        lv_obj_set_flex_flow(lv_obj_26, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_26, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_26, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_26, RADIUS_DEFAULT, 0);
        lv_obj_set_flag(lv_obj_26, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_screen_load_event(lv_obj_26, LV_EVENT_CLICKED, screen_manual, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);
        lv_obj_t * lv_image_7 = lv_image_create(lv_obj_26);
        lv_image_set_src(lv_image_7, icon_sliders);
        lv_obj_set_style_image_recolor(lv_image_7, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_7, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_23 = lv_label_create(lv_obj_26);
        lv_label_set_text(lv_label_23, "MAN");
        lv_obj_set_style_text_color(lv_label_23, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_23, font_body, 0);

        lv_obj_t * lv_obj_27 = lv_obj_create(lv_obj_23);
        lv_obj_set_width(lv_obj_27, 44);
        lv_obj_set_height(lv_obj_27, 34);
        lv_obj_set_flex_flow(lv_obj_27, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_27, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_27, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_27, RADIUS_DEFAULT, 0);
        lv_obj_set_flag(lv_obj_27, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_screen_load_event(lv_obj_27, LV_EVENT_CLICKED, screen_settings, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);
        lv_obj_t * lv_image_8 = lv_image_create(lv_obj_27);
        lv_image_set_src(lv_image_8, icon_settings);
        lv_obj_set_style_image_recolor(lv_image_8, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_8, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_24 = lv_label_create(lv_obj_27);
        lv_label_set_text(lv_label_24, "SETT");
        lv_obj_set_style_text_color(lv_label_24, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_24, font_body, 0);

        lv_obj_t * lv_obj_28 = lv_obj_create(lv_obj_23);
        lv_obj_set_width(lv_obj_28, 44);
        lv_obj_set_height(lv_obj_28, 34);
        lv_obj_set_flex_flow(lv_obj_28, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_28, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(lv_obj_28, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_radius(lv_obj_28, RADIUS_DEFAULT, 0);
        lv_obj_set_flag(lv_obj_28, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_screen_load_event(lv_obj_28, LV_EVENT_CLICKED, screen_info, LV_SCREEN_LOAD_ANIM_NONE, 0, 0);
        lv_obj_t * lv_image_9 = lv_image_create(lv_obj_28);
        lv_image_set_src(lv_image_9, icon_info);
        lv_obj_set_style_image_recolor(lv_image_9, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_image_recolor_opa(lv_image_9, (255 * 100 / 100), 0);

        lv_obj_t * lv_label_25 = lv_label_create(lv_obj_28);
        lv_label_set_text(lv_label_25, "INFO");
        lv_obj_set_style_text_color(lv_label_25, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_25, font_body, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

