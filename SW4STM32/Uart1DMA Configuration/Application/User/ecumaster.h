#ifndef __ecumaster_H
#define __ecumaster_H

#include <stdint.h>

#define ECU_BUFFER_SIZE 32

typedef struct ECUDataStruct {
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

void ecumaster_connection_init();
void checkECUData_thread(void* args);
uint16_t get_ECUDataReceivedIndex();
uint16_t get_ECUDataToSaveIndex();
ECUData* get_receivedECUData();
ECUData* get_toReceiveECUDataPointer();

#endif /* __ECUMASTER_H */
