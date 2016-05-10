#include <stdlib.h>
#include <stdint.h>

void ws2812_init();
/**
 * Argument uint8_t value:
 * 0    - LEDs off
 * 1-12 - given number of LEDs turned on with proper color
 * >12  - all LEDs red on
 */
void ws2812_displayRPM(uint8_t value);

/**
 * Argument uint8_t value:
 * 0    - LEDs off
 * 1    - first LED blue
 * 2-6  - given number of LEDs -1 turned on with proper color
 * >6   - all LEDs red on
 */
void ws2812_displayCLT(uint8_t value);

/**
 * Argument uint8_t value:
 * 0    - LEDs off
 * 1-5  - given number of LEDs turned on with proper color
 */
void ws2812_displayFuel(uint8_t value);
