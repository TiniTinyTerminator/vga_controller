/**
 * @file bitmap.c
 * @author Max Bensink (Max.bensink@student.hu.nl)
 * @brief source file of the @ref API_Load_bitmap function
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

    //calculate the maximum size of the buffer
    uint32_t buf_len = w * h;

    //for the y axis
    for (uint32_t i = 0; i < h; i++)
        //for the x axis
        for (uint32_t j = 0; j < w; j++)
        {
            //if index goes over buffer, return
            if (i * w + j >= buf_len)
                return;
            API_Set_pixel(x_lup + j, y_lup + i, bitmap[i * w + j]);
        }
}

//! the X11 bitmap only works with predefined colors, which has a total of 200 predefined colors. this will make it difficult to use in embedded environments

// typedef struct C
// {
//     uint8_t color;
//     uint8_t character;
// } c_t;

// void API_Load_bitmap_xpm(uint32_t x_lup, uint32_t y_lup, const uint8_t *bitmap)
// {
//     char * str_index = bitmap[0];
//     uint32_t colums = atoi(str_index);
//     str_index = strchr(str_index, ' ');
//     uint32_t rows = atoi(str_index);
//     str_index = strchr(str_index + 1, ' ');
//     uint32_t nColors = atoi(str_index);
//     str_index = strchr(str_index + 1, ' ');
//     uint32_t bytes_per_pixel = atoi(str_index);

//     uint32_t *colors = calloc(nColors, sizeof(c_t));

//     for(uint32_t c = 0; c < nColors; c++)
//         colors[c] = 1;

//     for(uint32_t i = 0; i < rows; i++)
//         for(uint32_t j = 0; j < colums; j++)
//             if(i * colums + j >= (colums * rows)) return;
//             else API_Set_pixel(x_lup + j, y_lup + i, bitmap[i * colums + j]);

// }

// uint8_t string_to_color(const char *str) {

// }
