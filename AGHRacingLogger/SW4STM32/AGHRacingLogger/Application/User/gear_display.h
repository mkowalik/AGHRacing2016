#ifndef __gear_display_H
#define __gear_display_H

#include "mxconstants.h"
#include "stm32f4xx_hal.h"

void gearDisplay_init();
void gearDisplay_displayDigit(uint8_t digit, uint8_t dot);

#endif //__gear_display_H
