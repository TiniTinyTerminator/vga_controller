/**
 * @file configuration.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "EE_API_LIB/shapes.h"

#include <stdio.h>

static uint32_t _w;

static uint32_t _h;

static uint8_t _filled = 0x0;

static uint32_t _line_thickness = 0x1;

static uint8_t _fill_color = 0xFF;

static uint8_t _draw_color = 0xFF;

static DrawPixelCallback _callback = NULL;
