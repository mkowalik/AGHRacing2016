#ifndef __gear_display_H
#define __gear_display_H

#include "mxconstants.h"
#include "stm32f4xx_hal.h"

/**
 * Inits 7-segment display connected by GearDisplay_ChipSelect_GPIO_Port and SPI1 trasceiver.
 */
void gearDisplay_init();

/**
 * Sends data with digit to display by SPI1 to 7-segment gear display.
 */
void gearDisplay_displayDigit(uint8_t digit, uint8_t dot);

/**
 * Switchs off display. Sends 0b00000000 data by SPI1 to 7-segment gear display.
 */
void gearDisplay_offDisplay(uint8_t dot);

#endif //__gear_display_H
