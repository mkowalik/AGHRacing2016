#include "ws2812_driver.h"
#include "stm32f4xx_hal.h"
#include "string.h"
#include "mxconstants.h"
#include "delay_timer6.h"
#include "logged_data_types.h"
#include "current_data_provider.h"

extern SPI_HandleTypeDef hspi2;

const uint8_t WS2812_RPMPattern[] = {
	0b11011011, 0b01101101, 0b10110110, //GREEN
	0b10010010, 0b01001001, 0b00100100,
	0b10010010, 0b01001001, 0b00100100,

	0b11011011, 0b01101101, 0b10110110, //GREEN
	0b10010010, 0b01001001, 0b00100100,
	0b10010010, 0b01001001, 0b00100100,

	0b11011011, 0b01101101, 0b10110110, //GREEN
	0b10010010, 0b01001001, 0b00100100,
	0b10010010, 0b01001001, 0b00100100,

	0b11011011, 0b01101101, 0b10110110, //GREEN
	0b10010010, 0b01001001, 0b00100100,
	0b10010010, 0b01001001, 0b00100100,

	0b10010010, 0b01001001, 0b00100100, //BLUE
	0b10010010, 0b01001001, 0b00100100,
	0b11011011, 0b01101101, 0b10110110,

	0b10010010, 0b01001001, 0b00100100, //BLUE
	0b10010010, 0b01001001, 0b00100100,
	0b11011011, 0b01101101, 0b10110110,

	0b10010010, 0b01001001, 0b00100100, //BLUE
	0b10010010, 0b01001001, 0b00100100,
	0b11011011, 0b01101101, 0b10110110,

	0b10010010, 0b01001001, 0b00100100, //BLUE
	0b10010010, 0b01001001, 0b00100100,
	0b11011011, 0b01101101, 0b10110110,

	0b10010010, 0b01001001, 0b00100100, //RED
	0b11011011, 0b01101101, 0b10110110,
	0b10010010, 0b01001001, 0b00100100,

	0b10010010, 0b01001001, 0b00100100, //RED
	0b11011011, 0b01101101, 0b10110110,
	0b10010010, 0b01001001, 0b00100100,

	0b10010010, 0b01001001, 0b00100100, //RED
	0b11011011, 0b01101101, 0b10110110,
	0b10010010, 0b01001001, 0b00100100,

	0b10010010, 0b01001001, 0b00100100, //RED
	0b11011011, 0b01101101, 0b10110110,
	0b10010010, 0b01001001, 0b00100100};

const uint8_t WS2812_off[] = {
	0b10010010, 0b01001001, 0b00100100,
	0b10010010, 0b01001001, 0b00100100,
	0b10010010, 0b01001001, 0b00100100};

const uint8_t WS2812_red[] = {
	0b10010010, 0b01001001, 0b00100100,
	0b11011011, 0b01101101, 0b10110110,
	0b10010010, 0b01001001, 0b00100100};

const uint8_t WS2812_blue[] = {
	0b10010010, 0b01001001, 0b00100100,
	0b10010010, 0b01001001, 0b00100100,
	0b11011011, 0b01101101, 0b10110110};

const uint8_t WS2812_green[] = {
	0b11011011, 0b01101101, 0b10110110,
	0b10010010, 0b01001001, 0b00100100,
	0b10010010, 0b01001001, 0b00100100};

const uint8_t WS2812_yellow[] = {
	0b11011011, 0b01101101, 0b10110110, //YELLOW
	0b11011011, 0b01101101, 0b10110110,
	0b10010010, 0b01001001, 0b00100100};

uint8_t WS2182_RPMActual[12*9];

const uint8_t WS2812_CLTPattern[] = {
	0b11011011, 0b01101101, 0b10110110, //GREEN
	0b10010010, 0b01001001, 0b00100100,
	0b10010010, 0b01001001, 0b00100100,

	0b11011011, 0b01101101, 0b10110110, //GREEN
	0b10010010, 0b01001001, 0b00100100,
	0b10010010, 0b01001001, 0b00100100,

	0b11011011, 0b01101101, 0b10110110, //GREEN
	0b10010010, 0b01001001, 0b00100100,
	0b10010010, 0b01001001, 0b00100100,

	0b11011011, 0b01101101, 0b10110110, //YELLOW
	0b11011011, 0b01101101, 0b10110110,
	0b10010010, 0b01001001, 0b00100100,

	0b10010010, 0b01001001, 0b00100100, //RED
	0b11011011, 0b01101101, 0b10110110,
	0b10010010, 0b01001001, 0b00100100};

const uint8_t WS2812_FuelPattern[] = {
	0b10010010, 0b01001001, 0b00100100, //RED
	0b11011011, 0b01101101, 0b10110110,
	0b10010010, 0b01001001, 0b00100100,

	0b11011011, 0b01101101, 0b10110110, //GREEN
	0b10010010, 0b01001001, 0b00100100,
	0b10010010, 0b01001001, 0b00100100,

	0b11011011, 0b01101101, 0b10110110, //GREEN
	0b10010010, 0b01001001, 0b00100100,
	0b10010010, 0b01001001, 0b00100100,

	0b11011011, 0b01101101, 0b10110110, //GREEN
	0b10010010, 0b01001001, 0b00100100,
	0b10010010, 0b01001001, 0b00100100,

	0b11011011, 0b01101101, 0b10110110, //GREEN
	0b10010010, 0b01001001, 0b00100100,
	0b10010010, 0b01001001, 0b00100100,};


uint8_t WS2812_CLTFuelActual[5*9];

uint8_t WS2812_AlertActual[3*9];

void ws2812_init(){
	//TODO 50us low level state on every ws2812

	DelayMicroseconds(500);

	for (uint8_t i=0; i<12; i++){
		memcpy(WS2182_RPMActual+(i*9), WS2812_off, 9);
	}

	while (HAL_SPI_GetState(&hspi2)!=HAL_SPI_STATE_READY); //wait for DMA

	HAL_GPIO_WritePin(WS2812_MultiSelect_1_GPIO_Port, WS2812_MultiSelect_1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(WS2812_MultiSelect_2_GPIO_Port, WS2812_MultiSelect_2_Pin, GPIO_PIN_SET);

	HAL_SPI_Transmit_DMA(&hspi2, WS2182_RPMActual, 9*12);


	DelayMicroseconds(500);

	for (uint8_t i=0; i<5; i++){
		memcpy(WS2812_CLTFuelActual+(i*9), WS2812_off, 9);
	}

	while (HAL_SPI_GetState(&hspi2)!=HAL_SPI_STATE_READY); //wait for DMA

	HAL_GPIO_WritePin(WS2812_MultiSelect_1_GPIO_Port, WS2812_MultiSelect_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(WS2812_MultiSelect_2_GPIO_Port, WS2812_MultiSelect_2_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit_DMA(&hspi2, WS2812_CLTFuelActual, 9*5);


	DelayMicroseconds(500);

	for (uint8_t i=0; i<5; i++){
		memcpy(WS2812_CLTFuelActual+(i*9), WS2812_off, 9);
	}

	while (HAL_SPI_GetState(&hspi2)!=HAL_SPI_STATE_READY); //wait for DMA

	HAL_GPIO_WritePin(WS2812_MultiSelect_1_GPIO_Port, WS2812_MultiSelect_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(WS2812_MultiSelect_2_GPIO_Port, WS2812_MultiSelect_2_Pin, GPIO_PIN_SET);

	HAL_SPI_Transmit_DMA(&hspi2, WS2812_CLTFuelActual, 9*5);

	DelayMicroseconds(500);

	for (int i=0; i<3; i++){
		memcpy(WS2812_AlertActual+(i*9), WS2812_off, 9);
	}

	while (HAL_SPI_GetState(&hspi2)!=HAL_SPI_STATE_READY); //wait for DMA

	HAL_GPIO_WritePin(WS2812_MultiSelect_1_GPIO_Port, WS2812_MultiSelect_1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(WS2812_MultiSelect_2_GPIO_Port, WS2812_MultiSelect_2_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit_DMA(&hspi2, WS2812_AlertActual, 9*3);

}

static uint8_t LED_RPM_number_prev=0;
static uint8_t LED_CLT_number_prev=0;
static uint8_t LED_Fuel_number_prev=0;
static uint8_t LED1_Alert_number_prev=0;
static uint8_t LED2_Alert_number_prev=0;
static uint8_t LED3_Alert_number_prev=0;

static uint8_t displayRPMEventCounter = REFRESH_LEDS_CYCLES_NUMBER-1;

/**
 * Argument uint8_t value:
 * 0    - LEDs off
 * 1-12 - given number of LEDs turned on with proper color
 * >12  - all LEDs red on
 */
void ws2812_displayRPM(uint8_t value){

	displayRPMEventCounter = (displayRPMEventCounter+1)%REFRESH_LEDS_CYCLES_NUMBER;

	if (value==LED_RPM_number_prev && displayRPMEventCounter!=0) return;

	if (value>12){
		for(uint8_t i=0; i<12; i++){
			memcpy(WS2182_RPMActual+(i*9), WS2812_red, 9);
		}
	} else {
		memcpy(WS2182_RPMActual, WS2812_RPMPattern, value*9);
		for (uint8_t i=value; i<12; i++){
			memcpy(WS2182_RPMActual+(i*9), WS2812_off, 9);
		}
	}

	while (HAL_SPI_GetState(&hspi2)!=HAL_SPI_STATE_READY); //wait for DMA

	HAL_GPIO_WritePin(WS2812_MultiSelect_1_GPIO_Port, WS2812_MultiSelect_1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(WS2812_MultiSelect_2_GPIO_Port, WS2812_MultiSelect_2_Pin, GPIO_PIN_SET);

	HAL_SPI_Transmit_DMA(&hspi2, WS2182_RPMActual, 9*12);

	LED_RPM_number_prev = value;

	displayRPMEventCounter = 0;

}

static uint8_t displayCLTEventCounter = REFRESH_LEDS_CYCLES_NUMBER-1;

/**
 * Argument uint8_t value:
 * 0    - LEDs off
 * 1    - first LED blue
 * 2-6  - given number of LEDs -1 turned on with proper color
 * >6   - all LEDs red on
 */
void ws2812_displayCLT(uint8_t value){

	displayCLTEventCounter = (displayCLTEventCounter+1)%REFRESH_LEDS_CYCLES_NUMBER;

	if (value==LED_CLT_number_prev && displayCLTEventCounter!=0) return;

	if (value==0){
		for (uint8_t i=0; i<5; i++){
			memcpy(WS2812_CLTFuelActual+(i*9), WS2812_off, 9);
		}
	} else if (value==1) {
		memcpy(WS2812_CLTFuelActual, WS2812_blue, 9);
		for (uint8_t i=1; i<5; i++){
			memcpy(WS2812_CLTFuelActual+(i*9), WS2812_off, 9);
		}
	} else 	if (value>6){
		for(uint8_t i=0; i<5; i++){
			memcpy(WS2812_CLTFuelActual+(i*9), WS2812_red, 9);
		}
	} else { //2-6
		memcpy(WS2812_CLTFuelActual, WS2812_CLTPattern, (value-1)*9);
		for (uint8_t i=value-1; i<5; i++){
			memcpy(WS2812_CLTFuelActual+(i*9), WS2812_off, 9);
		}
	}

	while (HAL_SPI_GetState(&hspi2)!=HAL_SPI_STATE_READY); //wait for DMA

	HAL_GPIO_WritePin(WS2812_MultiSelect_1_GPIO_Port, WS2812_MultiSelect_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(WS2812_MultiSelect_2_GPIO_Port, WS2812_MultiSelect_2_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit_DMA(&hspi2, WS2812_CLTFuelActual, 9*5);

	LED_CLT_number_prev = value;

	displayCLTEventCounter=0;

}

static uint8_t displayFuelEventCounter = REFRESH_LEDS_CYCLES_NUMBER-1;

/**
 * Argument uint8_t value:
 * 0    - LEDs off
 * 1-5  - given number of LEDs turned on with proper color
 */
void ws2812_displayFuel(uint8_t value){

	displayFuelEventCounter = (displayFuelEventCounter+1)%REFRESH_LEDS_CYCLES_NUMBER;

	if (value==LED_Fuel_number_prev && displayFuelEventCounter!=0) return;

	if (value>5) value=5;

	memcpy(WS2812_CLTFuelActual, WS2812_FuelPattern, value*9);
	for (uint8_t i=value; i<5; i++){
		memcpy(WS2812_CLTFuelActual+(i*9), WS2812_off, 9);
	}

	while (HAL_SPI_GetState(&hspi2)!=HAL_SPI_STATE_READY); //wait for DMA

	HAL_GPIO_WritePin(WS2812_MultiSelect_1_GPIO_Port, WS2812_MultiSelect_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(WS2812_MultiSelect_2_GPIO_Port, WS2812_MultiSelect_2_Pin, GPIO_PIN_SET);

	HAL_SPI_Transmit_DMA(&hspi2, WS2812_CLTFuelActual, 9*5);

	LED_Fuel_number_prev = value;

	displayFuelEventCounter = 0;

}

static uint8_t displayAlertsEventCounter = REFRESH_LEDS_CYCLES_NUMBER-1;

/**
 * Value meaning for every uint8_t led1, led2, led3 arguments:
 * 0 - no alert
 * 1 - blue
 * 2 - green
 * 3 - yellow
 * >3 - red
 */
void ws2812_displayAlerts(uint8_t led1, uint8_t led2, uint8_t led3){

	displayAlertsEventCounter = (displayAlertsEventCounter+1)%REFRESH_LEDS_CYCLES_NUMBER;

	if(led1==LED1_Alert_number_prev && led2==LED2_Alert_number_prev && led3==LED3_Alert_number_prev && displayAlertsEventCounter!=0) return;

	uint8_t leds[] = {led1, led2, led3};


	for (int i=0; i<3; i++){
		switch (leds[i]){
		case 0:
			memcpy(WS2812_AlertActual+(i*9), WS2812_off, 9);
			break;
		case 1:
			memcpy(WS2812_AlertActual+(i*9), WS2812_blue, 9);
			break;
		case 2:
			memcpy(WS2812_AlertActual+(i*9), WS2812_green, 9);
			break;
		case 3:
			memcpy(WS2812_AlertActual+(i*9), WS2812_yellow, 9);
			break;
		default:
			memcpy(WS2812_AlertActual+(i*9), WS2812_red, 9);
			break;
		}
	}

	while (HAL_SPI_GetState(&hspi2)!=HAL_SPI_STATE_READY); //wait for DMA

	HAL_GPIO_WritePin(WS2812_MultiSelect_1_GPIO_Port, WS2812_MultiSelect_1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(WS2812_MultiSelect_2_GPIO_Port, WS2812_MultiSelect_2_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit_DMA(&hspi2, WS2812_AlertActual, 9*3);

	LED1_Alert_number_prev=led1;
	LED2_Alert_number_prev=led2;
	LED3_Alert_number_prev=led3;

	displayAlertsEventCounter = 0;

}


#define RPM_LED_NUMBER	13
/*  								 		     GREEN  GREEN  GREEN  GREEN  BLUE   BLUE   BLUE   BLUE   RED    RED    RED    RED 	 ALL RED 		*/
const uint16_t rpm_led_values[RPM_LED_NUMBER] = {1000, 7000,  7500,  8000,  8500,  9000,  9500,  10000,  10500, 11000, 11500, 12000,   12500 };


#define CLT_LED_NUMBER	6
/*  								 			 GREEN  GREEN  GREEN  YELLOW  RED	ALL RED*/
const uint16_t clt_led_values[CLT_LED_NUMBER] = {60,    70,    80,    85,     90,        95};

void ws2812_displayDrivingWheelLEDs(){

	uint8_t led_number = 0;
	uint16_t value = getCurrentDataForChannel(ECU_RPM);

	while(led_number<RPM_LED_NUMBER && value >= rpm_led_values[led_number]){
		led_number++;
	}
	if (value > DataTypes_highAlert[ECU_RPM]){
		led_number = RPM_LED_NUMBER;
	}

	DelayMicroseconds(500);
	ws2812_displayRPM(led_number);


	led_number = 0;
	value = getCurrentDataForChannel(ECU_CLT);

	while (led_number<CLT_LED_NUMBER && value >= clt_led_values[led_number]){
		led_number++;
	}
	led_number++;
	if (value > DataTypes_highAlert[ECU_CLT]){
		led_number = CLT_LED_NUMBER+1;
	} else if (value < DataTypes_lowAlert[ECU_CLT]){
		led_number = 1;
	}
	DelayMicroseconds(500);
	ws2812_displayCLT(led_number);


	DelayMicroseconds(500);
	ws2812_displayFuel(0);

}

void ws2812_displayDashboardLEDs(){

	uint8_t led1_number = 0;
	uint16_t value = getCurrentDataForChannel(ECU_BATT);

	if (value<DataTypes_lowAlert[ECU_BATT] + 1*DataTypes_divider[ECU_BATT]){
		led1_number = 3;
	}
	if (value<DataTypes_lowAlert[ECU_BATT]){
		led1_number = 4;
	}

	uint8_t led2_number = 0;
	value = getCurrentDataForChannel(ECU_OIL_PRESSURE);

	if (value<DataTypes_lowAlert[ECU_OIL_PRESSURE]){
		led2_number = 4;
	}

	uint8_t led3_number = 0;
	value = getCurrentDataForChannel(SENSOR_NEUTRAL);

	if (value > 0){
		led3_number = 1;
	}


	DelayMicroseconds(500);
	ws2812_displayAlerts(led3_number, led2_number, led1_number);

}
