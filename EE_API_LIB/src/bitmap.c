/**
 * @file bitmap.c
 * @author Max Bensink (Max.bensink@student.hu.nl)
 * @brief 
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "graphics.h"
#include "stdlib.h"
#include "string.h"

void API_Load_bitmap(uint32_t x_lup, uint32_t y_lup, uint32_t w, uint32_t h, const uint8_t *bitmap)
{
    uint32_t buf_len = w * h;

    for(uint32_t i = 0; i < h; i++)
        for(uint32_t j = 0; j < w; j++)
            if(i * w + j >= buf_len) return;
            else API_Set_pixel(x_lup + j, y_lup + i, bitmap[i * w + j]);
}
