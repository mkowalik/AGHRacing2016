#include "ecumaster.h"
#include "logged_data_types.h"
#include "current_data_provider.h"

#define ECU_CHANNEL_RPM 1
#define ECU_CHANNEL_MAP 2
#define ECU_CHANNEL_TPS 3
#define ECU_CHANNEL_IAT 4
#define ECU_CHANNEL_BATT 5
#define ECU_CHANNEL_IGN_ANGLE 6
#define ECU_CHANNEL_EGT1 8
#define ECU_CHANNEL_EGT2 9
#define ECU_CHANNEL_DWELL_TIME 11
#define ECU_CHANNEL_PULSE_WIDTH 7
#define ECU_CHANNEL_WBO_LAMBDA 27
#define ECU_CHANNEL_WBO_AFR 12
#define ECU_CHANNEL_KNOCK_LEVEL 10
#define ECU_CHANNEL_VSS_SPEED 28
#define ECU_CHANNEL_GEAR 13
#define ECU_CHANNEL_BARO 14
#define ECU_CHANNEL_ANALOG_IN_1 15
#define ECU_CHANNEL_ANALOG_IN_2 16
#define ECU_CHANNEL_ANALOG_IN_3 17
#define ECU_CHANNEL_ANALOG_IN_4 18
#define ECU_CHANNEL_INJ_DC 19
#define ECU_CHANNEL_EMU_TEMP 20
#define ECU_CHANNEL_OIL_PRESSURE 21
#define ECU_CHANNEL_OIL_TEMP 22
#define ECU_CHANNEL_FUEL_PRESSURE 23
#define ECU_CHANNEL_CLT 24
#define ECU_CHANNEL_TABLES_SET 31
#define ECU_CHANNEL_FLEX_FUEL 25
#define ECU_CHANNEL_FF_TEMP 26
#define ECU_CHANNEL_CEL 255
#define ECU_CHANNEL_DELTA_FPR 29
#define ECU_CHANNEL_FUEL_LEVEL 30
//#define ECU_CHANNEL_SECONDARY_PULSE_WIDTH 7

volatile ECUData receivedECUData[ECU_BUFFER_SIZE];
volatile uint16_t ECUDataToSaveIndex = 0;
volatile uint16_t ECUDataReceivedIndex = 0;

void ecumaster_connection_init(){

}

volatile uint16_t get_ECUDataReceivedIndex(){
	return ECUDataReceivedIndex;
}

volatile uint16_t get_ECUDataToSaveIndex(){
	return ECUDataToSaveIndex;
}

volatile ECUData* get_receivedECUData(){
	return receivedECUData;
}

volatile ECUData* get_toReceiveECUDataPointer(){
	return &(receivedECUData[ECUDataReceivedIndex]);
}

ECUData get_actualReceivedData(){
	return receivedECUData[ECUDataToSaveIndex];
}

void checkECUData_thread(void* args){
	while (ECUDataToSaveIndex < ECUDataReceivedIndex){
		ECUData actECUFrame = receivedECUData[ECUDataToSaveIndex%ECU_BUFFER_SIZE];

		uint8_t loggedDataChannel;

		switch (actECUFrame.channel){
			case ECU_CHANNEL_RPM:
				loggedDataChannel = ECU_RPM;
				break;
			case ECU_CHANNEL_MAP:
				loggedDataChannel = ECU_MAP_SENSOR;
				break;
			case ECU_CHANNEL_TPS:
				loggedDataChannel = ECU_TPS;
				break;
			case ECU_CHANNEL_IAT:
				loggedDataChannel = ECU_IAT;
				break;
			case ECU_CHANNEL_BATT:
				loggedDataChannel = ECU_BATT;
				break;
			case ECU_CHANNEL_IGN_ANGLE:
				loggedDataChannel = ECU_IGN_ANGLE;
				break;
			case ECU_CHANNEL_EGT1:
				loggedDataChannel = ECU_EGT1;
				break;
			case ECU_CHANNEL_EGT2:
				loggedDataChannel = ECU_EGT2;
				break;
			case ECU_CHANNEL_DWELL_TIME:
				loggedDataChannel = ECU_DWELL_TIME;
				break;
			case ECU_CHANNEL_PULSE_WIDTH:
				loggedDataChannel = ECU_PULSE_WIDTH;
				break;
			case ECU_CHANNEL_WBO_LAMBDA:
				loggedDataChannel = ECU_WBO_LAMBDA;
				break;
			case ECU_CHANNEL_WBO_AFR:
				loggedDataChannel = ECU_WBO_AFR;
				break;
			case ECU_CHANNEL_KNOCK_LEVEL:
				loggedDataChannel = ECU_KNOCK_LEVEL;
				break;
			case ECU_CHANNEL_VSS_SPEED:
				loggedDataChannel = ECU_VSS_SPEED;
				break;
			case ECU_CHANNEL_GEAR:
				loggedDataChannel = ECU_GEAR;
				break;
			case ECU_CHANNEL_BARO:
				loggedDataChannel = ECU_BARO;
				break;
			case ECU_CHANNEL_ANALOG_IN_1:
				loggedDataChannel = ECU_ANALOG_IN_1;
				break;
			case ECU_CHANNEL_ANALOG_IN_2:
				loggedDataChannel = ECU_ANALOG_IN_2;
				break;
			case ECU_CHANNEL_ANALOG_IN_3:
				loggedDataChannel = ECU_ANALOG_IN_3;
				break;
			case ECU_CHANNEL_ANALOG_IN_4:
				loggedDataChannel = ECU_ANALOG_IN_4;
				break;
			case ECU_CHANNEL_INJ_DC:
				loggedDataChannel = ECU_INJ_DC;
				break;
			case ECU_CHANNEL_EMU_TEMP:
				loggedDataChannel = ECU_EMU_TEMP;
				break;
			case ECU_CHANNEL_OIL_PRESSURE:
				loggedDataChannel = ECU_OIL_PRESSURE;
				break;
			case ECU_CHANNEL_OIL_TEMP:
				loggedDataChannel = ECU_OIL_TEMP;
				break;
			case ECU_CHANNEL_FUEL_PRESSURE:
				loggedDataChannel = ECU_FUEL_PRESSURE;
				break;
			case ECU_CHANNEL_CLT:
				loggedDataChannel = ECU_CLT;
				break;
			case ECU_CHANNEL_TABLES_SET:
				loggedDataChannel = ECU_TABLES_SET;
				break;
			case ECU_CHANNEL_FLEX_FUEL:
				loggedDataChannel = ECU_FLEX_FUEL;
				break;
			case ECU_CHANNEL_FF_TEMP:
				loggedDataChannel = ECU_FF_TEMP;
				break;
			case ECU_CHANNEL_CEL:
				loggedDataChannel = ECU_CEL;
				break;
			case ECU_CHANNEL_DELTA_FPR:
				loggedDataChannel = ECU_DELTA_FPR;
				break;
			case ECU_CHANNEL_FUEL_LEVEL:
				loggedDataChannel = ECU_FUEL_LEVEL;
				break;
//			case ECU_CHANNEL_SECONDARY_PULSE_WIDTH:
//				loggedDataChannel =
		}
		saveCurrentData(loggedDataChannel, actECUFrame.value);
		if (ECUDataToSaveIndex>ECU_BUFFER_SIZE){
			ECUDataToSaveIndex-=ECU_BUFFER_SIZE;
			ECUDataReceivedIndex-=ECU_BUFFER_SIZE;
		}
	}
}
