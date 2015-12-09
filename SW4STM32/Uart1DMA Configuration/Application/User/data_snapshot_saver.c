#include "data_snapshot_saver.h"
#include "current_data_provider.h"
#include "usart.h"
#include "logged_data_types.h"
#include <string.h>

uint16_t savedSnapshots[MAX_CHANNEL_NUMBER][MAX_SNAPSHOT_NUMBER];

void saveActualData_thread(void* args){

	const uint16_t size = 3;
	volatile uint8_t parameters[] = {ECU_RPM, ECU_TPS, ECU_BATT};
	volatile char* labels[] = {"RPM: ", "TPS: ", "BATT:"};
	volatile uint16_t* currentData = getCurrentData();
	int i;
	for (i=0; i<size; i++) {
		UART2_TransmitData((volatile uint8_t*)labels[i], strlen((char*)labels[i]));

		char valueString[10];
		sprintf(valueString, "%d ", currentData[parameters[i]]);
		UART2_TransmitData((volatile uint8_t*)valueString, strlen(valueString));
	}
	UART2_TransmitData((uint8_t*)"\r\n", strlen("\r\n"));

}
