#ifndef __ws2812_driver_H
#define __ws2812_driver_H

#include <stdlib.h>
#include <stdint.h>

#define 	REFRESH_LEDS_CYCLES_NUMBER	5	//Number of thread cycles when sending data to WS2812 LEDs is omitted when the same as previous cycle

void ws2812_init();
void ws2812_displayDrivingWheelLEDs();
void ws2812_displayDashboardLEDs();

#endif //__ws2812_driver_H
