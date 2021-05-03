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

#include "graphics.h"
#include <stddef.h>

uint32_t _w;

uint32_t _h;

void API_Set_resolution(uint32_t w, uint32_t h)
{
    _w = w;
    _h = h;
}

SetPixelCallback _set_pixel_callback = NULL;

inline void API_Bind_set_pixel_callback(SetPixelCallback callback)
{
    _set_pixel_callback = callback;
}

SetFillScreenCallback _fill_screen_callback = NULL;

inline void API_Bind_fill_screen_callback(SetFillScreenCallback callback)
{
    _fill_screen_callback = callback;
}
