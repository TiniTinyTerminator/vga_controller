/**
 * @file fonts.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __API_FONTS_H__
#define __API_FONTS_H__

#include "graphics.h"
#include <inttypes.h>

#define MAX_FONTS 12

/**
 * @brief struct define of 
 * 
 */
typedef struct Glyphs
{
    char character;
    
    uint16_t w, h;

    uint16_t x_off, y_off;
    
    const uint8_t * payload;

} Glyph_t;

typedef struct Fonts {
    char *name;
    char *style;
    uint16_t size;
    uint16_t length;

    Glyph_t * glyphs;

} Font_t;

/**
 * @brief 
 * 
 * @param string 
 * @param length 
 * @param size 
 */
void API_Put_text(const char * string, uint32_t length);

/**
 * @brief 
 * 
 * @param c 
 */
void API_Put_char(char c, const char * font_name, const char * style, char size);

/**
 * @brief add font to api
 * 
 * @param font pointer to font information
 */
void API_Add_font(const Font_t * font);

// /**
//  * @brief 
//  * 
//  * @param font 
//  */
// void API_Remove_font(const Font_t * font);

// /**
//  * @brief 
//  * 
//  * @param font 
//  */
// void API_Remove_font_by_name(const char * font);

#endif