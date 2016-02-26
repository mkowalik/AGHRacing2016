#include "logged_data_types.h"

#define NULL 0

char* DataTypes_unitString[CHANNEL_NUMBER];
char* DataTypes_fullName[CHANNEL_NUMBER];

void DataTypes_initDefaults(){

	uint16_t data_type;

	for (data_type=0; data_type<CHANNEL_NUMBER; data_type++){
		DataTypes_divider[data_type] = 1;
		DataTypes_gaugeDivider[data_type] = 1;
		DataTypes_gaugeMinValue[data_type] = 0;
		DataTypes_gaugeMaxValue[data_type] = INT16_MAX;
		DataTypes_AlertMode[data_type] = DATA_NO_ALERT;
		DataTypes_unitString[data_type] = NULL;
		DataTypes_fullName[data_type] = NULL;
	}

	DataTypes_divider[ECU_RPM]= 1;
	DataTypes_gaugeDivider[ECU_RPM]= 1000;
	DataTypes_gaugeMinValue[ECU_RPM]= 0;
	DataTypes_gaugeMaxValue[ECU_RPM]= 9000;
	DataTypes_unitString[ECU_RPM]= "RPM";
	DataTypes_fullName[ECU_RPM]= "ECU_RPM";
	DataTypes_highAlert[ECU_RPM]= 8500;
	DataTypes_AlertMode[ECU_RPM]= DATA_ONLY_HIGH_VALUE_ALERT;

	DataTypes_divider[ECU_MAP_SENSOR]= 1;
	DataTypes_gaugeDivider[ECU_MAP_SENSOR]= 1;
	DataTypes_gaugeMinValue[ECU_MAP_SENSOR]= 0;
	DataTypes_gaugeMaxValue[ECU_MAP_SENSOR]= 400;
	DataTypes_unitString[ECU_MAP_SENSOR]= "kPa";
	DataTypes_fullName[ECU_MAP_SENSOR]= "ECU_MAP_SENSOR";
	DataTypes_highAlert[ECU_MAP_SENSOR]= 300;
	DataTypes_AlertMode[ECU_MAP_SENSOR]= DATA_ONLY_HIGH_VALUE_ALERT;

	DataTypes_divider[ECU_TPS]= 1;
	DataTypes_gaugeDivider[ECU_TPS]= 1;
	DataTypes_gaugeMinValue[ECU_TPS]= 0;
	DataTypes_gaugeMaxValue[ECU_TPS]= 100;
	DataTypes_unitString[ECU_TPS]= "%";
	DataTypes_fullName[ECU_TPS]= "ECU_TPS";

	DataTypes_divider[ECU_IAT]= 1;
	DataTypes_gaugeDivider[ECU_IAT]= 1;
	DataTypes_gaugeMinValue[ECU_IAT]= -40;
	DataTypes_gaugeMaxValue[ECU_IAT]= 120;
	DataTypes_unitString[ECU_IAT]= "C";
	DataTypes_fullName[ECU_IAT]= "ECU_IAT";

	DataTypes_divider[ECU_BATT]= 37;
	DataTypes_gaugeDivider[ECU_BATT]= 1;
	DataTypes_gaugeMinValue[ECU_BATT]= 8;
	DataTypes_gaugeMaxValue[ECU_BATT]= 20;
	DataTypes_unitString[ECU_BATT]= "V";
	DataTypes_fullName[ECU_BATT]= "Battery voltage";
	DataTypes_lowAlert[ECU_BATT]= 8;
	DataTypes_AlertMode[ECU_BATT]= DATA_ONLY_LOW_VALUE_ALERT;

	DataTypes_divider[ECU_IGN_ANGLE]= 2;
	DataTypes_gaugeDivider[ECU_IGN_ANGLE]= 1;
	DataTypes_gaugeMinValue[ECU_IGN_ANGLE]= -20;
	DataTypes_gaugeMaxValue[ECU_IGN_ANGLE]= 60;
	DataTypes_unitString[ECU_IGN_ANGLE]= "deg";
	DataTypes_fullName[ECU_IGN_ANGLE]= "Igntion Angle";

	DataTypes_divider[ECU_EGT1]= 1;
	DataTypes_gaugeDivider[ECU_EGT1]= 100;
	DataTypes_gaugeMinValue[ECU_EGT1]= 0;
	DataTypes_gaugeMaxValue[ECU_EGT1]= 1100;
	DataTypes_unitString[ECU_EGT1]= "C";
	DataTypes_fullName[ECU_EGT1]= "EGT #1";
	DataTypes_highAlert[ECU_EGT1]= 950;
	DataTypes_AlertMode[ECU_EGT1]= DATA_ONLY_HIGH_VALUE_ALERT;

	DataTypes_divider[ECU_EGT2]= 1;
	DataTypes_gaugeDivider[ECU_EGT2]= 100;
	DataTypes_gaugeMinValue[ECU_EGT2]= 0;
	DataTypes_gaugeMaxValue[ECU_EGT2]= 1100;
	DataTypes_unitString[ECU_EGT2]= "C";
	DataTypes_fullName[ECU_EGT2]= "EGT #2";
	DataTypes_highAlert[ECU_EGT2]= 950;
	DataTypes_AlertMode[ECU_EGT2]= DATA_ONLY_HIGH_VALUE_ALERT;

	DataTypes_divider[ECU_DWELL_TIME]= 20;
	DataTypes_gaugeDivider[ECU_DWELL_TIME]= 1;
	DataTypes_gaugeMinValue[ECU_DWELL_TIME]= 0;
	DataTypes_gaugeMaxValue[ECU_DWELL_TIME]= 10;
	DataTypes_unitString[ECU_DWELL_TIME]= "ms";
	DataTypes_fullName[ECU_DWELL_TIME]= "Dwell Time";

	DataTypes_divider[ECU_PULSE_WIDTH]= 62;
	DataTypes_gaugeDivider[ECU_PULSE_WIDTH]= 1;
	DataTypes_gaugeMinValue[ECU_PULSE_WIDTH]= 0;
	DataTypes_gaugeMaxValue[ECU_PULSE_WIDTH]= 25;
	DataTypes_unitString[ECU_PULSE_WIDTH]= "ms";
	DataTypes_fullName[ECU_PULSE_WIDTH]= "Injectors PW";

	DataTypes_divider[ECU_WBO_LAMBDA]= 128;
	DataTypes_gaugeDivider[ECU_WBO_LAMBDA]= 1;
	DataTypes_gaugeMinValue[ECU_WBO_LAMBDA]= 0.7;
	DataTypes_gaugeMaxValue[ECU_WBO_LAMBDA]= 1.3;
	DataTypes_unitString[ECU_WBO_LAMBDA]= "lambda";
	DataTypes_fullName[ECU_WBO_LAMBDA]= "Lambda";

	DataTypes_divider[ECU_WBO_AFR]= 10;
	DataTypes_gaugeDivider[ECU_WBO_AFR]= 1;
	DataTypes_gaugeMinValue[ECU_WBO_AFR]= 10;
	DataTypes_gaugeMaxValue[ECU_WBO_AFR]= 20;
	DataTypes_unitString[ECU_WBO_AFR]= "AFR";
	DataTypes_fullName[ECU_WBO_AFR]= "AFR";

	DataTypes_divider[ECU_KNOCK_LEVEL]= 51;
	DataTypes_gaugeDivider[ECU_KNOCK_LEVEL]= 1;
	DataTypes_gaugeMinValue[ECU_KNOCK_LEVEL]= 0;
	DataTypes_gaugeMaxValue[ECU_KNOCK_LEVEL]= 5;
	DataTypes_unitString[ECU_KNOCK_LEVEL]= "V";
	DataTypes_fullName[ECU_KNOCK_LEVEL]= "Knock Level";

	DataTypes_divider[ECU_VSS_SPEED]= 4;
	DataTypes_gaugeDivider[ECU_VSS_SPEED]= 1;
	DataTypes_gaugeMinValue[ECU_VSS_SPEED]= 0;
	DataTypes_gaugeMaxValue[ECU_VSS_SPEED]= 300;
	DataTypes_unitString[ECU_VSS_SPEED]= "km/h";
	DataTypes_fullName[ECU_VSS_SPEED]= "Vehicle Speed";

	DataTypes_divider[ECU_GEAR]= 1;
	DataTypes_gaugeDivider[ECU_GEAR]= 1;
	DataTypes_gaugeMinValue[ECU_GEAR]= 0;
	DataTypes_gaugeMaxValue[ECU_GEAR]= 6;
	DataTypes_unitString[ECU_GEAR]= "";
	DataTypes_fullName[ECU_GEAR]= "Gear";

	DataTypes_divider[ECU_BARO]= 1;
	DataTypes_gaugeDivider[ECU_BARO]= 1;
	DataTypes_gaugeMinValue[ECU_BARO]= 50;
	DataTypes_gaugeMaxValue[ECU_BARO]= 120;
	DataTypes_unitString[ECU_BARO]= "kPa";
	DataTypes_fullName[ECU_BARO]= "BARO";

	DataTypes_divider[ECU_ANALOG_IN_1]= 51;
	DataTypes_gaugeDivider[ECU_ANALOG_IN_1]= 1;
	DataTypes_gaugeMinValue[ECU_ANALOG_IN_1]= 0;
	DataTypes_gaugeMaxValue[ECU_ANALOG_IN_1]= 5;
	DataTypes_unitString[ECU_ANALOG_IN_1]= "V";
	DataTypes_fullName[ECU_ANALOG_IN_1]= "Analog #1";

	DataTypes_divider[ECU_ANALOG_IN_2]= 51;
	DataTypes_gaugeDivider[ECU_ANALOG_IN_2]= 1;
	DataTypes_gaugeMinValue[ECU_ANALOG_IN_2]= 0;
	DataTypes_gaugeMaxValue[ECU_ANALOG_IN_2]= 5;
	DataTypes_unitString[ECU_ANALOG_IN_2]= "V";
	DataTypes_fullName[ECU_ANALOG_IN_2]= "Analog #2";

	DataTypes_divider[ECU_ANALOG_IN_3]= 51;
	DataTypes_gaugeDivider[ECU_ANALOG_IN_3]= 1;
	DataTypes_gaugeMinValue[ECU_ANALOG_IN_3]= 0;
	DataTypes_gaugeMaxValue[ECU_ANALOG_IN_3]= 5;
	DataTypes_unitString[ECU_ANALOG_IN_3]= "V";
	DataTypes_fullName[ECU_ANALOG_IN_3]= "Analog #3";

	DataTypes_divider[ECU_ANALOG_IN_4]= 51;
	DataTypes_gaugeDivider[ECU_ANALOG_IN_4]= 1;
	DataTypes_gaugeMinValue[ECU_ANALOG_IN_4]= 0;
	DataTypes_gaugeMaxValue[ECU_ANALOG_IN_4]= 5;
	DataTypes_unitString[ECU_ANALOG_IN_4]= "V";
	DataTypes_fullName[ECU_ANALOG_IN_4]= "Analog #4";

	DataTypes_divider[ECU_INJ_DC]= 2;
	DataTypes_gaugeDivider[ECU_INJ_DC]= 1;
	DataTypes_gaugeMinValue[ECU_INJ_DC]= 0;
	DataTypes_gaugeMaxValue[ECU_INJ_DC]= 100;
	DataTypes_unitString[ECU_INJ_DC]= "%";
	DataTypes_fullName[ECU_INJ_DC]= "Injectors DC";

	DataTypes_divider[ECU_EMU_TEMP]= 1;
	DataTypes_gaugeDivider[ECU_EMU_TEMP]= 1;
	DataTypes_gaugeMinValue[ECU_EMU_TEMP]= -40;
	DataTypes_gaugeMaxValue[ECU_EMU_TEMP]= 120;
	DataTypes_unitString[ECU_EMU_TEMP]= "C";
	DataTypes_fullName[ECU_EMU_TEMP]= "ECU Temperature";

	DataTypes_divider[ECU_OIL_PRESSURE]= 16;
	DataTypes_gaugeDivider[ECU_OIL_PRESSURE]= 1;
	DataTypes_gaugeMinValue[ECU_OIL_PRESSURE]= 0;
	DataTypes_gaugeMaxValue[ECU_OIL_PRESSURE]= 12;
	DataTypes_unitString[ECU_OIL_PRESSURE]= "Bar";
	DataTypes_fullName[ECU_OIL_PRESSURE]= "Oil pressure";
	DataTypes_lowAlert[ECU_OIL_PRESSURE]= 0.4;
	DataTypes_AlertMode[ECU_OIL_PRESSURE]= DATA_ONLY_LOW_VALUE_ALERT;

	DataTypes_divider[ECU_OIL_TEMP]= 1;
	DataTypes_gaugeDivider[ECU_OIL_TEMP]= 1;
	DataTypes_gaugeMinValue[ECU_OIL_TEMP]= 0;
	DataTypes_gaugeMaxValue[ECU_OIL_TEMP]= 160;
	DataTypes_unitString[ECU_OIL_TEMP]= "C";
	DataTypes_fullName[ECU_OIL_TEMP]= "Oil temperature";
	DataTypes_highAlert[ECU_OIL_TEMP]= 140;
	DataTypes_AlertMode[ECU_OIL_TEMP]= DATA_ONLY_HIGH_VALUE_ALERT;

	DataTypes_divider[ECU_FUEL_PRESSURE]= 32;
	DataTypes_gaugeDivider[ECU_FUEL_PRESSURE]= 1;
	DataTypes_gaugeMinValue[ECU_FUEL_PRESSURE]= 0;
	DataTypes_gaugeMaxValue[ECU_FUEL_PRESSURE]= 7;
	DataTypes_unitString[ECU_FUEL_PRESSURE]= "Bar";
	DataTypes_fullName[ECU_FUEL_PRESSURE]= "Fuel pressure";

	DataTypes_divider[ECU_CLT]= 1;
	DataTypes_gaugeDivider[ECU_CLT]= 1;
	DataTypes_gaugeMinValue[ECU_CLT]= -40;
	DataTypes_gaugeMaxValue[ECU_CLT]= 220;
	DataTypes_unitString[ECU_CLT]= "C";
	DataTypes_fullName[ECU_CLT]= "ECU_CLT";
	DataTypes_highAlert[ECU_CLT]= 105;
	DataTypes_AlertMode[ECU_CLT]= DATA_ONLY_HIGH_VALUE_ALERT;

	DataTypes_divider[ECU_TABLES_SET]= 1;
	DataTypes_gaugeDivider[ECU_TABLES_SET]= 1;
	DataTypes_gaugeMinValue[ECU_TABLES_SET]= 0;
	DataTypes_gaugeMaxValue[ECU_TABLES_SET]= 1;
	DataTypes_unitString[ECU_TABLES_SET]= "";
	DataTypes_fullName[ECU_TABLES_SET]= "Tables set";

	DataTypes_divider[ECU_FLEX_FUEL]= 2;
	DataTypes_gaugeDivider[ECU_FLEX_FUEL]= 1;
	DataTypes_gaugeMinValue[ECU_FLEX_FUEL]= 0;
	DataTypes_gaugeMaxValue[ECU_FLEX_FUEL]= 100;
	DataTypes_unitString[ECU_FLEX_FUEL]= "%";
	DataTypes_fullName[ECU_FLEX_FUEL]= "FF Ethanol content";

	DataTypes_divider[ECU_FF_TEMP]= 1;
	DataTypes_gaugeDivider[ECU_FF_TEMP]= 1;
	DataTypes_gaugeMinValue[ECU_FF_TEMP]= -30;
	DataTypes_gaugeMaxValue[ECU_FF_TEMP]= 120;
	DataTypes_unitString[ECU_FF_TEMP]= "C";
	DataTypes_fullName[ECU_FF_TEMP]= "FF Fuel Temp";

	DataTypes_divider[ECU_CEL]= 1;
	DataTypes_gaugeDivider[ECU_CEL]= 1;
	DataTypes_gaugeMinValue[ECU_CEL]= 0;
	DataTypes_gaugeMaxValue[ECU_CEL]= 128;
	DataTypes_unitString[ECU_CEL]= "";
	DataTypes_fullName[ECU_CEL]= "Check engine code";

	DataTypes_divider[ECU_DELTA_FPR]= 1;
	DataTypes_gaugeDivider[ECU_DELTA_FPR]= 50;
	DataTypes_gaugeMinValue[ECU_DELTA_FPR]= 100;
	DataTypes_gaugeMaxValue[ECU_DELTA_FPR]= 500;
	DataTypes_unitString[ECU_DELTA_FPR]= "kPa";
	DataTypes_fullName[ECU_DELTA_FPR]= "Fuel pressure delta";

	DataTypes_divider[ECU_FUEL_LEVEL]= 1;
	DataTypes_gaugeDivider[ECU_FUEL_LEVEL]= 1;
	DataTypes_gaugeMinValue[ECU_FUEL_LEVEL]= 0;
	DataTypes_gaugeMaxValue[ECU_FUEL_LEVEL]= 100;
	DataTypes_unitString[ECU_FUEL_LEVEL]= "%";
	DataTypes_fullName[ECU_FUEL_LEVEL]= "Fuel level";
	DataTypes_lowAlert[ECU_FUEL_LEVEL]= 5;
	DataTypes_AlertMode[ECU_FUEL_LEVEL]= DATA_ONLY_LOW_VALUE_ALERT;

}
