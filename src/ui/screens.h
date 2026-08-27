#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
  _SCREEN_ID_FIRST = 1,
  SCREEN_ID_MAIN = 1,
  SCREEN_ID_PROFILES = 2,
  SCREEN_ID_MANUAL = 3,
  _SCREEN_ID_LAST = 3
};

typedef struct _objects_t {
  lv_obj_t *main;
  lv_obj_t *profiles;
  lv_obj_t *manual;
  lv_obj_t *obj0;
  lv_obj_t *obj0__obj8;
  lv_obj_t *obj0__obj9;
  lv_obj_t *obj0__obj10;
  lv_obj_t *obj1;
  lv_obj_t *obj2;
  lv_obj_t *obj3;
  lv_obj_t *obj4;
  lv_obj_t *obj5;
  lv_obj_t *obj6;
  lv_obj_t *obj7;
  lv_obj_t *obj8;
  lv_obj_t *obj9;
  lv_obj_t *obj10;
  lv_obj_t *obj11;
  lv_obj_t *obj12;
  lv_obj_t *obj13;
  lv_obj_t *obj14;
  lv_obj_t *obj15;
  lv_obj_t *obj16;
  lv_obj_t *obj17;
  lv_obj_t *obj18;
  lv_obj_t *obj19;
  lv_obj_t *obj20;
  lv_obj_t *obj21;
  lv_obj_t *obj22;
  lv_obj_t *obj23;
  lv_obj_t *obj23__obj0;
  lv_obj_t *obj23__obj1;
  lv_obj_t *obj23__obj2;
  lv_obj_t *obj23__obj3;
  lv_obj_t *obj23__obj4;
  lv_obj_t *obj23__obj5;
  lv_obj_t *obj23__obj6;
  lv_obj_t *obj23__obj7;
  lv_obj_t *obj24;
  lv_obj_t *obj24__obj8;
  lv_obj_t *obj24__obj9;
  lv_obj_t *obj24__obj10;
  lv_obj_t *obj25;
  lv_obj_t *obj26;
  lv_obj_t *obj26__obj0;
  lv_obj_t *obj26__obj1;
  lv_obj_t *obj26__obj2;
  lv_obj_t *obj26__obj3;
  lv_obj_t *obj26__obj4;
  lv_obj_t *obj26__obj5;
  lv_obj_t *obj26__obj6;
  lv_obj_t *obj26__obj7;
  lv_obj_t *obj27;
  lv_obj_t *obj27__obj8;
  lv_obj_t *obj27__obj9;
  lv_obj_t *obj27__obj10;
  lv_obj_t *obj28;
  lv_obj_t *obj29;
  lv_obj_t *obj29__obj0;
  lv_obj_t *obj29__obj1;
  lv_obj_t *obj29__obj2;
  lv_obj_t *obj29__obj3;
  lv_obj_t *obj29__obj4;
  lv_obj_t *obj29__obj5;
  lv_obj_t *obj29__obj6;
  lv_obj_t *obj29__obj7;
} objects_t;

extern objects_t objects;

void create_screen_main();
void tick_screen_main();

void create_screen_profiles();
void tick_screen_profiles();

void create_screen_manual();
void tick_screen_manual();

void create_user_widget_navigation(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_navigation(int startWidgetIndex);

void create_user_widget_header(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_header(int startWidgetIndex);

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

// Color themes

enum Themes {
  THEME_ID_DEFAULT,
};
enum Colors {
  COLOR_ID_COLOR_BG,
  COLOR_ID_COLOR_PANEL,
  COLOR_ID_COLOR_PANEL_ALT,
  COLOR_ID_COLOR_BORDER,
  COLOR_ID_COLOR_RED,
  COLOR_ID_COLOR_RED_DARK,
  COLOR_ID_COLOR_RED_DIM,
  COLOR_ID_COLOR_WHITE,
  COLOR_ID_COLOR_TEXT,
  COLOR_ID_COLOR_TEXT_DIM,
  COLOR_ID_COLOR_GREEN,
  COLOR_ID_COLOR_GREEN_DARK,
  COLOR_ID_COLOR_YELLOW,
};
void change_color_theme(uint32_t themeIndex);
extern uint32_t theme_colors[1][13];
extern uint32_t active_theme_index;

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/