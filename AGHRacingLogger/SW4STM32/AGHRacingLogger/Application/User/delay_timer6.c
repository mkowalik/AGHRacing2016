#include "delay_timer6.h"

extern TIM_HandleTypeDef htim6;

void DelayMicroseconds(uint16_t timeArg){

	__HAL_TIM_SetCounter(&htim6, 0);
	HAL_TIM_Base_Start(&htim6);
//	uint32_t a = __HAL_TIM_GET_COUNTER(&htim6);
	while (__HAL_TIM_GET_COUNTER(&htim6) < timeArg);
//	uint32_t b = __HAL_TIM_GET_COUNTER(&htim6);
}
