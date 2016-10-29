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
static uint8_t can_stopped = 0;

#define CAN_SENSOR_CHANNEL_NEUTRAL	256
#define CAN_SENSOR_CHANNEL_GEAR		257

extern osMutexId currentDataMutexHandle;

CanRxMsgTypeDef rx_msg;

void canSensors_ReceiveDataFromSensors_init(CAN_HandleTypeDef* hcan_ptr_arg){

	hcan_ptr = hcan_ptr_arg;

	HAL_StatusTypeDef status;

	CAN_FilterConfTypeDef sFilterConfig;
	sFilterConfig.FilterNumber = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.BankNumber = 0;

	HAL_CAN_ConfigFilter(hcan_ptr, &sFilterConfig);

	hcan_ptr->pRxMsg = &rx_msg;

	do {
		status = HAL_CAN_Receive(hcan_ptr, CAN_FIFO0, 150);
	} while ((status!=HAL_OK && status!=HAL_TIMEOUT) || (hcan_ptr->ErrorCode != HAL_CAN_ERROR_NONE));

}

void canSensors_ReceiveDataFromSensors_Start(){

	HAL_CAN_Receive_IT(hcan_ptr, CAN_FIFO0);

}

void canSensors_saveCurrentData(){

	while (canSensorsDataLeftIndex <canSensorsDataRightIndex){

		CanSensorsData actCanSensorData = receivedSensorsData[canSensorsDataLeftIndex%CAN_SENSORS_BUFFER_SIZE];

		uint8_t loggedDataChannel = 0;

		switch (actCanSensorData.channelId){
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

	if (can_stopped){
		can_stopped = 0;
		HAL_CAN_Receive_IT(hcan_ptr, CAN_FIFO0);
	}

}

uint32_t counter = 0;

void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan){

	if ((rx_msg.IDE==CAN_ID_STD) && (rx_msg.RTR == CAN_RTR_DATA) && (rx_msg.DLC == BYTES_IN_SENSORS_FRAME)){

		receivedSensorsData[canSensorsDataRightIndex%CAN_SENSORS_BUFFER_SIZE].channelId = rx_msg.StdId;
		receivedSensorsData[canSensorsDataRightIndex%CAN_SENSORS_BUFFER_SIZE].valueL = rx_msg.Data[0];
		receivedSensorsData[canSensorsDataRightIndex%CAN_SENSORS_BUFFER_SIZE].valueH = rx_msg.Data[1];

		canSensorsDataRightIndex++;

		counter++;

	}

	if (canSensorsDataRightIndex - canSensorsDataLeftIndex < CAN_SENSORS_BUFFER_SIZE){
		HAL_CAN_Receive_IT(hcan_ptr, CAN_FIFO0);
	} else {
		can_stopped = 1;
	}

}
