/*
 * can_sensors.h
 *
 *  Created on: 4 sie 2016
 *      Author: kowalik
 */

#ifndef __can_sensors_H_
#define __can_sensors_H_

#include <stdint.h>

#define BYTES_IN_SENSORS_FRAME		2
#define CAN_SENSORS_BUFFER_SIZE		256
/**
 * Inits CAN transceiver.
 */
void canSensors_ReceiveDataFromSensors_init();

/**
 * Starts receiving messages and waits for new message interrupt.
 */
void canSensors_ReceiveDataFromSensors_Start();

/**
 * Main thread function. Saves data from temporary structure to current_data_provider.
 */
void canSensors_saveCurrentData();

#endif /* APPLICATION_USER_CAN_SENSORS_H_ */
