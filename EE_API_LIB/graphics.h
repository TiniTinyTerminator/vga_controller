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
 *      @mainpage Introduction 
 *      @brief in this document will be explained how the EE_API_LIB works and how it can be used.
 *      under here will be some files to look into.
 *      @see graphics.h
 *      @see graphics.c
 *      @see bitmap.c
 *      @see fonts.c
 *      @see extra.h
 *      @see extra.c
 * 
 *      @brief In this part we have few main functions used by the program
 *      @see API_Set_pixel(int32_t x, int32_t y, uint8_t color);
 *      @see API_Draw(int32_t x, int32_t y, uint8_t color, uint32_t size, DrawStyle_t draw_type);
 *      @see API_Load_bitmap(uint32_t x_lup, uint32_t y_lup, uint32_t w, uint32_t h, const uint8_t *bitmap);
 *      @see API_Draw_line(int32_t xA, int32_t yA, int32_t xB, int32_t yB, uint8_t color, uint32_t thickness, DrawStyle_t draw_style);
 *      <hr/>
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
typedef enum DrawStyle
{
    DOT,
    ROUND,
    SQUARE
} DrawStyle_t;

/**
 * @brief callback type to bind function thats able to set pixels
 * 
 */
typedef void (*SetPixelCallback_t)(uint32_t x, uint32_t y, uint32_t color);

/**
 * @brief the pixel readout callback
 * 
 */
typedef uint8_t (*GetPixelCallback_t)(uint32_t x, uint32_t y);

/**
 * @brief callback type that changes background
 * 
 */
typedef void (*SetFillScreenCallback_t)(uint32_t color);

/**
 * @brief this functions implements the function is able to set pixels in the framebuffer.
 * 
 * @param callback address of set pixel function
 */
void API_Bind_set_pixel_callback(SetPixelCallback_t callback);

/**
 * @brief this functions implements the function is able to get pixels from the framebuffer.
 * 
 * @param callback address of the get pixel function
 */
void API_Bind_get_pixel_callback(GetPixelCallback_t callback);

/**
 * @brief this function implements the functions that fills the screen if avaiblabe.
 * 
 * @param callback address of the fill screen function
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
 * @brief draw a square on the display
 * 
 * @param x_lup the x lup position
 * @param y_lup the y lup position
 * @param width the width of the square
 * @param height the height of the square
 * @param color the color of the lines
 * @param thickness the thickness of the lines
 */
void API_Draw_square(int32_t x_lup, int32_t y_lup, uint32_t width, uint32_t height, uint8_t color, uint32_t thickness);

/**
 * @brief draw a polygon on the display
 * 
 * @param list_X a list of the x positions of the polygon
 * @param list_Y a list of the y positions of the polygon
 * @param length the length of the arrays
 * @param color the color of the lines
 * @param thickness the thickness of the lines
 * @param draw_style the draw style of the lines
 */
void API_Draw_polygon(const int32_t *list_X, const int32_t *list_Y, uint32_t length, uint8_t color, uint32_t thickness, DrawStyle_t draw_style);

/**
 * @brief draw a circle on the display
 * 
 * @param xm the x position of the middle of the circle
 * @param ym the y position of the middle of the circle
 * @param radius the radius of the circle
 * @param color the color of the circle
 * @param thickness the thickness of the line
 */
void API_Draw_circle(int32_t xm, int32_t ym, int32_t radius, uint8_t color, uint32_t thickness);

/**
 * @brief draw a filled circle on the display 
 * 
 * @param xm the x position of the middle of the circle
 * @param ym the y position of the middle of the circle
 * @param radius the radius of the circle
 * @param color the color of the circle
 */
void API_Fill_circle(int32_t xm, int32_t ym, int32_t radius, uint8_t color);

/**
 * @brief a function that checks if what is drawn is in the framebuffer
 * 
 * @param x the x lup position of the object
 * @param y the y lup position of the object
 * @param w the width of the object
 * @param h the height of the object
 * @return char
 * @retval 1 if shape fits in display
 * @retval 0 if shape does not fit in display
 * @retval -1 if shape is completely out of display
 */
char API_Check_inbounds(int32_t x, int32_t y, uint32_t w, uint32_t h);

/**
 * @brief load an bitmap into the framebuffer
 * 
 * @param x_lup the x lup of position
 * @param y_lup the y lup of the position
 * @param w the width of the bitmap
 * @param h the height of the bitmap
 * @param bitmap the bitmap array
 */
void API_Load_bitmap(uint32_t x_lup, uint32_t y_lup, uint32_t w, uint32_t h, const uint8_t *bitmap);

#endif