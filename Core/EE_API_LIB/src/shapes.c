/**
 * @file circle.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "shapes.h"
#include <stdio.h>
#include <math.h>
 
#define sgn(v) ( ( (v) < 0 ) ? -1 : ( (v) > 0 ) )
#define abs(v) ( ( (v) < 0)  ? (v * -1) : (v))

extern uint32_t _w;
extern uint32_t _h;
extern uint8_t _filled;
extern uint32_t _line_thickness;
extern uint8_t _fill_color;
extern uint8_t _draw_color;

extern SetPixelCallback _set_pixel_callback;
extern SetFillScreenCallback _fill_screen_callback;

inline void API_Set_pixel(const Pvector_t pos, uint8_t color)
{
    _set_pixel_callback(pos->x, pos->y, color);
}

inline void API_fill_screen(uint8_t color)
{
    if(_fill_screen_callback != NULL)
        _fill_screen_callback(color);
    else
    {
        vector_t pos = {};
        for(pos.x = 0; pos.x < _w; pos.x++)
            for(pos.y = 0; pos.y < _h; pos.y ++)
                API_Set_pixel(&pos, color);
    }
}

void API_Draw_vector(const Pvector_t start, const Pvector_t end)
{
    // float a = (float)(end->y - start->y) / (float)(end->x - start->x);
    // // float b = (float)(start->y) - a * (float)(start->x);

    // for(vector_t pos = *start; pos.x <= end->x; pos.y = (uint32_t)((float)pos.x++ * a) + start->y)
    // {
    //     API_Set_pixel(&pos, _draw_color);
    // }

    const int32_t dx = end->x - start->x;
    const int32_t dy = end->y - start->y;

    const int32_t derr = abs(dy / dx);

    vector_t pos = {};
    pos.y = start->x < end->x ? start->y : end->y;
    pos.x = (start->x < end->x) ? start->x : end->x;
    if(derr == NAN) //line is vertical
    {
        for(pos.y = )
    }
    else
    {
        float err = 0;
        for(; pos.x < (start->x > end->x) ? start->x : end->x; pos.x++)
        {
            
            API_Set_pixel(&pos, _draw_color);

            err = derr + err;

            if(err >= 0.5)
            {
                pos.y = pos.y + sgn(err);
                err = err - 1.0;
            }
        
        }
    }
}

void API_Draw_circle(const Pvector_t position, uint32_t radius)
{

    // if(!API_Check_inbounds(position, radius, radius))
    //     return;

    // vector_t pos = {0, 0};

    // if(_filled)
    // for(uint32_t x = position->x - radius / 2; x <= position->x + radius / 2; x++)
    // {
    //     pos.x = x;

    //     uint32_t low_y = (uint32_t)sqrt(radius-(x * x)) + position->y;
    //     uint32_t high_y = -(uint32_t)sqrt(radius-(x * x)) + position->y;

    //     for(uint32_t y = low_y; y <= high_y; y++)
    //     {
    //         pos.y = y;

    //         API_Set_pixel(&pos, _fill_color);
    //     }
    // }

    // uint32_t min_radius = (radius - _line_thickness / 2);
    // uint32_t max_radius = (radius + _line_thickness / 2);

    // for(uint32_t _radius = min_radius; _radius < max_radius; _radius++) {

    //     uint32_t min_x = position->x - _radius/2;
    //     uint32_t max_x = position->x + _radius/2;

    //     for(int32_t x = min_x; x <= max_x; x++) {
    //         pos.x = x;
    //         pos.y = (uint32_t)sqrt(radius - pow(x - sqrt(radius), 2)) + position->y;
    //         API_Set_pixel(&pos, _draw_color);
    //         pos.y = -(uint32_t)sqrt(radius - pow(x - sqrt(radius), 2)) + position->y;
    //         API_Set_pixel(&pos, _draw_color);
    //     }
    // }
}

void API_Draw_square(const Pvector_t start, uint32_t width, uint32_t height)
{
    vector_t pos;
    for (pos = *start; pos.x < width; pos.x++)
        API_Set_pixel(&pos, _draw_color);
    for (pos.y += height - 1; pos.x > start->x; pos.x--)
        API_Set_pixel(&pos, _draw_color);
    // for (pos; pos.y <= height; pos.y++)
    //     API_Set_pixel(&pos, _draw_color);
    // for (pos.x += width; pos.y >= start->y; pos.y--)
    //     API_Set_pixel(&pos, _draw_color);
    // for (pos.y += height; pos.x >= start->x; pos.x--)
    //     API_Set_pixel(&pos, _draw_color);
}
