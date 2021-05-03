/**
 * @file shapes.h
 * @author Max Bensink (max.bensink@student.hu.nl)
 * @brief drawing functions useable for a display
 * @version 0.3
 * @date 2021-04-21
 * 
 * @copyright Copyright (c) 2021
 * 
 * @attention some of the design of the drawing functions defined below are adaptations of the work of Alois Zingls.
 * (Alois Zingl, <a href="http://members.chello.at/~easyfilter/Bresenham.pdf">bresenham.pdf</a>)
 * 
 */

#ifndef __SHAPES_H__
#define __SHAPES_H__

#include <inttypes.h>

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
 * @brief fill the framebuffer with a certain color
 * 
 * @param color the color
 */
void API_Fill_screen(uint8_t color);

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
void API_Draw_line(int32_t xA, int32_t yA, int32_t xB, int32_t yB, uint8_t color);

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param width 
 * @param height 
 */
void API_Draw_square(int32_t x, int32_t y, uint32_t width, uint32_t height, uint8_t color);

/**
 * @brief 
 * 
 * @param list_X 
 * @param list_Y 
 * @param length 
 */
void API_Draw_polygon(const int32_t * list_X, const int32_t * list_Y, uint32_t length, uint8_t color);

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param radius 
 */
void API_Draw_circle(int32_t x, int32_t y, uint32_t radius, uint8_t color);

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

#endif