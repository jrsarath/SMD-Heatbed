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
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "home_#");
        lv_obj_set_width(lv_obj_0, lv_pct(100));
        lv_obj_set_height(lv_obj_0, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_0, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_bg_color(lv_obj_0, COLOR_DARK_BG, 0);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);

        lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
        lv_obj_set_width(lv_obj_1, lv_pct(100));
        lv_obj_set_height(lv_obj_1, 40);
        lv_obj_set_flex_flow(lv_obj_1, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_bg_color(lv_obj_1, COLOR_NAV_BG, 0);
        lv_obj_set_style_border_width(lv_obj_1, 1, 0);
        lv_obj_set_style_border_color(lv_obj_1, COLOR_NAV_BORDER, 0);
        lv_obj_set_style_pad_hor(lv_obj_1, SPACE_MD, 0);
        lv_obj_set_style_flex_main_place(lv_obj_1, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_0, "SMD HEATBED");
        lv_obj_set_style_text_color(lv_label_0, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_0, font_md, 0);

        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_1, "STANDBY");
        lv_obj_set_style_text_color(lv_label_1, COLOR_WARNING, 0);
        lv_obj_set_style_text_font(lv_label_1, font_sm, 0);

        lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_0);
        lv_obj_set_width(lv_obj_2, lv_pct(100));
        lv_obj_set_flex_grow(lv_obj_2, 1);
        lv_obj_set_flex_flow(lv_obj_2, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_bg_opa(lv_obj_2, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(lv_obj_2, 0, 0);
        lv_obj_set_style_pad_all(lv_obj_2, SPACE_MD, 0);
        lv_obj_set_style_pad_gap(lv_obj_2, SPACE_MD, 0);
        lv_obj_t * lv_obj_3 = lv_obj_create(lv_obj_2);
        lv_obj_set_width(lv_obj_3, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_3, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_bg_color(lv_obj_3, COLOR_CARD_BG, 0);
        lv_obj_set_style_border_width(lv_obj_3, 1, 0);
        lv_obj_set_style_border_color(lv_obj_3, COLOR_CARD_BORDER, 0);
        lv_obj_set_style_radius(lv_obj_3, RADIUS_MD, 0);
        lv_obj_set_style_pad_all(lv_obj_3, SPACE_MD, 0);
        lv_obj_set_style_pad_gap(lv_obj_3, SPACE_SM, 0);
        lv_obj_t * lv_label_2 = lv_label_create(lv_obj_3);
        lv_label_set_text(lv_label_2, "TEMPERATURE");
        lv_obj_set_style_text_color(lv_label_2, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_2, font_xs, 0);

        lv_obj_t * lv_obj_4 = lv_obj_create(lv_obj_3);
        lv_obj_set_width(lv_obj_4, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_4, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_bg_opa(lv_obj_4, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(lv_obj_4, 0, 0);
        lv_obj_set_style_flex_main_place(lv_obj_4, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_4, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_t * lv_obj_5 = lv_obj_create(lv_obj_4);
        lv_obj_set_flex_flow(lv_obj_5, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_bg_opa(lv_obj_5, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(lv_obj_5, 0, 0);
        lv_obj_t * lv_label_3 = lv_label_create(lv_obj_5);
        lv_label_set_text(lv_label_3, "CURRENT");
        lv_obj_set_style_text_color(lv_label_3, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_3, font_xs, 0);

        lv_obj_t * lv_label_4 = lv_label_create(lv_obj_5);
        lv_label_set_text(lv_label_4, "25 °C");
        lv_obj_set_style_text_color(lv_label_4, COLOR_TEXT_PRIMARY, 0);
        lv_obj_set_style_text_font(lv_label_4, font_lg, 0);

        lv_obj_t * lv_obj_6 = lv_obj_create(lv_obj_4);
        lv_obj_set_flex_flow(lv_obj_6, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_bg_opa(lv_obj_6, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(lv_obj_6, 0, 0);
        lv_obj_t * lv_label_5 = lv_label_create(lv_obj_6);
        lv_label_set_text(lv_label_5, "TARGET");
        lv_obj_set_style_text_color(lv_label_5, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_5, font_xs, 0);

        lv_obj_t * lv_label_6 = lv_label_create(lv_obj_6);
        lv_label_set_text(lv_label_6, "150 °C");
        lv_obj_set_style_text_color(lv_label_6, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_6, font_lg, 0);

        lv_obj_t * lv_obj_7 = lv_obj_create(lv_obj_2);
        lv_obj_set_width(lv_obj_7, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_7, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_bg_color(lv_obj_7, COLOR_CARD_BG, 0);
        lv_obj_set_style_border_width(lv_obj_7, 1, 0);
        lv_obj_set_style_border_color(lv_obj_7, COLOR_CARD_BORDER, 0);
        lv_obj_set_style_radius(lv_obj_7, RADIUS_MD, 0);
        lv_obj_set_style_pad_all(lv_obj_7, SPACE_MD, 0);
        lv_obj_set_style_pad_gap(lv_obj_7, SPACE_XS, 0);
        lv_obj_t * lv_label_7 = lv_label_create(lv_obj_7);
        lv_label_set_text(lv_label_7, "ACTIVE PROFILE");
        lv_obj_set_style_text_color(lv_label_7, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_7, font_xs, 0);

        lv_obj_t * lv_label_8 = lv_label_create(lv_obj_7);
        lv_label_set_text(lv_label_8, "SAC305 Lead-Free");
        lv_obj_set_style_text_color(lv_label_8, COLOR_TEXT_PRIMARY, 0);
        lv_obj_set_style_text_font(lv_label_8, font_md, 0);

        lv_obj_t * lv_label_9 = lv_label_create(lv_obj_7);
        lv_label_set_text(lv_label_9, "Peak: 245°C | Soak: 180°C");
        lv_obj_set_style_text_color(lv_label_9, COLOR_TEXT_MUTED, 0);
        lv_obj_set_style_text_font(lv_label_9, font_sm, 0);

        lv_obj_t * nav_bar = navigation_bar_create(lv_obj_0, 0, true, false, false, false);
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

