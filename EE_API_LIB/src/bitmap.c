/**
 * @file bitmap.c
 * @author your name (you@domain.com)
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


// typedef struct ColorCodes
// {
//     uint8_t * colorName;
//     uint8_t color;
//     /* data */
// } ColorCodes_t;

// static const ColorCodes_t color_codes[] =
// {
//     {"black", 0x00},
//     {"white", 0xFF},
//     {"cyan", 0x},
//     {"blue"},
//     {"green"},
//     {"orange"},
//     {"red"},
//     {"purple"}
// };


void API_Load_bitmap(uint32_t x_lup, uint32_t y_lup, uint32_t w, uint32_t h, const uint8_t *bitmap)
{
    uint32_t buf_len = w * h;

    for(uint32_t i = 0; i < h; i++)
        for(uint32_t j = 0; j < w; j++)
            if(i * w + j >= buf_len) return;
            else API_Set_pixel(x_lup + j, y_lup + i, bitmap[i * w + j]);
}

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