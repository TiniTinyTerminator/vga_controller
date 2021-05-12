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
 * @brief the different available font styles
 * 
 */
typedef enum FontStyles {
    NORMAL = 0b00,
    BOLD = 0b01,
    ITALIC = 0b10,
    BOLDITALIC = 0b11
} FontStyles_t;

/**
 * @brief struct definition of a glyph (and small part of an image)
 * 
 */
typedef struct Glyphs
{
    char character;
    
    uint16_t w, h;

    uint16_t x_off, y_off;
    
} Glyph_t;

/**
 * @brief a struct definition for information about the font
 * 
 */
typedef struct Fonts {
    //!@brief the name of the font
    char *name;
    //!@brief the amount of glyphs in the font
    uint32_t size;
    //!@brief a pointer to the array of glyphs
    Glyph_t * glyphs;
    //!@brief the space between the fonts
    uint8_t spacing_in_bits;

    /**
     * @brief the internal struct for the dataframe of the font
     * 
     */
    struct data_frame {
        //!@brief a pointer to the data
        uint8_t * data;
        //!@brief the width of the frame in bits
        uint32_t width;
        //!@brief the height of the frame in bits
        uint32_t height;
    } frame;

} Font_t;

/**
 * @brief display the given text on the display
 * 
 * @param string the string to display
 * @param length the length of the string
 * @param x the x position
 * @param y the y position
 * @param font the font to use for the text
 * @param size the size to use for the font
 * @param style the style of the text, see @ref FontStyles
 * @param color the color of the string
 */
void API_Put_text(const char *string, uint32_t length, uint32_t x, uint32_t y, Font_t *font, uint8_t size, FontStyles_t style, uint8_t color);

/**
 * @brief put a single character on the display
 * 
 * @param c the character
 * @param x the x position
 * @param y the y position
 * @param font the font to use for the character
 * @param size the size to use for the font
 * @param style the styles of the text, see @ref FontStyles
 */
void API_Put_char(char c, uint32_t x, uint32_t y, Font_t *font, uint8_t size, FontStyles_t style, uint8_t color);

/**
 * @brief load a glyph from the font out of the data array
 * 
 * @param font the font of the glyph
 * @param glyph the glyph to print
 * @param x the x position
 * @param y the y position
 * @param size the size to generate the glyph in
 * @param styles the style to generate the glyph in, see @ref FontStyles
 * @param color the color of the glyph
 */
void API_Load_glyph(Font_t *font, Glyph_t *glyph, uint32_t x, uint32_t y, uint8_t size, FontStyles_t styles, uint8_t color);

#endif
