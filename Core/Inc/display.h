/**
 * @file display.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <gpio.h>

enum res {
    V240H320 = 0,
    V320H480,
    V480H720,
};

void init_display(void)

void set_resolution(enum res = V240H320);

void 