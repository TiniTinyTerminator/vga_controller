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
} Complex_t;

/**
 * @brief apply a square function on the complex number 
 * 
 * @param c the complex number
 * @return Complex_t the squared number
 */
inline Complex_t Complex_square(Complex_t c)
{  
  return (Complex_t){c.x * c.x - c.y * c.y, 2 * c.x * c.y};
}

/**
 * @brief calculate the position in the mandelbrot till the 
 * 
 * @param z_initial 
 * @param max_iterations 
 * @return int 
 */
int mandel_iterate(Complex_t z_initial, uint32_t max_iterations)
{
  Complex_t z = z_initial;


  uint32_t cnt = 0;
  
  while ((z.x * z.x + z.y * z.y <= 4) && (cnt < max_iterations))
  {
    z = Complex_square(z);
    z.x += z_initial.x;
    z.y += z_initial.y;
    cnt++;
  }
  return cnt;
}

void API_mandelbrot(int max_iterations, double real_min, double real_max, double imag_min, double imag_max)
{
  float real_inc = (real_max - real_min) / _w;
  float imag_inc = (imag_max - imag_min) / _h;

  static uint8_t color = 0x00;

  Complex_t z;

  int32_t x, y;
  
  for (x = 0, z.x = real_min; x < _w; x++, z.x += real_inc)
    for (y = 0, z.y = imag_min; y < _h; y++, z.y += imag_inc)
    {
      uint32_t cnt = mandel_iterate(z, max_iterations);
      if (cnt == max_iterations)
        color = 0x00;
      else
      {
        color = (uint8_t)cnt;
      }
      API_Set_pixel(x, y, color);
    }
}
