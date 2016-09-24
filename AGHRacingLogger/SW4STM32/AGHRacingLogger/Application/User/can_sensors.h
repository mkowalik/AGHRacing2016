/*
 * can_sensors.h
 *
 *  Created on: 4 sie 2016
 *      Author: kowalik
 */

#ifndef CAN_SENSORS_H_
#define CAN_SENSORS_H_

#include <stdint.h>

#define BYTES_IN_SENSORS_FRAME		2
#define CAN_SENSORS_BUFFER_SIZE		256

void canSensors_ReceiveDataFromSensors_init();
void canSensors_ReceiveDataFromSensors_Start();
void canSensors_saveCurrentData();

typedef struct {
	uint32_t channelId;
	union {
		struct {
			uint8_t valueL;
			uint8_t valueH;
		};
		uint16_t value;
	};
} CanSensorsData;


#endif /* APPLICATION_USER_CAN_SENSORS_H_ */
