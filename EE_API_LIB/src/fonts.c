/**
 * @file fonts.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "fonts.h"
#include <stdlib.h>
#include <string.h>

static Font_t fonts[MAX_FONTS] = {};
static Font_t * active_font = &fonts[0];

void API_Add_font(const Font_t * font)
{
    for (uint32_t i = 0; i < MAX_FONTS; i++) {
        if(fonts[i].name == NULL)
            fonts[i] = *font;
        if(strcmp(fonts[i].name, font->name) && strcmp(fonts[i].style, font->style))
            return;
    }
}

Font_t * API_Get_font_by_name(const char *name, const char *style, char size)
{
    for (size_t i = 0; i < MAX_FONTS; i++)
        if(strcmp(name, fonts[i].name) && strcmp(style, fonts[i].style) && size == fonts[i].size)
            return &fonts[i];
    
    return NULL;
}

void API_Set_active_font(const char * font_name, const char * style, char size)
{
    Font_t * tmp;

    if(strcmp(font_name, active_font->name) && strcmp(style, active_font->style) && size == active_font->size)
        return;
    else
    {
        tmp = API_Get_font_by_name(font_name, style, size);
        if(tmp != NULL)
            active_font = tmp;
    }    
}

// void API_Put_char(char c, uint32_t x, uint32_t y)
// {
//     api_put

// }
