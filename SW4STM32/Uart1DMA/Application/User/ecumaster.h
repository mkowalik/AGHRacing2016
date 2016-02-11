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

#define BYTES_IN_ECU_FRAME 	5
#define ECU_BUFFER_SIZE 	(256 * BYTES_IN_ECU_FRAME)
#define ID_CHAR_VALUE		0xA3

void ECU_receivedByteNotification();
volatile uint16_t ECU_getBytesRightIndex();
volatile uint16_t ECU_getBytesLeftIndex();
volatile uint8_t* ECU_getReceivedBytesTab();
volatile uint8_t* ECU_getNextReceivedBytePointer();
void ECU_saveCurrentData(void const * args);

#endif /* __ECUMASTER_H */