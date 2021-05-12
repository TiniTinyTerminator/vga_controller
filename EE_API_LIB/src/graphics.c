/**
 * @file shapes.c
 * @author Max Bensink (Max.bensink@student.hu.nl)
 * @brief 
 * @date 2021-04-27
 * 
 * @copyright Copyright (c) 2021
 */

#include "graphics.h"
#include <inttypes.h>
#include <stddef.h>

#define sgn(v) (((v) < 0) ? -1 : ((v) > 0))
#define abs(v) (((v) < 0) ? (v * -1) : (v))

extern uint32_t _w;
extern uint32_t _h;

extern SetPixelCallback_t _set_pixel_callback;
extern SetFillScreenCallback_t _fill_screen_callback;
extern GetPixelCallback_t _get_pixel_callback;

inline void API_Set_pixel(int32_t x, int32_t y, uint8_t color)
{
    if (_set_pixel_callback == NULL)
        return;

    _set_pixel_callback(x, y, color);
}

inline uint8_t API_Get_pixel(int32_t x, int32_t y)
{
    if (_get_pixel_callback == NULL)
        return 0x0;

    return _get_pixel_callback(x, y);
}

inline void API_Fill_screen(uint8_t color)
{
    if (_fill_screen_callback != NULL)
        _fill_screen_callback(color);
    else
        API_Fill_square(0, 0, _w, _h, color);
}

inline void API_Draw(int32_t x, int32_t y, uint8_t color, uint32_t size, DrawStyle_t draw_type)
{
    switch (draw_type)
    {
    case DOT:
        API_Set_pixel(x, y, color);
        break;
    case SQUARE:
        API_Fill_square(x - (size / 2), y - (size / 2), size - 1, size - 1, color);
        break;
    default:
        API_Fill_circle(x, y, size, color);
        break;
    }
}

inline void API_Fill_square(uint32_t x_lup, uint32_t y_lup, uint32_t w, uint32_t h, uint32_t color)
{
    for (uint32_t x = x_lup; x <= (x_lup + w); x++)
        for (uint32_t y = y_lup; y <= (y_lup + h); y++)
            API_Set_pixel(x, y, color);
}

void API_Draw_line(int32_t xA, int32_t yA, int32_t xB, int32_t yB, uint8_t color, uint32_t thickness, DrawStyle_t draw_style)
{
    int32_t dx = abs(xB - xA), sx = xA < xB ? 1 : -1;

    int32_t dy = -abs(yB - yA), sy = yA < yB ? 1 : -1;

    int32_t error = dx + dy, e2; /* error value e_xy */

    for (;;)
    { /* loop */
        API_Draw(xA, yA, color, thickness, draw_style);
        e2 = 2 * error;
        if (e2 >= dy)
        { /* e_xy+e_x > 0 */
            if (xA == xB)
                break;
            error += dy;
            xA += sx;
        }
        if (e2 <= dx)
        { /* e_xy+e_y < 0 */
            if (yA == yB)
                break;
            error += dx;
            yA += sy;
        }
    }
}

void API_Draw_circle(int32_t xm, int32_t ym, int32_t radius, uint8_t color, uint32_t thickness)
{
    int32_t x = -radius, y = 0, err = 2 - 2 * radius; /* bottom left to top right */
    do
    {

        API_Draw(xm - x, ym + y, color, thickness, ROUND); /* I. Quadrant +x +y */
        API_Draw(xm - y, ym - x, color, thickness, ROUND); /* II. Quadrant -x +y */
        API_Draw(xm + x, ym - y, color, thickness, ROUND); /* III. Quadrant -x -y */
        API_Draw(xm + y, ym + x, color, thickness, ROUND); /* IV. Quadrant +x -y */

        radius = err;

        if (radius <= y)
            err += ++y * 2 + 1;    /* e_xy+e_y < 0 */

        if (radius > x || err > y) /* e_xy+e_x > 0 or no 2nd y-step */
            err += ++x * 2 + 1;    /* -> x-step now */
            
    } while (x < 0);
}

void API_Fill_circle(int32_t xm, int32_t ym, int32_t radius, uint8_t color)
{
    int32_t x = -radius, y = 0, err = 2 - 2 * radius; /* bottom left to top right */
    do
    {
        API_Draw_line(xm + x, ym - y, xm - x, ym - y, color, 1, DOT);
        API_Draw_line(xm + x, ym + y, xm - x, ym + y, color, 1, DOT);

        radius = err;
        
        if (radius <= y)
            err += ++y * 2 + 1;    /* e_xy+e_y < 0 */

        if (radius > x || err > y) /* e_xy+e_x > 0 or no 2nd y-step */
            err += ++x * 2 + 1;    /* -> x-step now */

    } while (x < 0);
}

void API_Draw_square(int32_t x, int32_t y, uint32_t width, uint32_t height, uint8_t color, uint32_t thickness)
{
    API_Draw_line(x, y, x + width, y, color, thickness, SQUARE);
    API_Draw_line(x, y, x, y + height, color, thickness, SQUARE);
    API_Draw_line(x + width, y, x + width, y + height, color, thickness, SQUARE);
    API_Draw_line(x, y + height, x + width, y + height, color, thickness, SQUARE);
}

void API_Draw_polygon(const int32_t *list_X, const int32_t *list_Y, uint32_t length, uint8_t color, uint32_t thickness, DrawStyle_t draw_style)
{
    API_Draw_line(list_X[0], list_Y[0], list_X[length - 1], list_Y[length - 1], color, thickness, draw_style);

    // API_Draw_line(list_X[3], list_X[3], list_X[2], list_X[2], color, thickness, draw_style);

    for (int32_t i = 0; i < (length - 1); i++)
        API_Draw_line(list_X[i], list_Y[i], list_X[i + 1], list_Y[i + 1], color, thickness, draw_style);
}
