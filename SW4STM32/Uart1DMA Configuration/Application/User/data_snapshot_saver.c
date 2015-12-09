#include "data_snapshot_saver.h"
#include "current_data_provider.h"
#include "usart.h"
#include "logged_data_types.h"
#include <string.h>

uint16_t savedSnapshots[MAX_CHANNEL_NUMBER][MAX_SNAPSHOT_NUMBER];

void saveActualData_thread(void* args){

	const uint16_t size = 3;
	uint8_t parameters[] = {ECU_RPM, ECU_TPS, ECU_BATT};
	char* labels[] = {"RPM: ", "TPS: ", "BATT:"};
	uint16_t* currentData = getCurrentData();
	int i;
	for (i=0; i<size; i++) {
		HAL_UART_TransmitData((uint8_t*)labels[i], strlen(labels[i]));

		char valueString[10];
		sprintf(valueString, "%d\n", currentData[parameters[i]]);
		HAL_UART_TransmitData((uint8_t*)valueString, strlen(valueString));
	}

}
