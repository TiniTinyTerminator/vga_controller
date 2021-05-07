/**
 * @file shapes.h
 * @author Max Bensink (max.bensink@student.hu.nl)
 * @brief drawing functions useable for a display
 * @version 0.3
 * @date 2021-04-21
 * 
 * @copyright Copyright (c) 2021
 * 
 * 
 */

#ifndef __SHAPES_H__
#define __SHAPES_H__

#include <inttypes.h>

typedef enum DrawStyle {
    DOT,
    ROUND,
    SQUARE
} DrawStyle_t;


/**
 * @brief callback type to bind function thats able to set pixels
 * 
 */
typedef void (* SetPixelCallback_t)(uint32_t x, uint32_t y, uint32_t color);

/**
 * @brief 
 * 
 */
typedef uint8_t (* GetPixelCallback_t)(uint32_t x, uint32_t y);

/**
 * @brief callback type that changes background
 * 
 */
typedef void (* SetFillScreenCallback_t)(uint32_t color);

/**
 * @brief this functions implements the function is able to set pixels in the framebuffer.
 * 
 * @param callback address of callback function
 */
void API_Bind_set_pixel_callback(SetPixelCallback_t callback);

/**
 * @brief 
 * 
 * @param callback 
 */
void API_Bind_get_pixel_callback(GetPixelCallback_t callback);

/**
 * @brief this function implements the functions that se
 * 
 * @param callback 
 */
void API_Bind_fill_screen_callback(SetFillScreenCallback_t callback);

/**
 * @brief 
 * 
 * @param w 
 * @param h 
 */
void API_Set_resolution(uint32_t w, uint32_t h);

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param color 
 */
void API_Set_pixel(int32_t x, int32_t y, uint8_t color);

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @return uint8_t 
 */
uint8_t API_Get_pixel(int32_t x, int32_t y);

/**
 * @brief fill the framebuffer with a certain color
 * 
 * @param color the color
 */
void API_Fill_screen(uint8_t color);

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param color 
 * @param size 
 * @param draw_type 
 */
void API_Draw(int32_t x, int32_t y, uint8_t color, uint32_t size, DrawStyle_t draw_type);

/**
 * @brief fil
 * 
 * @param x 
 * @param y 
 * @param w 
 * @param h 
 * @param color 
 */
void API_Fill_square(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);

/**
 * @brief 
 * 
 * @param xA 
 * @param yA 
 * @param xB 
 * @param yB 
 */
void API_Draw_line(int32_t xA, int32_t yA, int32_t xB, int32_t yB, uint8_t color, uint32_t thickness, DrawStyle_t draw_style);

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param width 
 * @param height 
 */
void API_Draw_square(int32_t x, int32_t y, uint32_t width, uint32_t height, uint8_t color, uint32_t thickness);

/**
 * @brief 
 * 
 * @param list_X 
 * @param list_Y 
 * @param length 
 */
void API_Draw_polygon(const int32_t * list_X, const int32_t * list_Y, uint32_t length, uint8_t color, uint32_t thickness, DrawStyle_t draw_style);

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param radius 
 */
void API_Draw_circle(int32_t xm, int32_t ym, int32_t radius, uint8_t color, uint32_t thickness);

/**
 * @brief 
 * 
 * @param xm 
 * @param ym 
 * @param r 
 * @param color 
 */
void API_Fill_circle(int32_t xm, int32_t ym, int32_t radius, uint8_t color);

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param w 
 * @param h 
 * @retval 1 if shape fits in display
 * @retval 0 if shape does not fit in display
 * @retval -1 if shape is completely out of display
 */
char API_Check_inbounds(int32_t x, int32_t y, uint32_t w, uint32_t h);

/**
 * @brief 
 * 
 * @param x_lup 
 * @param y_lup 
 * @param w 
 * @param h 
 * @param bitmap 
 */
void API_Load_bitmap(uint32_t x_lup, uint32_t y_lup, uint32_t w, uint32_t h, const uint8_t *bitmap);

#endif