#ifndef __dashboard_H
#define __dashboard_H

#include <stdint.h>
#include "logged_data_types.h"

#define DEFAULT_DASHBOARD_FUNCTION_INDEX			0
#define NUMBER_OF_AVAILABLE_DASHBOARD_CHANNELS		7

void dash_displayCurrentData(uint8_t dataChannel);
void dash_init();
uint8_t dash_updateButtonValue();
void dash_displayActualGear();

#endif /* __dashboard_H */
