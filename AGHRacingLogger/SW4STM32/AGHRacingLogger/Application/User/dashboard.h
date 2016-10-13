#ifndef __dashboard_H
#define __dashboard_H

#include <stdint.h>
#include "logged_data_types.h"

#define DEFAULT_DASHBOARD_FUNCTION_INDEX			0
#define NUMBER_OF_AVAILABLE_DASHBOARD_CHANNELS		7

void dash_displayCurrentData();
void dash_init();
void dash_displayActualGear();
void dash_nextDisplayingValueChannelIndexNotification();

#endif /* __dashboard_H */
