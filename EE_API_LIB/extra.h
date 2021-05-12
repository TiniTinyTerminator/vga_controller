/**
 * @file extra.h
 * @author Max Bensink (Max.bensink@student.hu.nl)
 * @brief some extra functions that were fun to make
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/**
 * @brief calculate the mandelbrot and visualize it on the display
 * 
 * @param max_iterations the maximum amount of iterations per pixel
 * @param real_min minimum real number (x-axis)
 * @param real_max maximum real number (x-axis)
 * @param imag_min minimum imaginary number (y-axis)
 * @param imag_max maximum imaginary number (y-axis)
 */
void API_mandelbrot(int max_iterations, double real_min, double real_max, double imag_min, double imag_max);