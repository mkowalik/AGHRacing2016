#include "sd_card_saver.h"
#include "stm32f4xx_hal_rtc.h"
#include "string.h"
#include "ff.h"
#include <stdlib.h>

#define MAX_FILENAME_PREFIX_LENGTH	128
#define MAX_FILENAME_LENGTH			(MAX_FILENAME_PREFIX_LENGTH+26)
#define FILE_NAME_PREFIX			"AGHRT_Log_"
#define FILE_EXTENSION				".csv"

static FIL fileHandler;
static TCHAR filename[MAX_FILENAME_LENGTH+1];

static FATFS SDCardHandler;
static uint8_t fileOpened = 0;

static TCHAR buffer[50];

void SDCardSaver_init(){
	if (f_mount(&SDCardHandler, "", 0)!=FR_OK){
		//TODO zrob cos zlego
	}
}

void SDCardSaver_initNewFile(){
	RTC_TimeTypeDef *sTime;
	RTC_DateTypeDef *sDate;

	HAL_RTC_GetTime(NULL, sTime, FORMAT_BCD); //TODO RTC handler instead of NULL
	HAL_RTC_GetDate(NULL, sDate, FORMAT_BCD); //TODO RTC handler instead of NULL
	strcpy(filename, FILE_NAME_PREFIX);
	itoa(sDate->Year, filename+strlen(filename), 10);
	strcat(filename, "-");
	itoa(sDate->Month, filename+strlen(filename), 10);
	strcat(filename, "-");
	itoa(sDate->Date, filename+strlen(filename), 10);
	strcat(filename, "_");

	itoa(sTime->Hours, filename+strlen(filename), 10);
	strcat(filename, "_");
	itoa(sTime->Minutes, filename+strlen(filename), 10);
	strcat(filename, "_");
	itoa(sTime->Seconds, filename+strlen(filename), 10);

	char basicFilename[MAX_FILENAME_LENGTH+1];
	strcpy(basicFilename, filename);

	strcat(filename, FILE_EXTENSION);

	uint8_t fileVersionsCounter = 0;
	FRESULT result = f_open(&fileHandler, filename, FA_CREATE_NEW);
	while (result==FR_EXIST){
		fileVersionsCounter++;
		strcpy(filename, basicFilename);
		strcat(filename, "_");
		itoa(fileVersionsCounter, filename+strlen(filename), 10);
		strcat(filename, FILE_EXTENSION);
		result = f_open(&fileHandler, filename, FA_CREATE_NEW);
	}

	if (result==FR_OK){
		fileOpened = 1;
	} else {
		//zrob cos zlego
	}

}

void saveFirstLine(){
	FRESULT result;
	UINT bytesWritten;
	for (uint16_t i=0; i<CHANNEL_NUMBER; i++){
		result = f_write(&fileHandler, DataTypes_fullName[i], strlen(DataTypes_fullName[i]), &bytesWritten);
		if (result!=FR_OK || bytesWritten!=strlen(DataTypes_fullName[i])){
			//zrob cos zlego
		}
		if (i+1<CHANNEL_NUMBER){
			result = f_write(&fileHandler, ",", strlen(","), &bytesWritten);
			if (result!=FR_OK || bytesWritten!=strlen(",")){
				//zrob cos zlego
			}
		}
	}
	result = f_write(&fileHandler, "\r\n", strlen("\r\n"), &bytesWritten);
	if (result!=FR_OK || bytesWritten!=strlen("\r\n")){
		//zrob cos zlego
	}
}

void SDCardSaver_saveAllUnsavedData(){
	FRESULT result;
	UINT bytesWritten;
	//TODO jakis mutex na danych
	uint16_t* toSaveData = SnapshotMaker_getLeftSnapshotPointer();
	while (toSaveData!=NULL){
		for (uint16_t i=0; i<CHANNEL_NUMBER; i++){
			itoa(toSaveData[i], buffer);
			result = f_write(&fileHandler, buffer, strlen(buffer), &bytesWritten);
			if (result!=FR_OK || bytesWritten!=strlen(DataTypes_fullName[i])){
				//zrob cos zlego
			}
		}
		result = f_write(&fileHandler, "\r\n", strlen("\r\n"), &bytesWritten);
		if (result!=FR_OK || bytesWritten!=strlen("\r\n")){
			//zrob cos zlego
		}
		SnapshotMaker_leftSnaphotReadNotification();
	}
}

void SDCardSaver_stopSaving(){
	FRESULT result = f_close(&fileHandler);
}
