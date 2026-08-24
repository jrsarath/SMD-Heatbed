/**
 * @file navigation_button_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "navigation_button_gen.h"
#include "../../../lvgl_ui.h"

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

lv_obj_t * navigation_button_create(lv_obj_t * parent, const char * label, const void * icon, bool active, int32_t grow)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_nav_btn;
    static lv_style_t style_nav_btn_light;
    static lv_style_t style_nav_btn_dark;
    static lv_style_t style_nav_btn_active;
    static lv_style_t style_nav_btn_pressed;
    static lv_style_t style_nav_btn_icon;
    static lv_style_t style_nav_btn_label;

    static bool style_inited = false;

    if (!style_inited) {
        /*Init all styles*/
        lv_style_init(&style_nav_btn);
        lv_style_init(&style_nav_btn_light);
        lv_style_init(&style_nav_btn_dark);
        lv_style_init(&style_nav_btn_active);
        lv_style_init(&style_nav_btn_pressed);
        lv_style_init(&style_nav_btn_icon);
        lv_style_init(&style_nav_btn_label);

        lv_style_set_flex_flow(&style_nav_btn, LV_FLEX_FLOW_COLUMN);
        lv_style_set_bg_opa(&style_nav_btn, (255 * 0 / 100));
        lv_style_set_border_width(&style_nav_btn, 0);
        lv_style_set_shadow_width(&style_nav_btn, 0);
        lv_style_set_radius(&style_nav_btn, 0);
        lv_style_set_pad_hor(&style_nav_btn, SPACE_XS);
        lv_style_set_pad_ver(&style_nav_btn, SPACE_XS);
        lv_style_set_pad_gap(&style_nav_btn, SPACE_XS);
        lv_style_set_flex_cross_place(&style_nav_btn, LV_FLEX_ALIGN_CENTER);
        lv_style_set_flex_main_place(&style_nav_btn, LV_FLEX_ALIGN_CENTER);
        lv_style_set_text_font(&style_nav_btn, font_body);
        lv_style_set_text_color(&style_nav_btn_light, COLOR_LIGHT_TEXT);
        lv_style_set_text_opa(&style_nav_btn_light, (255 * 60 / 100));
        lv_style_set_image_recolor(&style_nav_btn_light, COLOR_LIGHT_TEXT);
        lv_style_set_image_recolor_opa(&style_nav_btn_light, (255 * 60 / 100));
        lv_style_set_text_color(&style_nav_btn_dark, COLOR_DARK_TEXT);
        lv_style_set_text_opa(&style_nav_btn_dark, (255 * 60 / 100));
        lv_style_set_image_recolor(&style_nav_btn_dark, COLOR_DARK_TEXT);
        lv_style_set_image_recolor_opa(&style_nav_btn_dark, (255 * 60 / 100));
        lv_style_set_bg_color(&style_nav_btn_active, COLOR_ACCENT);
        lv_style_set_bg_opa(&style_nav_btn_active, (255 * 100 / 100));
        lv_style_set_text_color(&style_nav_btn_active, COLOR_ACCENT_TEXT);
        lv_style_set_text_opa(&style_nav_btn_active, (255 * 100 / 100));
        lv_style_set_image_recolor(&style_nav_btn_active, COLOR_ACCENT_TEXT);
        lv_style_set_image_recolor_opa(&style_nav_btn_active, (255 * 100 / 100));
        lv_style_set_radius(&style_nav_btn_active, 0);
        lv_style_set_recolor(&style_nav_btn_pressed, COLOR_TRACK);
        lv_style_set_recolor_opa(&style_nav_btn_pressed, (255 * 40 / 100));
        lv_style_set_image_recolor_opa(&style_nav_btn_icon, (255 * 100 / 100));
        lv_style_set_align(&style_nav_btn_icon, LV_ALIGN_CENTER);
        lv_style_set_text_font(&style_nav_btn_label, font_md);
        lv_style_set_text_align(&style_nav_btn_label, LV_TEXT_ALIGN_CENTER);
        lv_style_set_align(&style_nav_btn_label, LV_ALIGN_CENTER);

        style_inited = true;
    }


    lv_obj_t * the_root = NULL;

    #if LVGL_UI_CHECK_COMPILE_TARGET(LVGL_UI_TARGET_ALL)
    if (lvgl_ui_check_target(LVGL_UI_TARGET_ALL)) {
        lv_obj_t * lv_button_0 = lv_button_create(parent);
        lv_obj_set_name_static(lv_button_0, "navigation_button_#");
        lv_obj_set_flex_flow(lv_button_0, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_flex_grow(lv_button_0, grow);
        lv_obj_set_width(lv_button_0, lv_pct(100));
        lv_obj_set_height(lv_button_0, lv_pct(100));
        lv_obj_set_flag(lv_button_0, LV_OBJ_FLAG_CHECKABLE, true);
        lv_obj_set_state(lv_button_0, LV_STATE_CHECKED, active);
        lv_obj_set_style_flex_main_place(lv_button_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(lv_button_0, LV_FLEX_ALIGN_CENTER, 0);

        lv_obj_add_style(lv_button_0, &style_nav_btn, 0);
        lv_obj_add_style(lv_button_0, &style_nav_btn_light, 0);
        lv_obj_bind_style(lv_button_0, &style_nav_btn_dark, 0, &subject_theme_dark, 1);
        lv_obj_add_style(lv_button_0, &style_nav_btn_active, LV_STATE_CHECKED);
        lv_obj_add_style(lv_button_0, &style_nav_btn_pressed, LV_STATE_PRESSED);
        lv_obj_t * lv_image_0 = lv_image_create(lv_button_0);
        lv_image_set_src(lv_image_0, icon);
        lv_obj_set_flag(lv_image_0, LV_OBJ_FLAG_HIDDEN, !icon);
        lv_obj_add_style(lv_image_0, &style_nav_btn_icon, 0);

        lv_obj_t * lv_label_0 = lv_label_create(lv_button_0);
        lv_label_set_text(lv_label_0, label);
        lv_obj_set_flag(lv_label_0, LV_OBJ_FLAG_HIDDEN, !label);
        lv_obj_set_width(lv_label_0, lv_pct(100));
        lv_obj_add_style(lv_label_0, &style_nav_btn_label, 0);

        the_root = lv_button_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

