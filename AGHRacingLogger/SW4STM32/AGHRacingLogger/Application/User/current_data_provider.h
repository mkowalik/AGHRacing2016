#ifndef __current_data_provider_H
#define __current_data_provider_H

#include <stdint.h>

/**
 * Medium (like CAN or RS232) classes saves just arrived data to global structure.
 */
void saveCurrentData(uint8_t channel, uint16_t value);

/**
 * Returns pointer to global table of all-channels data.
 */
volatile uint16_t* getCurrentData();

/**
 * Return actual data value for channel in argument.
 */
volatile uint16_t getCurrentDataForChannel(uint8_t channel);

#endif /* __current_data_provider_H */
