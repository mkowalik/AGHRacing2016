#ifndef __ecumaster_H
#define __ecumaster_H

#include <stdint.h>

typedef struct {
	uint8_t channel;
	uint8_t idChar;
	union {
		struct {
			uint8_t valueL;
			uint8_t valueH;
		};
		uint16_t value;
	};
	uint8_t checksum;
} ECUData;

#define ECU_BYTES_IN_FRAME 	5
#define ECU_BUFFER_SIZE 	(256 * ECU_BYTES_IN_FRAME)
#define ECU_ID_CHAR_VALUE		0xA3

void ECU_init();
void ECU_receiveData();
void ECU_receivedByteNotification();
volatile uint16_t ECU_getBytesRightIndex();
volatile uint16_t ECU_getBytesLeftIndex();
volatile uint8_t* ECU_getReceivedBytesTab();
volatile uint8_t* ECU_getNextReceivedBytePointer();
void ECU_saveCurrentData(void const * args);

#endif /* __ECUMASTER_H */
