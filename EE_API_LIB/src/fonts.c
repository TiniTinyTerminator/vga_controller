/**
 * @file fonts.c
 * @author Max Bensink (Max.bensink@student.hu.nl)
 * @brief the source file of the @ref fonts.h files
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
        for (i = 0; i < font->size; i++)
        {
            Glyph_t *glyph = &font->glyphs[i];
            if (*c == glyph->character)
            {
                API_Load_glyph(font, glyph, x, y, size, style, color);

                x += glyph->w * size + size;
                break;
            }
        }

        if (i + 1 > font->size)
            API_Draw_square(x, y, font->glyphs->w, font->glyphs->h, color, 1);
    }
}

void API_Put_char(char c, uint32_t x, uint32_t y, Font_t *font, uint8_t size, FontStyles_t style, uint8_t color)
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

    if (i + 1 >= font->size)
        API_Draw_square(x, y, font->glyphs->w, font->glyphs->h, color, 1);
}

void API_Load_glyph(Font_t *font, Glyph_t *glyph, uint32_t x, uint32_t y, uint8_t size, FontStyles_t styles, uint8_t color)
{
    div_t bit_row = div(font->frame.width, 8);

    // size--;

    for (uint32_t col = glyph->x_off; col < (glyph->x_off + glyph->w); col++)
    {
        for (uint32_t row = glyph->y_off; row < (glyph->y_off + glyph->h); row++)
        {
            div_t bit_x = div(col, 8);

            uint32_t row_bytes = (bit_row.rem > 0) ? bit_row.quot + 1 : bit_row.quot;

            if (font->frame.data[bit_x.quot + row * row_bytes] & (1 << bit_x.rem))
                API_Fill_square(x + (col - glyph->x_off) * size, y + (row - glyph->y_off) * size, size, size, color);
        }
    }
}
