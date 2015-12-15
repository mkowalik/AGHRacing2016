#ifndef __ecumaster_H
#define __ecumaster_H

#include <stdint.h>

typedef struct {
	uint8_t channel;
	uint8_t idChar;
	union {
		struct {
			uint8_t valueH;
			uint8_t valueL;
		};
		uint16_t value;
	};
	uint8_t checksum;
} ECUData;

#define BYTES_IN_ECU_FRAME 	5
#define ECU_BUFFER_SIZE 	(32 * BYTES_IN_ECU_FRAME)
#define ID_CHAR_VALUE		0xA3

void receivedDataByteNotification();
volatile uint16_t get_ECUDataReceivedIndex();
volatile uint16_t get_ECUDataToSaveIndex();
volatile uint8_t* get_receivedECUDataTab();
volatile uint8_t* get_toReceiveECUDataPointer();
void checkECUData_thread(void* args);

#endif /* __ECUMASTER_H */
