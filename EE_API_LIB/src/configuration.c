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

SetPixelCallback_t _set_pixel_callback = NULL;

inline void API_Bind_set_pixel_callback(SetPixelCallback_t callback)
{
    _set_pixel_callback = callback;
}

SetFillScreenCallback_t _fill_screen_callback = NULL;

inline void API_Bind_fill_screen_callback(SetFillScreenCallback_t callback)
{
    _fill_screen_callback = callback;
}
