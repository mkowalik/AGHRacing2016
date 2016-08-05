/*
 * can_sensors.c
 *
 *  Created on: 4 sie 2016
 *      Author: kowalik
 */

#include "can_sensors.h"
#include "stm32f4xx_hal.h"
#include "logged_data_types.h"
#include "cmsis_os.h"
#include "error_logger.h"
#include "current_data_provider.h"

static volatile CanSensorsData receivedSensorsData[CAN_SENSORS_BUFFER_SIZE];

static CAN_HandleTypeDef* hcan_ptr;
static volatile uint16_t canSensorsDataLeftIndex = 0;
static volatile uint16_t canSensorsDataRightIndex = 0;

#define CAN_SENSOR_CHANNEL_NEUTRAL	256
#define CAN_SENSOR_CHANNEL_GEAR		257

extern osMutexId currentDataMutexHandle;

void canSensors_ReceiveDataFromSensors_init(CAN_HandleTypeDef* hcan_ptr_arg){

	hcan_ptr = hcan_ptr_arg;

	HAL_StatusTypeDef status;

	do {
		status = HAL_CAN_Receive(hcan_ptr, CAN_FIFO0, 50);
		HAL_CAN_IRQHandler(hcan_ptr);
	} while ((status!=HAL_OK && status!=HAL_TIMEOUT) || (hcan_ptr->ErrorCode != HAL_CAN_ERROR_NONE));

}

void canSensors_ReceiveDataFromSensors_Start(){

	HAL_CAN_Receive_IT(hcan_ptr, CAN_FIFO0);

}

void canSensors_saveCurrentData(){

	while (canSensorsDataLeftIndex <canSensorsDataRightIndex){

		CanSensorsData actCanSensorData = receivedSensorsData[canSensorsDataLeftIndex];

		uint8_t checksum = ((uint16_t)actCanSensorData.channelH + actCanSensorData.channelL + actCanSensorData.idChar + actCanSensorData.valueH + actCanSensorData.valueL) % 256;

		if ((actCanSensorData.idChar != CAN_SENSOR_ID_CHAR_VALUE) || (actCanSensorData.checksum!= checksum)){
			canSensorsDataLeftIndex++;
			continue;
		}

		uint8_t loggedDataChannel = 0;

		switch (actCanSensorData.channel){
			case CAN_SENSOR_CHANNEL_NEUTRAL:
				loggedDataChannel = SENSOR_NEUTRAL;
				break;
			case CAN_SENSOR_CHANNEL_GEAR:
				loggedDataChannel = SENSOR_GEAR;
				break;
			default:
				canSensorsDataLeftIndex++;
				return;
		}


		/** Take mutex for current data **/
		if (osMutexWait(currentDataMutexHandle, 10)!=osOK){
			LOG_warning("Error (timeout probably) while waiting for mutex for current data in data_snapshot_maker.");
			return;
		}

		saveCurrentData(loggedDataChannel, actCanSensorData.value);

		/** Release mutex for current data **/
		if (osMutexRelease(currentDataMutexHandle)!=osOK){
			LOG_warning("Error while releasing mutex for current data in data_snapshot_maker.");
		}

		canSensorsDataLeftIndex++;

		if (canSensorsDataLeftIndex>CAN_SENSORS_BUFFER_SIZE){
			canSensorsDataLeftIndex-=CAN_SENSORS_BUFFER_SIZE;
			canSensorsDataRightIndex-=CAN_SENSORS_BUFFER_SIZE;
		}

	}

}

void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan){

	CanRxMsgTypeDef* msg = hcan->pRxMsg;

	if ((msg->RTR == CAN_RTR_DATA) && (msg->DLC != BYTES_IN_SENSORS_FRAME)){

		receivedSensorsData[canSensorsDataRightIndex].channelH = msg->Data[0];
		receivedSensorsData[canSensorsDataRightIndex].channelL = msg->Data[1];
		receivedSensorsData[canSensorsDataRightIndex].idChar = msg->Data[2];
		receivedSensorsData[canSensorsDataRightIndex].valueH = msg->Data[3];
		receivedSensorsData[canSensorsDataRightIndex].valueL = msg->Data[4];
		receivedSensorsData[canSensorsDataRightIndex].checksum = msg->Data[5];

		canSensorsDataRightIndex++;

	}

	HAL_CAN_Receive_IT(hcan_ptr, CAN_FIFO0);

}
