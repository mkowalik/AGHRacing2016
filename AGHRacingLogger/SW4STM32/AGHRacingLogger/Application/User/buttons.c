#include "buttons.h"
#include <string.h>
#include "mxconstants.h"
#include "stm32f4xx_hal.h"
#include "stm32f407xx.h"

static uint32_t lastButtonResetTick = 0;
static uint32_t lastButtonSetTick = 0;

uint8_t buttons_updateButtonValue(){	//TODO do it on interrupt
	GPIO_PinState pinState = HAL_GPIO_ReadPin(Dash_Button2_GPIO_Port, Dash_Button2_Pin);
	if (pinState==GPIO_PIN_RESET){
		lastButtonResetTick = HAL_GetTick();
	} else {
		lastButtonSetTick = HAL_GetTick();
	}

	if (((int32_t)lastButtonResetTick-(int32_t)lastButtonSetTick)>50){
		lastButtonSetTick = lastButtonResetTick+500;
		return 1;
	}
	return 0;

}
