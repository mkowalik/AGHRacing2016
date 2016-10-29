#ifndef __delay_timer6_H
#define __delay_timer6_H

#include <stdint.h>
#include "stm32f4xx_hal.h"

/**
 * Simple busy-waiting delay in microseconds using timer6.
 */
void DelayMicroseconds(uint16_t timeArg);

#endif //__delay_timer6_H
