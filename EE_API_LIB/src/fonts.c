/**
 * @file fonts.c
 * @author Max Bensink (Max.bensink@student.hu.nl)
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

#define BITSINBYTE 8

void API_Put_text(const char *string, uint32_t length, uint32_t x, uint32_t y, Font_t *font, uint8_t size, FontStyles_t style, uint8_t color)
{
    uint8_t *data = (uint8_t *)malloc(length);

    memcpy(data, string, length);

    uint8_t *end_char = data + length;

    for (uint8_t *c = data; c < end_char; c++)
    {
        uint32_t i;
        for(i = 0; i < font->size; i++)
        {
            Glyph_t * glyph = &font->glyphs[i];
            if (*c == glyph->character)
            {
                
                API_Load_glyph(font, glyph, x, y, size, style, color);

                x += glyph->w;
                break;
            }

        }

        if(i + 1 >= font->size)
            API_Draw_square(x, y, font->glyphs->w, font->glyphs->h, color, 1);
    }
}

void API_Put_char(char c, Font_t *font, uint32_t x, uint32_t y, uint8_t size, FontStyles_t style, uint8_t color)
{

    uint32_t i;

    for (i = 0; i < font->size; i++)
    {
        if (c == font->glyphs[i].character)
        {
            API_Load_glyph(font, &font->glyphs[i], x, y, size, style, color);

            return;
        }
    }

    if(i + 1 >= font->size)
        API_Draw_square(x, y, font->glyphs->w, font->glyphs->h, color, 1);

}

void API_Load_glyph(Font_t *font, Glyph_t *glyph, uint32_t x, uint32_t y, uint8_t size, FontStyles_t styles, uint8_t color)
{
    for (uint32_t y_offset = 0; y_offset < glyph->h; y_offset++)
    {
        for (uint32_t x_offset = 0; x_offset < glyph->w; x_offset++)
        {
            div_t byte_offset = div(glyph->x_off + x_offset, BITSINBYTE);
            uint32_t needs_drawing = (font->frame.data[font->frame.width * y_offset + byte_offset.quot] & (1 << byte_offset.rem));

            if (needs_drawing)
                API_Set_pixel(x + x_offset, y + y_offset, color);
        }
    }
}

// void API_load_glyph(Glyph_t *glyph, uint32_t x, uint32_t y, uint8_t size)
// {

// }
