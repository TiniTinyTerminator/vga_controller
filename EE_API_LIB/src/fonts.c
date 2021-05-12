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
    // allocate memory
    uint8_t *data = (uint8_t *)malloc(length);

    // copy string into dynamic memory
    memcpy(data, string, length);

    //calculate the end position of the string
    uint8_t *end_char = data + length;

    //loop thru every character
    for (uint8_t *c = data; c < end_char; c++)
    {
        //loop thru every possible glyph
        uint32_t i;
        for (i = 0; i < font->size; i++)
        {
            //access glyph
            Glyph_t *glyph = &font->glyphs[i];

            // if characters are the same, place glyph and add width to x position
            if (*c == glyph->character)
            {
                API_Load_glyph(font, glyph, x, y, size, style, color);

                x += glyph->w * size + size;
                break;
            }
        }
        //draw square if glyph does not exist
        if (i + 1 > font->size)
            API_Draw_square(x, y, font->glyphs->w, font->glyphs->h, color, 1);
    }

    //clear memory
    memset(data, 0, length);
    //free memory
    free(data);
}

void API_Put_char(char c, uint32_t x, uint32_t y, Font_t *font, uint8_t size, FontStyles_t style, uint8_t color)
{
    uint32_t i;

    ///see @ref API_Put_text forloop for explanation
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
    //calculate the amount of bytes per row
    div_t bit_row = div(font->frame.width, 8);

    // go thru every bit in the bytes
    for (uint32_t col = glyph->x_off; col < (glyph->x_off + glyph->w); col++)
    {
        //go thru every row
        for (uint32_t row = glyph->y_off; row < (glyph->y_off + glyph->h); row++)
        {
            //calculate the bit offset in the bytes
            div_t bit_x = div(col, 8);
            
            // check for extra byte
            uint32_t row_bytes = (bit_row.rem > 0) ? bit_row.quot + 1 : bit_row.quot;

            // if bit is one, then set area
            if (font->frame.data[bit_x.quot + row * row_bytes] & (1 << bit_x.rem))
                API_Fill_square(x + (col - glyph->x_off) * size, y + (row - glyph->y_off) * size, size, size, color);
        }
    }
}
