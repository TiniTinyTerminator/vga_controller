/**
 * @file happy_smiley.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <inttypes.h>

#define HAPPY_SMILEY_WIDTH 24
#define HAPPY_SMILEY_HEIGHT 23

const uint8_t happy_smiley_map[] = {
  /*Pixel format: Blue: 2 bit, Green: 3 bit, Red: 3 bit*/
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0xff, 0xff, 
  0xff, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0xff, 0xff, 0xff, 0x00, 0xfc, 0xfc, 0x00, 0xff, 0xff, 0xff, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0xff, 
  0xff, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0xff, 0x00, 0xff, 0x00, 0xfc, 0xfc, 0x00, 0xff, 0x00, 0xff, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0xff, 
  0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0xff, 0xff, 0xff, 0x00, 0xfc, 0xfc, 0x00, 0xff, 0xff, 0xff, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0xff, 
  0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 
  0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 
  0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 
  0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 
  0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 
  0x00, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0x00, 0xff, 
  0xff, 0x00, 0xfc, 0xfc, 0xfc, 0x00, 0xe5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe5, 0x00, 0xfc, 0xfc, 0xfc, 0x00, 0xff, 
  0xff, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0xe5, 0xe5, 0xe5, 0xe5, 0xe5, 0xe5, 0xe5, 0xe5, 0xe5, 0xe5, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0xff, 
  0xff, 0xff, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0xe5, 0xe5, 0xe5, 0xe5, 0xe5, 0xe5, 0xe5, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0xe5, 0xe5, 0xe5, 0xe5, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
};
