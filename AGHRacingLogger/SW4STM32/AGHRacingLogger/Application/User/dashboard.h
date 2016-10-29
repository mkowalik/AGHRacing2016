#ifndef __dashboard_H
#define __dashboard_H

#include <stdint.h>
#include "logged_data_types.h"

#define DEFAULT_DASHBOARD_FUNCTION_INDEX			0
#define NUMBER_OF_AVAILABLE_DASHBOARD_CHANNELS		7


/**
 * This function prepares data from sensors and sends proper data to ssd1306 driver for display proper value.
 */
void dash_displayCurrentData();

/**
 * Runs unit functions of OLED SSD1306 display and 7-segment gear display.
 */
void dash_init();

/**
 * Get actual data from gear sensor and neutral sensor and runs gearDisplay_displayDigit function and displays proper digit.
 */
void dash_displayActualGear();

/**
 * Running this function gives information to change displaying data on OLED display for next sensor.
 */
void dash_nextDisplayingValueChannelIndexNotification();

#endif /* __dashboard_H */
