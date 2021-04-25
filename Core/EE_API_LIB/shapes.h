/**
 * @file shapes.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/*! \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 */

#ifndef __SHAPES_H__
#define __SHAPES_H__

#include <inttypes.h>

/**
 * @brief a struct for storing x and y positions
 * 
 */
typedef struct
{
    int32_t x;
    int32_t y;
} vector_t;

/**
 * @brief pointer to vector
 * 
 */
typedef vector_t *Pvector_t;

/**
 * @brief callback type to bind function thats able to set pixels
 * 
 */
typedef void (* SetPixelCallback)(uint32_t x, uint32_t y, uint32_t color);

/**
 * @brief callback type that changes background
 * 
 */
typedef void (* SetFillScreenCallback)(uint32_t color);

/**
 * @brief this functions implements the function is able to set pixels in the framebuffer.
 * 
 * @param callback address of callback function
 */
void API_Bind_set_pixel_callback(SetPixelCallback callback);

/**
 * @brief this function implements the functions that se
 * 
 * @param callback 
 */
void API_Bind_fill_screen_callback(SetFillScreenCallback callback);

/**
 * @brief set the resolution of the used display
 * 
 * @param w 
 * @param h 
 */
void API_Set_resolution(uint32_t w, uint32_t h);

/**
 * @brief 
 * 
 * @param thickess 
 */
void API_Set_line_thickness(uint32_t thickess);

/**
 * @brief abababa
 * 
 * @param color 
 */
void API_Set_fill_color(uint8_t color);

/**
 * @brief 
 * 
 * @param color 
 */
void API_Set_draw_color(uint8_t color);

/**
 * @brief 
 * 
 * @param fill 
 */
void API_Set_fill(uint8_t fill);

/**
 * @brief draw pixel at a certain position
 * 
 * @param pos 
 */
void API_Set_Pixel(const Pvector_t pos, uint8_t color);

/**
 * @brief fill the framebuffer with a certain color
 * 
 * @param color the color
 */
void API_fill_screen(uint8_t color);

/**
 * @brief 
 * 
 * @param start 
 * @param end 
 */
void API_Draw_vector(const Pvector_t start, const Pvector_t end);

/**
 * @brief 
 * 
 * @param start 
 * @param width 
 * @param height 
 */
void API_Draw_square(const Pvector_t start, uint32_t width, uint32_t height);

/**
 * @brief 
 * 
 * @param vector_list 
 * @param length 
 */
void API_Draw_polygon(const Pvector_t * vector_list, uint32_t length);

/**
 * @brief 
 * 
 * @param position 
 * @param radius 
 */
void API_Draw_circle(const Pvector_t position, uint32_t radius);

/**
 * @brief 
 * 
 * @param string 
 * @param length 
 */
void API_Put_text(const char * string, uint32_t length);

/**
 * @brief 
 * 
 * @param string 
 * @param length 
 * @param border 
 */
void API_Put_textBox(const char * string, uint32_t length, uint32_t border);

/**
 * @brief check if object is in framebuffer
 * 
 * @param w 
 * @param h 
 */
char API_Check_inbounds(const Pvector_t, uint32_t w, uint32_t h);

#endif