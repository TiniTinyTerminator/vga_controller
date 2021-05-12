/**
 * @file extra.c
 * @author Max Bensink (Max.bensink@student.hu.nl)
 * @brief 
 * @version 0.1
 * @date 2021-05-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "graphics.h"

extern uint32_t _w;
extern uint32_t _h;
typedef struct
{
  double x, y;
} Complex;

Complex complexSquare(Complex c);

inline Complex complexSquare(Complex c)
{
  Complex cSq;
  cSq.x = c.x * c.x - c.y * c.y;
  cSq.y = 2 * c.x * c.y;
  return cSq;
}

int mandel_iterate(Complex zInit, int maxIter)
{
  Complex z = zInit;
  int cnt = 0;
  while ((z.x * z.x + z.y * z.y <= 4) && (cnt < maxIter))
  {
    z = complexSquare(z);
    z.x += zInit.x;
    z.y += zInit.y;
    cnt++;
  }
  return cnt;
}

void API_mandelbrot(int maxIter, float realMin, float realMax, float imagMin, float imagMax)
{
  float realInc = (realMax - realMin) / _w;
  float imagInc = (imagMax - imagMin) / _h;
  static uint8_t color = 0x00;

  Complex z;
  int x, y;
  int cnt;
  for (x = 0, z.x = realMin; x < _w; x++, z.x += realInc)
    for (y = 0, z.y = imagMin; y < _h; y++, z.y += imagInc)
    {
      cnt = mandel_iterate(z, maxIter);
      if (cnt == maxIter)
        color = 0x00;
      else
      {
        color = (uint8_t)cnt;
      }
      API_Set_pixel(x, y, color);
    }
}
