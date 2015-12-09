#include "current_data_provider.h"

uint16_t currentData [MAX_CHANNEL_NUMBER];

void saveCurrentData(uint8_t channel, uint16_t value){
	currentData[channel] = value;
}

uint16_t* getCurrentData(){	//TODO zwrocic to tak, zeby nie dalo sie zmieniac - static
	return currentData;
}
