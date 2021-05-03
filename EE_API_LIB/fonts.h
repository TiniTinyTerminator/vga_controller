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

enum FontNames
{
    ARIAL,
    CONSOLAS
};

enum FontStyle
{
    NORMAL,
    BOLD,
    ITALIC
};

/**
 * @brief 
 * 
 * @param string 
 * @param length 
 * @param size 
 */
void API_Put_text(const char * string, uint32_t length, uint8_t font_size, FontNames font_name, FontStyle font_style);

/**
 * @brief 
 * 
 * @param font_name 
 */
void API_Set_Font(FontNames font_name);

#endif