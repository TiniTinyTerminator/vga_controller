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

#pragma once

#include <inttypes.h>

/**
 * @brief a struct for storing x and y positions
 * 
 */
typedef struct
{
    uint32_t x;
    uint32_t y;
} vector_t;

/**
 * @brief pointer to vector
 * 
 */
typedef vector_t *Pvector_t;

/**
 * @brief 
 * 
 * @param thickess 
 */
void API_Set_line_thickness(uint32_t thickess);

/**
 * @brief 
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
