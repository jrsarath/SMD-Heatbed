/**
 * @file lvgl_ui_gen.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "lvgl_ui_gen.h"

#if defined(LV_USE_XML) && LV_USE_XML
#endif /* LV_USE_XML */

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void check_font(lv_font_t ** font, const char * name);

/**********************
 *  STATIC VARIABLES
 **********************/

static uint32_t lvgl_ui_target = LVGL_UI_TARGET_ALL;

/*----------------
 * Translations
 *----------------*/

#ifndef LV_EDITOR_PREVIEW
    static const char * translation_languages[] = {"en", "de", NULL};
    static const char * translation_tags[] = {"dog", "cat", "house", NULL};
    static const char * translation_texts[] = {
        "This is a dog", "Das ist ein Hund", /* dog */
        "A curious little cat", "Eine neugierige kleine Katze", /* cat */
        "The house is cozy and warm", "Das Haus ist gemütlich und warm", /* house */
    };
#endif

/**********************
 *  GLOBAL VARIABLES
 **********************/

/*--------------------
 *  Permanent screens
 *-------------------*/

/*----------------
 * Fonts
 *----------------*/

lv_font_t * font_xs;
extern lv_font_t font_xs_data;
lv_font_t * font_sm;
extern lv_font_t font_sm_data;
lv_font_t * font_md;
extern lv_font_t font_md_data;
lv_font_t * font_lg;
extern lv_font_t font_lg_data;

/*----------------
 * Images
 *----------------*/



/*----------------
 * Global styles
 *----------------*/

/*----------------
 * Subjects
 *----------------*/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lvgl_ui_init_gen(const char * asset_path)
{

    /*----------------
     * Fonts
     *----------------*/

    /* Targets: any */

    #if LVGL_UI_CHECK_COMPILE_TARGET(LVGL_UI_TARGET_ALL)
    if (lvgl_ui_check_target(LVGL_UI_TARGET_ALL)) {
        if (!font_xs) {
            /* font_xs */
            /* get font 'font_xs' from a C array */
            font_xs = &font_xs_data;

        }
        if (!font_sm) {
            /* font_sm */
            /* get font 'font_sm' from a C array */
            font_sm = &font_sm_data;

        }
        if (!font_md) {
            /* font_md */
            /* get font 'font_md' from a C array */
            font_md = &font_md_data;

        }
        if (!font_lg) {
            /* font_lg */
            /* get font 'font_lg' from a C array */
            font_lg = &font_lg_data;

        }
    }
    #endif

    /*----------------
     * Images
     *----------------*/



    /*----------------
     * Global styles
     *----------------*/

    /*----------------
     * Subjects
     *----------------*/
    /*----------------
     * Translations
     *----------------*/

    #ifndef LV_EDITOR_PREVIEW
        lv_translation_add_static(translation_languages, translation_tags, translation_texts);
        lv_translation_set_language(translation_languages[0]);
    #endif

#if defined(LV_USE_XML) && LV_USE_XML
    /* Register widgets */

    /* Check all fonts / default if needed. This prevents fonts that are used in one target but
       defined in another from causing assertion failures during rendering of the Preview. */
    check_font(&font_xs, "font_xs");
    check_font(&font_sm, "font_sm");
    check_font(&font_md, "font_md");
    check_font(&font_lg, "font_lg");

    /* Register fonts */
    lv_xml_register_font(NULL, "font_xs", font_xs);
    lv_xml_register_font(NULL, "font_sm", font_sm);
    lv_xml_register_font(NULL, "font_md", font_md);
    lv_xml_register_font(NULL, "font_lg", font_lg);

    /* Register subjects */

    /* Register callbacks */
#endif

    /* Register all the global assets so that they won't be created again when globals.xml is parsed.
     * While running in the editor skip this step to update the preview when the XML changes */
#if defined(LV_USE_XML) && LV_USE_XML && !defined(LV_EDITOR_PREVIEW)
    /* Register images */
#endif

#if !defined(LV_USE_XML) || LV_USE_XML == 0
    /*--------------------
     *  Permanent screens
     *-------------------*/
    /* If XML is enabled it's assumed that the permanent screens are created
     * manually from XML using lv_xml_create() */
#endif
}

void lvgl_ui_set_target(uint32_t target)
{
    lvgl_ui_target = target;
}

uint32_t lvgl_ui_get_target(void)
{
    return lvgl_ui_target;
}

bool lvgl_ui_check_target(uint32_t target)
{
    return (lvgl_ui_target & target) ? true : false;
}

/* Callbacks */

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void check_font(lv_font_t ** font, const char * name)
{
    if (!(*font)) {
        *font = (lv_font_t *)LV_FONT_DEFAULT;
        LV_LOG_WARN("font `%s` was not set. Using `LV_FONT_DEFAULT` instead", name);
    }
}