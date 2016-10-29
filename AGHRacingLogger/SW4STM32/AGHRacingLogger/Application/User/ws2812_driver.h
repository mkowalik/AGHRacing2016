#ifndef __ws2812_driver_H
#define __ws2812_driver_H

#include <stdlib.h>
#include <stdint.h>

#define 	REFRESH_LEDS_CYCLES_NUMBER	5	//Number of thread cycles when sending data to WS2812 LEDs is omitted when the same as previous cycle

/**
 * Initializes WS2812 LEDs, sends 50us lowstate, and then turns off all LEDs
 */
void ws2812_init();
/**
 * Downloads actual data about RPM, CLT and fuel level (future?) and sends data to proper LED stripes.
 */
void ws2812_displayDrivingWheelLEDs();
/**
 * Downloads actual data about alarms and sends data to alarm LEDs on dashboard.
 */
void ws2812_displayDashboardLEDs();

#endif //__ws2812_driver_H
