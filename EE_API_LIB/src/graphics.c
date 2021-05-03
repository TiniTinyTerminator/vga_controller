/**
 * @file shapes.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "graphics.h"
#include <inttypes.h>
#include <stddef.h>
// #include <math.h>

#define sgn(v) (((v) < 0) ? -1 : ((v) > 0))
#define abs(v) (((v) < 0) ? (v * -1) : (v))

extern uint32_t _w;
extern uint32_t _h;

extern SetPixelCallback _set_pixel_callback;
extern SetFillScreenCallback _fill_screen_callback;

inline void API_Set_pixel(int32_t x, int32_t y, uint8_t color)
{
    if (_set_pixel_callback == NULL)
        return;

    _set_pixel_callback(x, y, color);
}

inline void API_Fill_screen(uint8_t color)
{
    if (_fill_screen_callback != NULL)
        _fill_screen_callback(color);
    else
        API_Fill_square(0, 0, _w, _h, color);
}

inline void API_Fill_square(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color)
{
    for (; x < x + w; x++)
        for (; y < y + h; y++)
            API_Set_pixel(x, y, color);
}

void API_Draw_line(int32_t xA, int32_t yA, int32_t xB, int32_t yB, uint8_t color)
{
    int dx = abs(xB - xA);
    int sx = xA < xB ? 1 : -1;

    int dy = -abs(yB - yA);
    int sy = yA < yB ? 1 : -1;

    int err = dx + dy, e2; /* error value e_xy */

    if (dx == 0)
        for (uint32_t y = (sy ? yA : yB); y < (sy ? yB : yA); y++)
        {
            API_Set_pixel(xA, y, color);
        }

    else if (dy == 0)
        for (uint32_t x = (sx ? xA : xB); x < (sx ? xB : xA); x++)
        {
            API_Set_pixel(x, yA, color);
        }
    else
        while (xA != xB && yA != yB)
        { /* loop */
            API_Set_pixel(xA, yA, color);

            e2 = 2 * err;
            if (e2 >= dy)
            {
                err += dy;
                xA += sx;
            } /* e_xy+e_x > 0 */
            if (e2 <= dx)
            {
                err += dx;
                yA += sy;
            } /* e_xy+e_y < 0 */
        }
}

void API_Draw_circle(int32_t xm, int32_t ym, uint32_t radius, uint8_t color)
{
    int x = -radius, y = 0, err = 2 - 2 * radius; /* II. Quadrant */
    do
    {
        API_Set_pixel(xm - x, ym + y, color); /*   I. Quadrant */
        API_Set_pixel(xm - y, ym - x, color); /*  II. Quadrant */
        API_Set_pixel(xm + x, ym - y, color); /* III. Quadrant */
        API_Set_pixel(xm + y, ym + x, color); /*  IV. Quadrant */
        radius = err;
        if (radius <= y)
            err += ++y * 2 + 1; /* e_xy+e_y < 0 */
        if (radius > x || err > y)
            err += ++x * 2 + 1; /* e_xy+e_x > 0 or no 2nd y-step */
    } while (x < 0);
}

void API_Fill_circle(uint32_t xm, uint32_t ym, uint32_t r, uint8_t color)
{
    for (int ra = r; ra > 0; ra--)
        API_Draw_circle(xm, ym, ra, color);
}

void API_Draw_square(int32_t x, int32_t y, uint32_t width, uint32_t height, uint8_t color)
{
    API_Draw_line(x, y, x + width, y, color);
    API_Draw_line(x, y, x, y + height, color);
    API_Draw_line(x + width, y, x + width, y + height + 1, color);
    API_Draw_line(x, y + height, x + width, y + height, color);
}

void plotEllipseRect(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint8_t color)
{
    uint32_t a = abs(x1 - x0), b = abs(y1 - y0), b1 = b & 1;     /* values of diameter */
    int32_t dx = 4 * (1 - a) * b * b, dy = 4 * (b1 + 1) * a * a; /* error increment */
    int32_t err = dx + dy + b1 * a * a, e2;                      /* error of 1.step */

    if (x0 > x1)
    {
        x0 = x1;
        x1 += a;
    } /* if called with swapped points */
    if (y0 > y1)
        y0 = y1; /* .. exchange them */
    y0 += (b + 1) / 2;
    y1 = y0 - b1; /* starting pixel */
    a *= 8 * a;
    b1 = 8 * b * b;

    do
    {
        API_Set_pixel(x1, y0, color); /*   I. Quadrant */
        API_Set_pixel(x0, y0, color); /*  II. Quadrant */
        API_Set_pixel(x0, y1, color); /* III. Quadrant */
        API_Set_pixel(x1, y1, color); /*  IV. Quadrant */
        e2 = 2 * err;
        if (e2 <= dy)
        {
            y0++;
            y1--;
            err += dy += a;
        } /* y step */
        if (e2 >= dx || 2 * err > dy)
        {
            x0++;
            x1--;
            err += dx += b1;
        } /* x step */
    } while (x0 <= x1);

    while (y0 - y1 < b)
    {                                     /* too early stop of flat ellipses a=1 */
        API_Set_pixel(x0 - 1, y0, color); /* -> finish tip of ellipse */
        API_Set_pixel(x1 + 1, y0++, color);
        API_Set_pixel(x0 - 1, y1, color);
        API_Set_pixel(x1 + 1, y1--, color);
    }
}

void API_Draw_polygon(const int32_t *list_X, const int32_t *list_Y, uint32_t length, uint8_t color)
{
    API_Draw_line(list_X[0], list_Y[0], list_X[length - 1], list_Y[length - 1], color);

    for (uint32_t i = 0; i < length - 1; i++)
        API_Draw_line(list_X[i], list_Y[i], list_X[i + 1], list_Y[i + 1], color);
}