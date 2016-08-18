/*
 * can_sensors.h
 *
 *  Created on: 4 sie 2016
 *      Author: kowalik
 */

#ifndef CAN_SENSORS_H_
#define CAN_SENSORS_H_

#include <stdint.h>

#define BYTES_IN_SENSORS_FRAME		6
#define CAN_SENSORS_BUFFER_SIZE		256
#define CAN_SENSOR_ID_CHAR_VALUE	0xA3

typedef struct {

	union {
		struct {
			uint8_t channelL;
			uint8_t channelH;
		};
		uint16_t channel;
	};

	uint8_t idChar;

	union {
		struct {
			uint8_t valueL;
			uint8_t valueH;
		};
		uint16_t value;
	};

	uint8_t checksum;
} CanSensorsData;

void canSensors_ReceiveDataFromSensors_init();
void canSensors_ReceiveDataFromSensors_Start();
void canSensors_saveCurrentData();


#endif /* APPLICATION_USER_CAN_SENSORS_H_ */
