#ifndef __current_data_provider_H
#define __current_data_provider_H

#include <stdint.h>

void saveCurrentData(uint8_t channel, uint16_t value);
volatile uint16_t* getCurrentData();
volatile uint16_t getCurrentDataForChannel(uint8_t channel);

#endif /* __current_data_provider_H */
