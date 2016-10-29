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

#define ECU_BYTES_IN_FRAME 	5							// Number of bytes in frame received by RS232 from ECU
#define ECU_BUFFER_SIZE 	(256 * ECU_BYTES_IN_FRAME)	// Buffer size in bytes for data received from ECU
#define ECU_ID_CHAR_VALUE		0xA3					// Pre-defined ID_CHAR received in data frame from ECU.

/**
 * Initializes UART1 trasceiver and receives data until occours any frame error.
 */
void ECU_init();

/**
 * Starts DMA for receiving data. Turns on RXNE (receive buffer not empty) interrupt.
 */
void ECU_receiveData();

/**
 * This function is called in IRQ_Handler when byte of data is received and saved to receivedECUBytes by DMA.
 */
void ECU_receivedByteNotification();

/**
 * Returns index to first empty cell in tab (!!! not mod-divided by ECU_BUFFER_SIZE). Just after with newest byte of data from ECU.
 */
volatile uint16_t ECU_getBytesRightIndex();

/**
 * Returns index to tab (!!! not mod-divided by ECU_BUFFER_SIZE) with oldest byte of data from ECU.
 */
volatile uint16_t ECU_getBytesLeftIndex();

/**
 * Returns pointer to receivedECUBytes tab - buffer for bytes received from ECU.
 */
volatile uint8_t* ECU_getReceivedBytesTab();

/**
 * Receives pointer to first empty cell of receivedECUBytes tab. Just after with newest byte of data from ECU.
 */
volatile uint8_t* ECU_getNextReceivedBytePointer();

/**
 * Main thread used in freertos for saving and processing data from receivedECUBytes to current_data_provider.
 */
void ECU_saveCurrentData(void const * args);

#endif /* __ECUMASTER_H */
