#include "mxconstants.h"
#include "stm32f4xx_hal.h"
#include "delay_timer6.h"

extern SPI_HandleTypeDef hspi1;

void gearDisplay_init(){

	  HAL_GPIO_WritePin(GearDisplay_ChipSelect_GPIO_Port, GearDisplay_ChipSelect_Pin, GPIO_PIN_RESET);
}

uint8_t digits[] = {
		0b11000000,
		0b11111001,
		0b10100100,
		0b10110000,
		0b10011001,
		0b10010010,
		0b10000010,
		0b11111000,
		0b10000000,
		0b10010000
};

void gearDisplay_displayDigit(uint8_t digit, uint8_t dot){
	uint8_t val = digits[digit%10];
	if (dot){
		val &= (0b01111111);
	}
	HAL_SPI_Transmit(&hspi1, &val, 1, 1);
	HAL_SPI_Transmit(&hspi1, &val, 1, 1);
	DelayMicroseconds(1);
	HAL_GPIO_WritePin(GearDisplay_ChipSelect_GPIO_Port, GearDisplay_ChipSelect_Pin, GPIO_PIN_SET);
	DelayMicroseconds(1);
	HAL_GPIO_WritePin(GearDisplay_ChipSelect_GPIO_Port, GearDisplay_ChipSelect_Pin, GPIO_PIN_RESET);
	DelayMicroseconds(1);
}

/* test
	  k = 0xFF&(~(1<<(i%8)));
	  HAL_SPI_Transmit(&hspi1, &k, 1, 10);
	  HAL_GPIO_WritePin(GearDisplay_ChipSelect_GPIO_Port, GearDisplay_ChipSelect_Pin, GPIO_PIN_SET);
	  HAL_Delay(1);//TODO
	  HAL_GPIO_WritePin(GearDisplay_ChipSelect_GPIO_Port, GearDisplay_ChipSelect_Pin, GPIO_PIN_RESET);
	  HAL_Delay(100);
 */
