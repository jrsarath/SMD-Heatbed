/*******************************************************************************
 * Size: 6 px
 * Bpp: 4
 * Opts: --font /fonts/Montserrat-Regular.ttf -o /fonts/font_xs_data.c --size 6 --bpp 4 --format lvgl --no-compress --symbols °—• --range 0x20-0x7F --lv-fallback font_body_symbols_data
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



#ifndef FONT_XS_DATA
#define FONT_XS_DATA 1
#endif

#if FONT_XS_DATA

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x70, 0x60, 0x40, 0x30,

    /* U+0022 "\"" */
    0x55, 0x22,

    /* U+0023 "#" */
    0x05, 0x13, 0x38, 0x75, 0x48, 0x83, 0x04, 0x50,

    /* U+0024 "$" */
    0x02, 0x00, 0x49, 0x61, 0x58, 0x00, 0x05, 0x63,
    0x48, 0x62, 0x02, 0x00,

    /* U+0025 "%" */
    0x55, 0x05, 0x03, 0x44, 0x62, 0x01, 0x53, 0x50,
    0x50, 0x54,

    /* U+0026 "&" */
    0x16, 0x60, 0x09, 0x40, 0x53, 0x64, 0x55, 0x66,
    0x00, 0x00,

    /* U+0027 "'" */
    0x52,

    /* U+0028 "(" */
    0x06, 0x32, 0x51, 0x32, 0x06,

    /* U+0029 ")" */
    0x60, 0x33, 0x14, 0x33, 0x60,

    /* U+002A "*" */
    0x37, 0x03, 0x70, 0x00, 0x00,

    /* U+002B "+" */
    0x02, 0x00, 0x29, 0x50, 0x06, 0x00,

    /* U+002C "," */
    0x06, 0x10,

    /* U+002D "-" */
    0x35,

    /* U+002E "." */
    0x40,

    /* U+002F "/" */
    0x00, 0x21, 0x00, 0x60, 0x00, 0x60, 0x04, 0x20,
    0x06, 0x00, 0x05, 0x00,

    /* U+0030 "0" */
    0x26, 0x62, 0x60, 0x06, 0x60, 0x06, 0x26, 0x62,

    /* U+0031 "1" */
    0x57, 0x06, 0x06, 0x06,

    /* U+0032 "2" */
    0x46, 0x80, 0x00, 0x70, 0x05, 0x20, 0x78, 0x51,

    /* U+0033 "3" */
    0x46, 0x90, 0x06, 0x50, 0x00, 0x60, 0x65, 0x70,

    /* U+0034 "4" */
    0x01, 0x50, 0x16, 0x10, 0x65, 0x95, 0x00, 0x60,

    /* U+0035 "5" */
    0x65, 0x50, 0x55, 0x50, 0x00, 0x51, 0x56, 0x70,

    /* U+0036 "6" */
    0x25, 0x50, 0x65, 0x60, 0x90, 0x06, 0x36, 0x62,

    /* U+0037 "7" */
    0x95, 0x92, 0x00, 0x70, 0x03, 0x30, 0x07, 0x00,

    /* U+0038 "8" */
    0x56, 0x63, 0x47, 0x82, 0x60, 0x06, 0x45, 0x63,

    /* U+0039 "9" */
    0x55, 0x70, 0x60, 0x54, 0x35, 0x63, 0x25, 0x60,

    /* U+003A ":" */
    0x40, 0x40,

    /* U+003B ";" */
    0x40, 0x06, 0x10,

    /* U+003C "<" */
    0x00, 0x00, 0x25, 0x50, 0x25, 0x40, 0x00, 0x00,

    /* U+003D "=" */
    0x25, 0x50, 0x35, 0x50,

    /* U+003E ">" */
    0x00, 0x00, 0x25, 0x40, 0x25, 0x50, 0x00, 0x00,

    /* U+003F "?" */
    0x55, 0x70, 0x07, 0x05, 0x00, 0x40,

    /* U+0040 "@" */
    0x05, 0x44, 0x51, 0x42, 0x65, 0x75, 0x56, 0x00,
    0x75, 0x42, 0x65, 0x85, 0x05, 0x44, 0x10,

    /* U+0041 "A" */
    0x04, 0x70, 0x00, 0x54, 0x10, 0x36, 0x56, 0x06,
    0x00, 0x51,

    /* U+0042 "B" */
    0x56, 0x57, 0x05, 0x66, 0x80, 0x52, 0x04, 0x15,
    0x65, 0x70,

    /* U+0043 "C" */
    0x17, 0x66, 0x07, 0x00, 0x00, 0x70, 0x00, 0x01,
    0x76, 0x60,

    /* U+0044 "D" */
    0x57, 0x57, 0x15, 0x20, 0x07, 0x52, 0x00, 0x75,
    0x75, 0x71,

    /* U+0045 "E" */
    0x57, 0x53, 0x56, 0x51, 0x52, 0x00, 0x57, 0x53,

    /* U+0046 "F" */
    0x57, 0x53, 0x52, 0x00, 0x56, 0x51, 0x52, 0x00,

    /* U+0047 "G" */
    0x17, 0x66, 0x07, 0x00, 0x00, 0x70, 0x05, 0x11,
    0x76, 0x70,

    /* U+0048 "H" */
    0x52, 0x04, 0x35, 0x65, 0x83, 0x52, 0x04, 0x35,
    0x20, 0x43,

    /* U+0049 "I" */
    0x52, 0x52, 0x52, 0x52,

    /* U+004A "J" */
    0x03, 0x65, 0x00, 0x15, 0x00, 0x15, 0x06, 0x72,

    /* U+004B "K" */
    0x52, 0x16, 0x05, 0x37, 0x00, 0x57, 0x71, 0x05,
    0x20, 0x70,

    /* U+004C "L" */
    0x52, 0x00, 0x52, 0x00, 0x52, 0x00, 0x57, 0x52,

    /* U+004D "M" */
    0x55, 0x00, 0x90, 0x57, 0x03, 0x90, 0x52, 0x66,
    0x60, 0x51, 0x30, 0x60,

    /* U+004E "N" */
    0x56, 0x04, 0x35, 0x64, 0x43, 0x52, 0x56, 0x35,
    0x20, 0x93,

    /* U+004F "O" */
    0x17, 0x67, 0x17, 0x00, 0x07, 0x70, 0x00, 0x71,
    0x76, 0x71,

    /* U+0050 "P" */
    0x57, 0x56, 0x52, 0x07, 0x56, 0x53, 0x52, 0x00,

    /* U+0051 "Q" */
    0x17, 0x67, 0x17, 0x00, 0x07, 0x70, 0x00, 0x71,
    0x76, 0x71, 0x00, 0x15, 0x40,

    /* U+0052 "R" */
    0x57, 0x56, 0x05, 0x20, 0x60, 0x56, 0x74, 0x05,
    0x20, 0x70,

    /* U+0053 "S" */
    0x45, 0x50, 0x54, 0x00, 0x01, 0x63, 0x45, 0x62,

    /* U+0054 "T" */
    0x5a, 0x52, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00,

    /* U+0055 "U" */
    0x51, 0x05, 0x15, 0x10, 0x51, 0x52, 0x05, 0x00,
    0x76, 0x60,

    /* U+0056 "V" */
    0x70, 0x06, 0x04, 0x30, 0x60, 0x07, 0x60, 0x00,
    0x57, 0x00,

    /* U+0057 "W" */
    0x70, 0x1a, 0x02, 0x44, 0x35, 0x61, 0x60, 0x07,
    0x60, 0x66, 0x00, 0x74, 0x08, 0x30,

    /* U+0058 "X" */
    0x52, 0x24, 0x07, 0x60, 0x07, 0x70, 0x61, 0x26,

    /* U+0059 "Y" */
    0x70, 0x05, 0x16, 0x60, 0x06, 0x30, 0x05, 0x20,

    /* U+005A "Z" */
    0x35, 0x86, 0x00, 0x70, 0x07, 0x00, 0x87, 0x54,

    /* U+005B "[" */
    0x55, 0x51, 0x51, 0x51, 0x55,

    /* U+005C "\\" */
    0x02, 0x00, 0x06, 0x00, 0x06, 0x00, 0x02, 0x40,
    0x00, 0x60, 0x00, 0x50,

    /* U+005D "]" */
    0x63, 0x33, 0x33, 0x33, 0x63,

    /* U+005E "^" */
    0x04, 0x00, 0x64, 0x41, 0x50,

    /* U+005F "_" */
    0x44, 0x40,

    /* U+0060 "`" */
    0x03, 0x00,

    /* U+0061 "a" */
    0x36, 0x83, 0x49, 0x55, 0x90,

    /* U+0062 "b" */
    0x60, 0x00, 0x66, 0x64, 0x61, 0x06, 0x66, 0x64,

    /* U+0063 "c" */
    0x36, 0x60, 0x60, 0x00, 0x46, 0x60,

    /* U+0064 "d" */
    0x00, 0x06, 0x46, 0x67, 0x60, 0x07, 0x46, 0x66,

    /* U+0065 "e" */
    0x45, 0x60, 0x74, 0x52, 0x36, 0x60,

    /* U+0066 "f" */
    0x36, 0x08, 0x60, 0x51, 0x05, 0x10,

    /* U+0067 "g" */
    0x46, 0x67, 0x60, 0x07, 0x46, 0x67, 0x25, 0x63,

    /* U+0068 "h" */
    0x60, 0x00, 0x66, 0x73, 0x60, 0x06, 0x60, 0x06,

    /* U+0069 "i" */
    0x30, 0x60, 0x60, 0x60,

    /* U+006A "j" */
    0x03, 0x00, 0x60, 0x06, 0x00, 0x60, 0x27, 0x00,

    /* U+006B "k" */
    0x60, 0x00, 0x60, 0x71, 0x68, 0x50, 0x60, 0x53,

    /* U+006C "l" */
    0x60, 0x60, 0x60, 0x60,

    /* U+006D "m" */
    0x65, 0x77, 0x56, 0x60, 0x06, 0x06, 0x60, 0x06,
    0x06,

    /* U+006E "n" */
    0x65, 0x73, 0x60, 0x06, 0x60, 0x06,

    /* U+006F "o" */
    0x36, 0x61, 0x60, 0x06, 0x46, 0x61,

    /* U+0070 "p" */
    0x66, 0x54, 0x61, 0x06, 0x66, 0x64, 0x60, 0x00,

    /* U+0071 "q" */
    0x46, 0x66, 0x60, 0x07, 0x46, 0x67, 0x00, 0x06,

    /* U+0072 "r" */
    0x66, 0x16, 0x00, 0x60, 0x00,

    /* U+0073 "s" */
    0x65, 0x34, 0x63, 0x45, 0x60,

    /* U+0074 "t" */
    0x20, 0x08, 0x60, 0x51, 0x02, 0x61,

    /* U+0075 "u" */
    0x60, 0x06, 0x60, 0x06, 0x37, 0x66,

    /* U+0076 "v" */
    0x70, 0x51, 0x42, 0x60, 0x0a, 0x10,

    /* U+0077 "w" */
    0x60, 0xa0, 0x50, 0x53, 0x45, 0x60, 0x0a, 0x07,
    0x30,

    /* U+0078 "x" */
    0x52, 0x60, 0x0b, 0x10, 0x61, 0x70,

    /* U+0079 "y" */
    0x07, 0x05, 0x10, 0x43, 0x60, 0x00, 0xa1, 0x00,
    0x65, 0x00,

    /* U+007A "z" */
    0x36, 0x80, 0x70, 0x86, 0x40,

    /* U+007B "{" */
    0x17, 0x24, 0x53, 0x24, 0x17,

    /* U+007C "|" */
    0x51, 0x51, 0x51, 0x51, 0x51,

    /* U+007D "}" */
    0x71, 0x42, 0x25, 0x42, 0x71,

    /* U+007E "~" */
    0x34, 0x20, 0x31, 0x50,

    /* U+00B0 "°" */
    0x23, 0x04, 0x22, 0x24, 0x00,

    /* U+2014 "—" */
    0x44, 0x44, 0x44,

    /* U+2022 "•" */
    0x52
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 25, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 25, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 36, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 6, .adv_w = 67, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 14, .adv_w = 59, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 26, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 46, .adv_w = 19, .box_w = 1, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 47, .adv_w = 32, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 52, .adv_w = 32, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 57, .adv_w = 37, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 62, .adv_w = 55, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 68, .adv_w = 20, .box_w = 1, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 70, .adv_w = 37, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 71, .adv_w = 20, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 32, .box_w = 4, .box_h = 6, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 84, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 92, .adv_w = 35, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 55, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 54, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 63, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 120, .adv_w = 54, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 58, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 57, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 61, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 58, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 20, .box_w = 1, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 20, .box_w = 1, .box_h = 5, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 165, .adv_w = 55, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 55, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 177, .adv_w = 55, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 54, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 99, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 206, .adv_w = 69, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 72, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 68, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 236, .adv_w = 79, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 246, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 254, .adv_w = 61, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 74, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 78, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 282, .adv_w = 29, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 48, .box_w = 4, .box_h = 4, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 68, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 57, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 312, .adv_w = 92, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 78, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 81, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 69, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 81, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 365, .adv_w = 69, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 59, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 55, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 391, .adv_w = 76, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 401, .adv_w = 67, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 107, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 63, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 433, .adv_w = 61, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 441, .adv_w = 62, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 31, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 454, .adv_w = 32, .box_w = 4, .box_h = 6, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 466, .adv_w = 31, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 471, .adv_w = 55, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 476, .adv_w = 48, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 478, .adv_w = 58, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 480, .adv_w = 57, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 65, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 493, .adv_w = 54, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 65, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 58, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 33, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 519, .adv_w = 66, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 527, .adv_w = 65, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 535, .adv_w = 26, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 539, .adv_w = 26, .box_w = 3, .box_h = 5, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 547, .adv_w = 57, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 555, .adv_w = 26, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 559, .adv_w = 102, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 65, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 574, .adv_w = 60, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 580, .adv_w = 65, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 588, .adv_w = 65, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 596, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 601, .adv_w = 47, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 606, .adv_w = 39, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 612, .adv_w = 65, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 618, .adv_w = 52, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 624, .adv_w = 84, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 633, .adv_w = 51, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 639, .adv_w = 52, .box_w = 5, .box_h = 4, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 649, .adv_w = 49, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 654, .adv_w = 32, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 659, .adv_w = 28, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 664, .adv_w = 32, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 669, .adv_w = 55, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 673, .adv_w = 40, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 678, .adv_w = 96, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 681, .adv_w = 28, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 1}
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
    0, 0, 0, 0, 4, 0, 3, -2,
    0, 2, 0, -5, -6, 1, 5, 2,
    2, -4, 1, 5, 0, 4, 1, 3,
    -2, 0, 6, 0, -1, 2, 0, -3,
    0, 0, 0, 0, -2, 2, 2, 0,
    0, -1, 0, -1, 1, 0, -1, 0,
    -1, 0, -2, 0, 0, -1, 0, -2,
    -1, 0, -3, 0, -11, 0, -2, -5,
    2, 3, 0, 0, -2, 1, 1, 3,
    2, -2, 2, 0, 0, -6, 0, 0,
    -4, 0, 0, -3, -1, -5, 0, -4,
    -1, 0, -3, 0, 0, 4, 0, -3,
    0, 0, 0, 0, -2, 0, 0, -1,
    -7, 0, 0, -8, 0, 4, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 1, 0, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 3, 0,
    0, 0, 1, 2, 1, 3, -1, 0,
    2, -1, -3, -13, 1, 3, 2, 0,
    -1, 0, 4, 0, 3, 0, 3, 0,
    0, 0, 0, -1, 3, 0, 0, -2,
    -4, 0, 0, -1, 0, -1, 0, 1,
    -2, -1, -2, 1, 0, -1, 0, 0,
    0, -4, 1, 0, -6, 0, 0, 0,
    0, -5, 1, -6, 0, 0, -3, -1,
    0, 10, -1, -1, 1, 1, -1, 0,
    -1, 1, 0, 0, -5, -2, 0, -9,
    0, 1, -6, 0, 6, -2, 0, -4,
    3, 0, -6, -9, -6, -2, 3, 0,
    0, -7, 0, 1, -2, 0, -1, 0,
    -2, 0, 3, 3, -12, 5, 0, 1,
    0, 0, 0, 0, 1, 1, -1, -2,
    0, 0, 0, -1, 0, 0, -1, 0,
    0, 0, -2, 0, 0, -2, 0, -2,
    0, 0, 0, 0, 1, -1, 0, 0,
    -1, 1, 1, 0, 0, 0, 0, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    -1, 0, 3, 0, 0, -1, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -1, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, 0,
    -3, -1, -3, 2, 0, -2, 1, 2,
    3, 0, -2, 0, -1, 0, 0, -5,
    1, -1, 1, -5, 1, 0, -5, 0,
    2, -3, 0, 0, 0, -1, 0, 0,
    -1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -1, 0, 0, 0, 0, 0,
    0, -1, 0, 0, -1, 0, -1, 0,
    -2, 1, 0, -1, 0, 1, 1, 0,
    0, 0, 0, 0, 0, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, 3, -1, 0, -3, 0, 3, -5,
    -5, -4, -2, 1, 0, -1, -6, -2,
    0, -2, 0, -2, 1, -2, 0, 1,
    0, -3, 0, 0, 0, 0, -1, 0,
    0, 1, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -1,
    0, 0, -3, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 4,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, -1, 0, 0, -2, 0, 1,
    0, -1, 0, 0, 0, -2, 0, 1,
    0, -5, -3, 0, 0, 0, -1, -5,
    0, 0, -1, 1, 0, -5, 0, -2,
    0, 0, -2, 1, 0, -2, 0, 0,
    0, 1, 0, 1, -2, -2, 0, -1,
    -1, -1, 0, 0, 0, 0, 0, 0,
    -3, 0, 0, -2, 0, -3, 1, 0,
    0, 0, 0, 0, 0, 0, -1, 0,
    3, 0, 1, 0, 0, -1, 0, 2,
    0, 0, 0, 0, 0, 0, 3, 0,
    2, 0, 0, -6, 0, -1, 2, 3,
    -13, 0, 10, 1, -2, -2, 1, 1,
    -1, 0, -5, 0, 0, 4, -6, -2,
    0, -6, 3, 13, -6, 0, -1, 2,
    -3, 0, 0, -1, 0, 1, 13, -2,
    -1, 3, 3, -3, 1, 0, 0, 1,
    1, -1, -3, 0, -12, 2, 0, 0,
    0, 2, 2, 2, 0, 0, 3, 0,
    -6, -6, 0, 4, 3, 2, -4, 1,
    4, 0, 4, 0, 2, 1, 0, 5,
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
const lv_font_t font_xs_data = {
#else
lv_font_t font_xs_data = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 7,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 4,           /*Cap height of the font*/
    .x_height = 3,               /*x-height of the font*/
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



#endif /*#if FONT_XS_DATA*/
