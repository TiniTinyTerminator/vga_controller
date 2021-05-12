/**
 * @file graphics.h
 * @author Max Bensink (Max.bensink@student.hu.nl)
 * @brief An api that helps with drawing text on the display
 * @date 2021-05-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */


/**
 * @warning some of the design of the drawing functions defined below are adaptations of the work of Alois Zingls.
 * (Alois Zingl, <a href="http://members.chello.at/~easyfilter/Bresenham.pdf">bresenham.pdf</a>)
 */

#ifndef __SHAPES_H__
#define __SHAPES_H__

#include <inttypes.h>

/**
 * @brief the different draw styles
 * 
 */
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
 * @brief the pixel readout callback
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
 * @brief a function that save the display size
 * 
 * @param w width of the display
 * @param h height of the display
 */
void API_Set_resolution(uint32_t w, uint32_t h);

/**
 * @brief set an pixel on the display
 * 
 * @param x the x position
 * @param y the y position
 * @param color the color of the pixel
 */
void API_Set_pixel(int32_t x, int32_t y, uint8_t color);

/**
 * @brief get the value of a position in the screen
 * 
 * @param x the x position
 * @param y the y position
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
 * @brief draw function used in the api
 * 
 * @param x the x position to draw
 * @param y the y position to draw
 * @param color the color of the brush
 * @param size the size of the brush
 * @param draw_type the brush-type used
 */
void API_Draw(int32_t x, int32_t y, uint8_t color, uint32_t size, DrawStyle_t draw_type);

/**
 * @brief fill a square on the display width a certain color
 * 
 * @param x the x lup position of the display
 * @param y the y lup position of the display
 * @param w the width of the square
 * @param h the height of the square
 * @param color the color of the square
 */
void API_Fill_square(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);

/**
 * @brief draw a line on the display
 * 
 * @param xA the start x position
 * @param yA the start y position
 * @param xB the end x position
 * @param yB the end y position
 * @param color the color of the line
 * @param thickness the thickness of the line
 * @param draw_style the draw-style of the line, see @ref
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