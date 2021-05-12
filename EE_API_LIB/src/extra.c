/**
 * @file extra.c
 * @author Max Bensink (Max.bensink@student.hu.nl)
 * @brief the source file of the @ref extra.h file
 * @version 0.1
 * @date 2021-05-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "graphics.h"

extern uint32_t _w;
extern uint32_t _h;

/**
 * @brief complex struct to hold real and imaginary numbers
 * 
 */
typedef struct Complex
{
  double real, imag;
} Complex_t;

/**
 * @brief apply a square function on the complex number 
 * 
 * @param c the complex number
 * @return Complex_t the squared number
 */
inline Complex_t Complex_square(Complex_t c)
{
  return (Complex_t){c.real * c.real - c.imag * c.imag, 2 * c.real * c.imag};
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

  while ((z.real * z.real + z.imag * z.imag <= 4) && (cnt < max_iterations))
  {
    z = Complex_square(z);
    z.real += z_initial.real;
    z.imag += z_initial.imag;
    cnt++;
  }
  return cnt;
}

void API_mandelbrot(int max_iterations, double real_min, double real_max, double imag_min, double imag_max)
{
  //!@brief calculate the distance between each pixel on the x and y axis
  float real_inc = (real_max - real_min) / _w;
  float imag_inc = (imag_max - imag_min) / _h;

  static uint8_t color = 0x00;

  Complex_t z;

  int32_t x, y;
  
  //for each x position
  for (x = 0, z.real = real_min; x < _w; x++, z.real += real_inc)
    //for each y position
    for (y = 0, z.imag = imag_min; y < _h; y++, z.imag += imag_inc)
    {
      //iterate till the maximume iteration has been reached
      uint32_t cnt = mandel_iterate(z, max_iterations);
      if (cnt == max_iterations)
      //set color to black if maximum iterations has been reached
        color = 0x00;
      else
      {
      //set color dependig on the interations
        color = (uint8_t)cnt;
      }
      //draw that pixel
      API_Set_pixel(x, y, color);
    }
}
