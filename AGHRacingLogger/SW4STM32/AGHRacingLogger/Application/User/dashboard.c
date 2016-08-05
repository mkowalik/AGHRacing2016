#include "dashboard.h"
#include "logged_data_types.h"
#include "SSD1306.h"
#include <stdlib.h>
#include <string.h>
#include "current_data_provider.h"
#include "mxconstants.h"
#include "stm32f4xx_hal.h"
#include "gear_display.h"

static uint16_t lastDisplayedValue;
static uint8_t lastDisplayedFunctionIndex;

static uint16_t lastDisplayedGearValue;

uint8_t avaliableFunctions[] = {ECU_BATT, ECU_CLT, ECU_TPS, ECU_RPM, ECU_WBO_LAMBDA, ECU_WBO_AFR, ECU_OIL_PRESSURE}; //TODO przeniesc do pliku .h

void display_value(uint16_t value, uint8_t channel){

	char s;

	int32_t divider = (int32_t) DataTypes_divider[channel];

	if (channel==ECU_RPM){
		divider = 100;
	}
	int32_t valueToDisplayBase = value/divider;
	int32_t valueToDisplayDecimal = ((value%divider)*10)/divider;

	uint32_t val = (valueToDisplayBase/100)%10;
	if (val!=0 || valueToDisplayBase>=1000){
		s = val+'0';
		ssd1306_draw_4834char(0, 0, s);
	} else {
		ssd1306_fill_screen(0, 0, 33, 47, 0);
	}
	val = (valueToDisplayBase/10)%10;
	if (val!=0 || valueToDisplayBase>=100){
		s = val+'0';
		ssd1306_draw_4834char(34+2,0, s);
	} else {
		ssd1306_fill_screen(34+2, 0, 34+2+33, 47, 0);
	}

	val = (valueToDisplayBase)%10;
	s = val+'0';
	ssd1306_draw_4834char(34*2+4,0, s);

	val = valueToDisplayDecimal%10;
	s = val+'0';
	ssd1306_draw_2819char(34*3+6,(48-28), s);

	ssd1306_refresh_gram();

}

void display_description(uint8_t channel){
	ssd1306_display_string(0, 52, (uint8_t*) DataTypes_fullName[channel], 12, 1);
	int16_t x = 128-(8*strlen(DataTypes_unitString[channel]));
	ssd1306_display_string(x, 48, (uint8_t*) DataTypes_unitString[channel], 16, 1);
	ssd1306_refresh_gram();
}


void dash_init(){

	lastDisplayedFunctionIndex = DEFAULT_DASHBOARD_FUNCTION_INDEX;
	lastDisplayedValue = getCurrentDataForChannel(avaliableFunctions[lastDisplayedFunctionIndex]);

	lastDisplayedGearValue = 0;
	gearDisplay_displayDigit(lastDisplayedGearValue, 1);

	ssd1306_init();
	ssd1306_display_on();
	ssd1306_clear_screen(0x00);

	display_value(lastDisplayedValue, avaliableFunctions[lastDisplayedFunctionIndex]);
	display_description(avaliableFunctions[lastDisplayedFunctionIndex]);
	ssd1306_refresh_gram();
}

void clear_description(){
	ssd1306_fill_screen(0, 48, 127, 63, 0);
}

void dash_displayCurrentData(uint8_t channelIndex){

	uint16_t data = getCurrentDataForChannel(avaliableFunctions[channelIndex]);

	if (lastDisplayedValue!=data || lastDisplayedFunctionIndex!=channelIndex){

		display_value(data, avaliableFunctions[channelIndex]);

		if (lastDisplayedFunctionIndex!=channelIndex){
			clear_description();
			display_description(avaliableFunctions[channelIndex]);
		}
	}

	lastDisplayedFunctionIndex = channelIndex;
	lastDisplayedValue=data;

}

static uint32_t lastButtonResetTick = 0;
static uint32_t lastButtonSetTick = 0;

uint8_t dash_updateButtonValue(){
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

static uint16_t lastDisplayedNeutralValue;

void dash_displayActualGear(){
	uint16_t dataNeutral = getCurrentDataForChannel(SENSOR_NEUTRAL);
//	uint16_t dataGear_virtual = getCurrentDataForChannel(VIRTUAL_GEAR);	//TODO virtual gear sensor

	if ((dataNeutral!=lastDisplayedNeutralValue)/* || (dataGear_virtual!=lastDisplayedGearValue)*/){	//TODO virtual gear sensor
//		gearDisplay_displayDigit(dataGear_virtual, (dataNeutral>0));	//TODO virtual gear sensor
		gearDisplay_offDisplay((dataNeutral>0));
		lastDisplayedNeutralValue = dataNeutral;
//		lastDisplayedGearValue = dataGear_virtual;	//TODO virtual gear sensor
	}

}
