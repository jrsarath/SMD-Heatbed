/*******************************************************************************
 * Size: 8 px
 * Bpp: 4
 * Opts: --font /fonts/Montserrat-Regular.ttf -o /fonts/font_sm_data.c --size 8 --bpp 4 --format lvgl --no-compress --symbols °—• --range 0x20-0x7F --lv-fallback font_body_symbols_data
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif



#ifndef FONT_SM_DATA
#define FONT_SM_DATA 1
#endif

#if FONT_SM_DATA

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x45, 0x45, 0x34, 0x22, 0x34,

    /* U+0022 "\"" */
    0x71, 0x66, 0x16,

    /* U+0023 "#" */
    0x03, 0x32, 0x40, 0x3a, 0x79, 0x72, 0x07, 0x06,
    0x00, 0x4a, 0x6a, 0x60, 0x06, 0x07, 0x00,

    /* U+0024 "$" */
    0x00, 0x60, 0x02, 0x8a, 0x71, 0x63, 0x60, 0x00,
    0x6b, 0x70, 0x00, 0x62, 0x74, 0x7b, 0x82, 0x00,
    0x60, 0x00,

    /* U+0025 "%" */
    0x45, 0x60, 0x52, 0x06, 0x07, 0x34, 0x00, 0x26,
    0x56, 0x66, 0x00, 0x07, 0x34, 0x33, 0x05, 0x10,
    0x77, 0x10,

    /* U+0026 "&" */
    0x08, 0x77, 0x00, 0x08, 0x16, 0x00, 0x08, 0xa1,
    0x10, 0x80, 0x08, 0x80, 0x38, 0x77, 0x80, 0x00,
    0x00, 0x00,

    /* U+0027 "'" */
    0x70, 0x60,

    /* U+0028 "(" */
    0x07, 0x10, 0x80, 0x08, 0x02, 0x60, 0x08, 0x00,
    0x80, 0x07, 0x10,

    /* U+0029 ")" */
    0x61, 0x07, 0x08, 0x08, 0x08, 0x07, 0x61,

    /* U+002A "*" */
    0x36, 0x35, 0xd6, 0x04, 0x00,

    /* U+002B "+" */
    0x00, 0x10, 0x00, 0x08, 0x00, 0x37, 0xb7, 0x00,
    0x08, 0x00,

    /* U+002C "," */
    0x62, 0x60,

    /* U+002D "-" */
    0x37, 0x40,

    /* U+002E "." */
    0x52,

    /* U+002F "/" */
    0x00, 0x08, 0x00, 0x26, 0x00, 0x70, 0x00, 0x80,
    0x04, 0x40, 0x08, 0x00, 0x07, 0x00,

    /* U+0030 "0" */
    0x08, 0x89, 0x26, 0x30, 0x09, 0x80, 0x00, 0x96,
    0x30, 0x09, 0x08, 0x89, 0x20,

    /* U+0031 "1" */
    0x7c, 0x09, 0x09, 0x09, 0x09,

    /* U+0032 "2" */
    0x67, 0x87, 0x00, 0x00, 0x90, 0x00, 0x46, 0x00,
    0x65, 0x00, 0x7b, 0x77, 0x10,

    /* U+0033 "3" */
    0x57, 0x8b, 0x00, 0x09, 0x10, 0x03, 0x95, 0x00,
    0x00, 0x80, 0x67, 0x77, 0x00,

    /* U+0034 "4" */
    0x00, 0x36, 0x00, 0x02, 0x80, 0x00, 0x19, 0x08,
    0x10, 0x78, 0x7b, 0x81, 0x00, 0x08, 0x10,

    /* U+0035 "5" */
    0x3a, 0x77, 0x04, 0x40, 0x00, 0x48, 0x76, 0x00,
    0x00, 0x72, 0x57, 0x78, 0x00,

    /* U+0036 "6" */
    0x08, 0x87, 0x16, 0x40, 0x00, 0x85, 0x77, 0x16,
    0x50, 0x08, 0x07, 0x78, 0x30,

    /* U+0037 "7" */
    0xa7, 0x7b, 0x44, 0x00, 0x90, 0x00, 0x54, 0x00,
    0x09, 0x00, 0x05, 0x40, 0x00,

    /* U+0038 "8" */
    0x18, 0x79, 0x25, 0x30, 0x26, 0x1b, 0x7b, 0x18,
    0x10, 0x09, 0x38, 0x78, 0x40,

    /* U+0039 "9" */
    0x48, 0x77, 0x08, 0x00, 0x74, 0x28, 0x66, 0x60,
    0x00, 0x64, 0x27, 0x87, 0x00,

    /* U+003A ":" */
    0x52, 0x00, 0x00, 0x52,

    /* U+003B ";" */
    0x52, 0x00, 0x00, 0x62, 0x60,

    /* U+003C "<" */
    0x00, 0x00, 0x00, 0x37, 0x60, 0x4a, 0x20, 0x00,
    0x05, 0x70,

    /* U+003D "=" */
    0x37, 0x77, 0x00, 0x00, 0x00, 0x37, 0x77, 0x00,

    /* U+003E ">" */
    0x00, 0x00, 0x02, 0x76, 0x10, 0x00, 0x4b, 0x03,
    0x73, 0x00,

    /* U+003F "?" */
    0x67, 0x77, 0x00, 0x09, 0x00, 0x73, 0x00, 0x30,
    0x01, 0x50,

    /* U+0040 "@" */
    0x02, 0x65, 0x56, 0x40, 0x25, 0x48, 0x6a, 0x54,
    0x70, 0x80, 0x08, 0x27, 0x70, 0x80, 0x08, 0x26,
    0x26, 0x47, 0x67, 0x85, 0x02, 0x66, 0x63, 0x00,

    /* U+0041 "A" */
    0x00, 0x96, 0x00, 0x03, 0x69, 0x00, 0x09, 0x02,
    0x60, 0x3a, 0x77, 0xb0, 0x90, 0x00, 0x27,

    /* U+0042 "B" */
    0x1b, 0x77, 0x91, 0x18, 0x00, 0x63, 0x1b, 0x77,
    0xa1, 0x18, 0x00, 0x18, 0x1b, 0x77, 0x83,

    /* U+0043 "C" */
    0x06, 0x87, 0x81, 0x45, 0x00, 0x00, 0x80, 0x00,
    0x00, 0x46, 0x00, 0x00, 0x06, 0x87, 0x81,

    /* U+0044 "D" */
    0x1b, 0x77, 0x93, 0x01, 0x80, 0x00, 0xa0, 0x18,
    0x00, 0x06, 0x21, 0x80, 0x00, 0xa0, 0x1b, 0x78,
    0x93, 0x00,

    /* U+0045 "E" */
    0x1b, 0x77, 0x51, 0x80, 0x00, 0x1b, 0x77, 0x31,
    0x80, 0x00, 0x1b, 0x77, 0x60,

    /* U+0046 "F" */
    0x1b, 0x77, 0x51, 0x80, 0x00, 0x1b, 0x77, 0x31,
    0x80, 0x00, 0x18, 0x00, 0x00,

    /* U+0047 "G" */
    0x06, 0x87, 0x82, 0x45, 0x00, 0x00, 0x80, 0x00,
    0x13, 0x46, 0x00, 0x26, 0x06, 0x87, 0x83,

    /* U+0048 "H" */
    0x18, 0x00, 0x09, 0x18, 0x00, 0x09, 0x1c, 0x88,
    0x89, 0x18, 0x00, 0x09, 0x18, 0x00, 0x09,

    /* U+0049 "I" */
    0x18, 0x18, 0x18, 0x18, 0x18,

    /* U+004A "J" */
    0x03, 0x7b, 0x20, 0x00, 0x72, 0x00, 0x07, 0x20,
    0x00, 0x71, 0x07, 0x79, 0x00,

    /* U+004B "K" */
    0x18, 0x00, 0x81, 0x18, 0x19, 0x10, 0x19, 0xb5,
    0x00, 0x1b, 0x07, 0x40, 0x18, 0x00, 0x73,

    /* U+004C "L" */
    0x18, 0x00, 0x01, 0x80, 0x00, 0x18, 0x00, 0x01,
    0x80, 0x00, 0x1b, 0x77, 0x40,

    /* U+004D "M" */
    0x1b, 0x00, 0x02, 0xb1, 0xb5, 0x00, 0x89, 0x17,
    0x71, 0x53, 0x91, 0x70, 0x97, 0x09, 0x17, 0x02,
    0x00, 0x90,

    /* U+004E "N" */
    0x1c, 0x00, 0x09, 0x19, 0x90, 0x09, 0x18, 0x28,
    0x09, 0x18, 0x04, 0x79, 0x18, 0x00, 0x59,

    /* U+004F "O" */
    0x06, 0x77, 0x83, 0x04, 0x50, 0x00, 0x91, 0x80,
    0x00, 0x05, 0x34, 0x50, 0x00, 0x91, 0x06, 0x88,
    0x83, 0x00,

    /* U+0050 "P" */
    0x1b, 0x78, 0x70, 0x18, 0x00, 0x63, 0x18, 0x00,
    0x72, 0x1b, 0x77, 0x50, 0x18, 0x00, 0x00,

    /* U+0051 "Q" */
    0x06, 0x77, 0x83, 0x04, 0x50, 0x00, 0x91, 0x80,
    0x00, 0x05, 0x44, 0x50, 0x00, 0x91, 0x06, 0x88,
    0x83, 0x00, 0x00, 0x27, 0x72,

    /* U+0052 "R" */
    0x1b, 0x78, 0x70, 0x18, 0x00, 0x63, 0x18, 0x00,
    0x72, 0x1b, 0x7a, 0x60, 0x18, 0x00, 0x81,

    /* U+0053 "S" */
    0x28, 0x77, 0x16, 0x30, 0x00, 0x06, 0x76, 0x00,
    0x00, 0x27, 0x47, 0x78, 0x20,

    /* U+0054 "T" */
    0x77, 0xc7, 0x40, 0x09, 0x00, 0x00, 0x90, 0x00,
    0x09, 0x00, 0x00, 0x90, 0x00,

    /* U+0055 "U" */
    0x27, 0x00, 0x17, 0x27, 0x00, 0x17, 0x27, 0x00,
    0x17, 0x09, 0x00, 0x45, 0x06, 0x88, 0x80,

    /* U+0056 "V" */
    0x90, 0x00, 0x45, 0x36, 0x00, 0x90, 0x09, 0x04,
    0x50, 0x03, 0x69, 0x00, 0x00, 0xb5, 0x00,

    /* U+0057 "W" */
    0x81, 0x00, 0xd0, 0x02, 0x62, 0x70, 0x66, 0x50,
    0x81, 0x09, 0x08, 0x09, 0x08, 0x00, 0x66, 0x60,
    0x76, 0x40, 0x00, 0xd0, 0x01, 0xd0, 0x00,

    /* U+0058 "X" */
    0x55, 0x02, 0x70, 0x07, 0x49, 0x00, 0x00, 0xe2,
    0x00, 0x08, 0x29, 0x00, 0x63, 0x01, 0x90,

    /* U+0059 "Y" */
    0x81, 0x00, 0x80, 0x18, 0x07, 0x10, 0x04, 0x95,
    0x00, 0x00, 0xa0, 0x00, 0x00, 0x90, 0x00,

    /* U+005A "Z" */
    0x47, 0x79, 0xb0, 0x00, 0x90, 0x00, 0x91, 0x00,
    0x82, 0x00, 0x7a, 0x77, 0x70,

    /* U+005B "[" */
    0x1b, 0x21, 0x70, 0x17, 0x01, 0x70, 0x17, 0x01,
    0x70, 0x1b, 0x20,

    /* U+005C "\\" */
    0x16, 0x00, 0x08, 0x00, 0x05, 0x20, 0x00, 0x70,
    0x00, 0x70, 0x00, 0x34, 0x00, 0x08,

    /* U+005D "]" */
    0x69, 0x09, 0x09, 0x09, 0x09, 0x09, 0x69,

    /* U+005E "^" */
    0x02, 0xa0, 0x07, 0x33, 0x25, 0x07,

    /* U+005F "_" */
    0x55, 0x55,

    /* U+0060 "`" */
    0x55,

    /* U+0061 "a" */
    0x16, 0x76, 0x16, 0x6b, 0x81, 0x0a, 0x38, 0x6b,

    /* U+0062 "b" */
    0x35, 0x00, 0x00, 0x35, 0x00, 0x00, 0x3a, 0x78,
    0x50, 0x38, 0x00, 0x90, 0x38, 0x00, 0x90, 0x3a,
    0x78, 0x50,

    /* U+0063 "c" */
    0x18, 0x78, 0x08, 0x10, 0x00, 0x81, 0x00, 0x01,
    0x87, 0x80,

    /* U+0064 "d" */
    0x00, 0x00, 0x90, 0x00, 0x09, 0x18, 0x77, 0x98,
    0x10, 0x19, 0x81, 0x01, 0x91, 0x87, 0x78,

    /* U+0065 "e" */
    0x17, 0x77, 0x18, 0x66, 0x64, 0x82, 0x00, 0x01,
    0x97, 0x80,

    /* U+0066 "f" */
    0x09, 0x71, 0x70, 0x7b, 0x51, 0x70, 0x17, 0x01,
    0x70,

    /* U+0067 "g" */
    0x18, 0x77, 0x98, 0x10, 0x0a, 0x81, 0x00, 0xa1,
    0x87, 0x79, 0x16, 0x77, 0x30,

    /* U+0068 "h" */
    0x35, 0x00, 0x03, 0x50, 0x00, 0x3a, 0x79, 0x33,
    0x70, 0x09, 0x35, 0x00, 0x93, 0x50, 0x09,

    /* U+0069 "i" */
    0x24, 0x00, 0x35, 0x35, 0x35, 0x35,

    /* U+006A "j" */
    0x02, 0x40, 0x00, 0x02, 0x60, 0x26, 0x02, 0x60,
    0x26, 0x59, 0x30,

    /* U+006B "k" */
    0x35, 0x00, 0x03, 0x50, 0x00, 0x35, 0x08, 0x23,
    0x7b, 0x10, 0x3b, 0x47, 0x03, 0x50, 0x55,

    /* U+006C "l" */
    0x35, 0x35, 0x35, 0x35, 0x35, 0x35,

    /* U+006D "m" */
    0x3a, 0x69, 0x67, 0x84, 0x37, 0x01, 0xa0, 0x09,
    0x35, 0x00, 0x80, 0x09, 0x35, 0x00, 0x80, 0x09,

    /* U+006E "n" */
    0x3a, 0x68, 0x33, 0x70, 0x09, 0x35, 0x00, 0x93,
    0x50, 0x09,

    /* U+006F "o" */
    0x18, 0x89, 0x18, 0x10, 0x18, 0x81, 0x01, 0x81,
    0x87, 0x81,

    /* U+0070 "p" */
    0x3a, 0x77, 0x50, 0x37, 0x00, 0x90, 0x38, 0x00,
    0x90, 0x3a, 0x78, 0x50, 0x35, 0x00, 0x00,

    /* U+0071 "q" */
    0x18, 0x77, 0x88, 0x10, 0x19, 0x81, 0x01, 0x91,
    0x87, 0x79, 0x00, 0x00, 0x90,

    /* U+0072 "r" */
    0x3a, 0x63, 0x70, 0x35, 0x03, 0x50,

    /* U+0073 "s" */
    0x57, 0x73, 0x75, 0x20, 0x02, 0x67, 0x57, 0x75,

    /* U+0074 "t" */
    0x17, 0x00, 0x7b, 0x50, 0x17, 0x00, 0x17, 0x00,
    0x0a, 0x70,

    /* U+0075 "u" */
    0x45, 0x00, 0x94, 0x50, 0x09, 0x35, 0x01, 0x90,
    0x97, 0x78,

    /* U+0076 "v" */
    0x90, 0x07, 0x14, 0x40, 0x80, 0x09, 0x62, 0x00,
    0x59, 0x00,

    /* U+0077 "w" */
    0x80, 0x0c, 0x00, 0x85, 0x35, 0x65, 0x25, 0x08,
    0x80, 0x87, 0x00, 0x86, 0x05, 0x80,

    /* U+0078 "x" */
    0x54, 0x18, 0x00, 0x79, 0x00, 0x08, 0x90, 0x06,
    0x31, 0x80,

    /* U+0079 "y" */
    0x09, 0x00, 0x71, 0x03, 0x51, 0x70, 0x00, 0x87,
    0x10, 0x00, 0x38, 0x00, 0x07, 0x80, 0x00,

    /* U+007A "z" */
    0x47, 0x98, 0x00, 0x90, 0x09, 0x10, 0x79, 0x75,

    /* U+007B "{" */
    0x09, 0x30, 0x90, 0x09, 0x03, 0x80, 0x09, 0x00,
    0x90, 0x09, 0x30,

    /* U+007C "|" */
    0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17,

    /* U+007D "}" */
    0x76, 0x00, 0x90, 0x09, 0x00, 0xb1, 0x09, 0x00,
    0x90, 0x76, 0x00,

    /* U+007E "~" */
    0x27, 0x24, 0x04, 0x05, 0x60,

    /* U+00B0 "°" */
    0x25, 0x45, 0x05, 0x25, 0x40,

    /* U+2014 "—" */
    0x66, 0x66, 0x66, 0x66,

    /* U+2022 "•" */
    0x49, 0x00
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 34, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 33, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 48, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 8, .adv_w = 89, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 23, .adv_w = 79, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 41, .adv_w = 106, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 59, .adv_w = 86, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 77, .adv_w = 26, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 79, .adv_w = 42, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 90, .adv_w = 42, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 97, .adv_w = 49, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 102, .adv_w = 74, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 112, .adv_w = 27, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 114, .adv_w = 49, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 116, .adv_w = 27, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 43, .box_w = 4, .box_h = 7, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 131, .adv_w = 85, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 46, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 73, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 72, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 85, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 190, .adv_w = 72, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 203, .adv_w = 78, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 75, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 82, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 78, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 27, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 27, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 264, .adv_w = 74, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 274, .adv_w = 74, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 282, .adv_w = 74, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 292, .adv_w = 73, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 132, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 326, .adv_w = 92, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 97, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 91, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 106, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 86, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 402, .adv_w = 81, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 99, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 104, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 445, .adv_w = 39, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 450, .adv_w = 64, .box_w = 5, .box_h = 5, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 91, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 75, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 122, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 509, .adv_w = 104, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 524, .adv_w = 107, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 92, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 107, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 578, .adv_w = 93, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 79, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 606, .adv_w = 73, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 619, .adv_w = 101, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 634, .adv_w = 89, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 649, .adv_w = 142, .box_w = 9, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 672, .adv_w = 84, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 687, .adv_w = 81, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 702, .adv_w = 83, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 715, .adv_w = 41, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 726, .adv_w = 43, .box_w = 4, .box_h = 7, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 740, .adv_w = 41, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 747, .adv_w = 74, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 753, .adv_w = 64, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 755, .adv_w = 77, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 756, .adv_w = 76, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 764, .adv_w = 87, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 782, .adv_w = 72, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 792, .adv_w = 87, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 807, .adv_w = 77, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 817, .adv_w = 43, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 826, .adv_w = 88, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 839, .adv_w = 87, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 854, .adv_w = 34, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 860, .adv_w = 35, .box_w = 3, .box_h = 7, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 871, .adv_w = 77, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 886, .adv_w = 34, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 892, .adv_w = 136, .box_w = 8, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 908, .adv_w = 87, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 918, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 928, .adv_w = 87, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 943, .adv_w = 87, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 956, .adv_w = 51, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 962, .adv_w = 63, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 970, .adv_w = 52, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 980, .adv_w = 86, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 990, .adv_w = 69, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1000, .adv_w = 113, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1014, .adv_w = 68, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1024, .adv_w = 69, .box_w = 6, .box_h = 5, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 1039, .adv_w = 65, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1047, .adv_w = 43, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1058, .adv_w = 38, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1065, .adv_w = 43, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1076, .adv_w = 74, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1081, .adv_w = 54, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 1086, .adv_w = 128, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1090, .adv_w = 38, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x00, 0x1f64, 0x1f72
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 8051, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 3, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/

/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 1, 2, 0, 3, 4, 5,
    2, 6, 0, 7, 8, 9, 8, 9,
    10, 11, 0, 12, 13, 14, 15, 16,
    17, 18, 11, 19, 19, 0, 0, 0,
    20, 21, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 22, 23, 0, 0,
    24, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 22, 0, 0, 8,
    25, 0, 8
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 1, 2, 0, 3, 4, 5,
    2, 0, 6, 7, 8, 9, 8, 9,
    10, 11, 12, 13, 14, 15, 16, 11,
    17, 18, 19, 20, 20, 0, 0, 0,
    21, 22, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 23, 24, 25, 0,
    26, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 25, 8,
    27, 0, 8
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 1, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 6, 0, 4, -3,
    0, 3, 0, -7, -8, 1, 6, 3,
    2, -5, 1, 7, 0, 6, 1, 4,
    -2, 0, 8, 1, -1, 3, 0, -4,
    0, 0, 0, 0, -3, 2, 3, 0,
    0, -1, 0, -1, 1, 0, -1, 0,
    -1, -1, -3, 0, 0, -1, 0, -3,
    -2, 0, -4, 0, -15, 0, -3, -6,
    3, 4, 0, 0, -3, 1, 1, 4,
    3, -2, 3, 0, 0, -7, 0, 0,
    -5, 0, 0, -4, -1, -7, 0, -5,
    -1, 0, -4, 0, 1, 6, 0, -4,
    -1, 0, 0, 0, -2, 0, 0, -1,
    -10, 0, 0, -10, -1, 6, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    4, 0, 1, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 4, 1,
    0, 0, 1, 3, 1, 4, -1, 0,
    3, -1, -4, -18, 1, 4, 3, 0,
    -2, 0, 5, 0, 4, 0, 4, 0,
    0, 0, 0, -1, 4, 0, 0, -2,
    -5, 0, 0, -1, 0, -1, 0, 1,
    -2, -2, -3, 1, 0, -1, 0, 0,
    0, -5, 1, 0, -8, 0, 0, 0,
    0, -7, 1, -8, 0, 0, -4, -1,
    0, 13, -1, -2, 1, 1, -2, 0,
    -2, 1, 0, 0, -7, -3, 0, -13,
    0, 1, -8, 0, 8, -3, 0, -5,
    4, 0, -9, -13, -8, -3, 4, 0,
    0, -9, 0, 2, -3, 0, -2, 0,
    -3, 0, 4, 4, -16, 6, 0, 1,
    0, 0, 0, 0, 1, 1, -1, -3,
    0, 0, 0, -1, 0, 0, -1, 0,
    0, 0, -3, 0, 0, -3, 0, -3,
    0, 0, 0, 0, 1, -1, 0, 0,
    -1, 1, 1, 0, 0, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    -1, 0, 4, 0, 0, -1, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    -1, -1, 0, -1, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    -4, -1, -4, 3, 0, -3, 1, 3,
    4, 0, -3, 0, -2, 0, 0, -6,
    1, -1, 1, -7, 1, 0, -6, 0,
    3, -4, 0, 0, 0, -1, 0, 0,
    -1, 0, 0, 0, 0, 0, -1, -1,
    0, -1, -2, 0, 0, 0, 0, 0,
    0, -1, 0, 0, -2, 0, -1, 0,
    -3, 1, 0, -2, 1, 1, 1, 0,
    0, 0, 0, 0, 0, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, 4, -1, 0, -4, 0, 4, -6,
    -7, -6, -3, 1, 0, -1, -8, -2,
    0, -2, 0, -3, 2, -2, 0, 1,
    -1, -4, 1, 0, 0, 0, -1, 0,
    0, 1, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -1,
    0, 0, -4, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 6,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, -1, 0, 0, -2, 0, 1,
    0, -1, 0, 0, 0, -3, 0, 2,
    0, -6, -4, 0, 0, 0, -2, -6,
    0, 0, -1, 1, 0, -6, 0, -2,
    0, 0, -3, 1, 0, -2, 0, 0,
    0, 2, 0, 1, -3, -3, 0, -1,
    -1, -1, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, -3, 1, -4, 1, 0,
    1, 0, 0, 0, 1, 0, -1, 0,
    4, 0, 2, 0, 0, -2, 0, 3,
    0, 0, 0, 1, 0, 0, 4, 0,
    3, 0, 0, -8, 0, -1, 2, 4,
    -18, 0, 13, 2, -3, -3, 1, 1,
    -1, 0, -6, 0, 0, 6, -8, -3,
    0, -8, 4, 18, -8, 0, -1, 3,
    -4, 0, 0, -1, 0, 1, 17, -3,
    -1, 4, 4, -4, 1, 0, 0, 1,
    1, -1, -4, 0, -17, 3, 0, 0,
    0, 3, 3, 3, 0, 0, 4, 0,
    -8, -7, 0, 5, 4, 2, -5, 1,
    6, 0, 5, 0, 3, 1, 0, 7,
    0, 0, 0
};

/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 25,
    .right_class_cnt     = 27,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 2,
    .bpp = 4,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif

};

extern const lv_font_t font_body_symbols_data;


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t font_sm_data = {
#else
lv_font_t font_sm_data = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 7,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 6,           /*Cap height of the font*/
    .x_height = 4,               /*x-height of the font*/
#endif
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif

#if LV_VERSION_CHECK(9, 3, 0)
    .static_bitmap = 1,    /*Bitmaps are stored as const so they are always static if not compressed */
#endif

    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &font_body_symbols_data,
#endif
    .user_data = NULL,
};



#endif /*#if FONT_SM_DATA*/
