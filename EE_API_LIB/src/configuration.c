/**
 * @file configuration.c
 * @author Max Bensink (Max.bensink@student.hu.nl)
 * @brief 
 * @date 2021-04-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "graphics.h"
#include <stddef.h>

//!@brief internal width variable
uint32_t _w;

//!@brief internal height variable
uint32_t _h;

void API_Set_resolution(uint32_t w, uint32_t h)
{
    /**
     * @brief set the width and height variable
     * 
     */
    _w = w;
    _h = h;
}

//!@brief set pixel callback
SetPixelCallback_t _set_pixel_callback = NULL;

inline void API_Bind_set_pixel_callback(SetPixelCallback_t callback)
{
    _set_pixel_callback = callback;
}

//!@brief fill screen callback
SetFillScreenCallback_t _fill_screen_callback = NULL;

inline void API_Bind_fill_screen_callback(SetFillScreenCallback_t callback)
{
    _fill_screen_callback = callback;
}

//!@brief get pixel callback
GetPixelCallback_t _get_pixel_callback = NULL;

inline void API_Bind_get_pixel_callback(GetPixelCallback_t callback)
{
    _get_pixel_callback = callback;
}