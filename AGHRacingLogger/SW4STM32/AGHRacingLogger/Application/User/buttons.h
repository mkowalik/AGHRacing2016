#ifndef __buttons_H
#define __buttons_H

#include <stdlib.h>
#include <stdint.h>

/**
 * Returns true if there is pushed button for longer than 50 ticks.
 */
uint8_t buttons_updateButtonValue();

#endif //__buttons_H
