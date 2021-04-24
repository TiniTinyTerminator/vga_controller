/**
 * @file configuration.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "EE_API_LIB/inc/configuration.h"

void API_Set_resolution(uint32_t w, uint32_t h)
{
    _w = w;
    _h = h;
}

inline void API_Set_fill(uint8_t fill)
{
    _filled = fill;
}

inline void API_Set_line_thickness(uint32_t thickess)
{
    _line_thickness = thickess;
}

inline void API_Set_fill_color(uint8_t color)
{
    _fill_color = color;
}

inline void API_Set_draw_color(uint8_t color)
{
    _draw_color = color;
}

inline void API_Bind_draw_pixel_callback(DrawPixelCallback callback)
{
    _callback = callback;
}

inline void API_Draw_pixel(Pvector_t pos, uint8_t color)
{
    _callback(pos->x, pos->y, color);
}