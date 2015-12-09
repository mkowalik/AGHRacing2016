#ifndef __current_data_provider_H
#define __current_data_provider_H

#include <stdint.h>

#define MAX_CHANNEL_NUMBER 256

void saveCurrentData(uint8_t channel, uint16_t value);
volatile uint16_t* getCurrentData();

#endif /* __current_data_provider_H */
