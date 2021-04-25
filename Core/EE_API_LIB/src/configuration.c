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

#include "shapes.h"
#include <stddef.h>

static uint32_t _w;

static uint32_t _h;

void API_Set_resolution(uint32_t w, uint32_t h)
{
    _w = w;
    _h = h;
}

static uint8_t _filled = 0x0;

inline void API_Set_fill(uint8_t fill)
{
    _filled = fill;
}

static uint32_t _line_thickness = 0x1;

inline void API_Set_line_thickness(uint32_t thickess)
{
    _line_thickness = thickess;
}

static uint8_t _fill_color = 0xFF;

inline void API_Set_fill_color(uint8_t color)
{
    _fill_color = color;
}

static uint8_t _draw_color = 0xFF;

inline void API_Set_draw_color(uint8_t color)
{
    _draw_color = color;
}

static DrawPixelCallback _callback = NULL;

inline void API_Bind_draw_pixel_callback(DrawPixelCallback callback)
{
    _callback = callback;
}