#include "current_data_provider.h"
#include "logged_data_types.h"
#include "error_logger.h"

volatile uint16_t currentData [CHANNEL_NUMBER];

void saveCurrentData(uint8_t channel, uint16_t value){
	currentData[channel] = value;
}

volatile uint16_t* getCurrentData(){	//TODO zwrocic to tak, zeby nie dalo sie zmieniac - static
	return currentData;
}

volatile uint32_t getCurrentDataForChannel(uint8_t channel){
	return currentData[channel];
}
