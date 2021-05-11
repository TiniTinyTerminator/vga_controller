/**
 * @file fonts.h
 * @author Max Bensink (Max.bensink@student.hu.nl)
 * @brief some functions for the abillity to draw text on a display
 * @date 2021-04-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */



#ifndef __API_FONTS_H__
#define __API_FONTS_H__

#include "graphics.h"
#include <inttypes.h>

/**
 * @brief 
 * 
 */
typedef enum FontStyles {
    NORMAL = 0b00,
    ITALIC = 0b01,
    BOLD = 0b10,
    BOLDITALIC = 0b11
} FontStyles_t;

/**
 * @brief struct define of 
 * 
 */
typedef struct Glyphs
{
    char character;
    
    uint16_t w, h;

    uint16_t x_off, y_off;
    
    // const uint8_t * payload;

    // struct kerning {
    //     uint16_t x_off;
    // };
    
} Glyph_t;

/**
 * @brief 
 * 
 */
typedef struct Fonts {
    char *name;

    uint32_t size;

    Glyph_t * glyphs;

    uint8_t spacing_in_bits;

    struct data_frame {
        uint8_t * data;

        uint32_t width;
        uint32_t height;
    } frame;

} Font_t;

/**
 * @brief 
 * 
 * @param string 
 * @param length 
 * @param font 
 * @param size 
 */
void API_Put_text(const char *string, uint32_t length, uint32_t x, uint32_t y, Font_t *font, uint8_t size, FontStyles_t style, uint8_t color);

/**
 * @brief 
 * 
 * @param c 
 * @param font 
 * @param x 
 * @param y 
 * @param size 
 * @param style 
 */
void API_Put_char(char c, Font_t *font, uint32_t x, uint32_t y, uint8_t size, FontStyles_t style, uint8_t color);

/**
 * @brief 
 * 
 * @param font 
 * @param glyph 
 * @param x 
 * @param y 
 * @param size 
 * @param styles 
 * @param color 
 */
void API_Load_glyph(Font_t *font, Glyph_t *glyph, uint32_t x, uint32_t y, uint8_t size, FontStyles_t styles, uint8_t color);

#endif