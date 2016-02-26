#include "sd_card_saver.h"
//#include "stm32f4xx_hal_rtc.h"
#include "ff.h"
#include "data_snapshot_maker.h"
#include "itoa.h"
#include "string.h"

#define MAX_FILENAME_PREFIX_LENGTH	128
#define MAX_FILENAME_LENGTH			(MAX_FILENAME_PREFIX_LENGTH+26)
#define FILE_NAME_PREFIX			"AGHRT_Log_"
#define FILE_EXTENSION				".csv"

volatile static TCHAR filename[MAX_FILENAME_LENGTH+1];

FATFS SDCardHandler;
uint8_t fileOpened = 0;

static TCHAR buffer[50];

void SDCardSaver_init(){
	FRESULT result = f_mount(&SDCardHandler, "", 0);
	if (result!=FR_OK){
		//TODO zrob cos zlego
	}
}

void SDCardSaver_initNewFile(){
	/*RTC_TimeTypeDef *sTime;
	RTC_DateTypeDef *sDate;

	HAL_RTC_GetTime(NULL, sTime, FORMAT_BCD); //TODO RTC handler instead of NULL
	HAL_RTC_GetDate(NULL, sDate, FORMAT_BCD); //TODO RTC handler instead of NULL*/
//	strcpy((char*)filename, FILE_NAME_PREFIX);
	/*itoa(sDate->Year, filename+strlen(filename), 10);
	strcat(filename, "-");
	itoa(sDate->Month, filename+strlen(filename), 10);
	strcat(filename, "-");
	itoa(sDate->Date, filename+strlen(filename), 10);
	strcat(filename, "_");

	itoa(sTime->Hours, filename+strlen(filename), 10);
	strcat(filename, "_");
	itoa(sTime->Minutes, filename+strlen(filename), 10);
	strcat(filename, "_");
	itoa(sTime->Seconds, filename+strlen(filename), 10);*/
//	strcat((char*)filename, "2016-01-01_15-13");

	char basicFilename[MAX_FILENAME_LENGTH+1];
//	strcpy(basicFilename, (char*)filename);
//
//	strcat((char*)filename, FILE_EXTENSION);

	uint8_t fileVersionsCounter = 0;
	FIL fileHandler;
	FRESULT result = f_open(&fileHandler, filename, FA_READ|FA_WRITE|FA_CREATE_NEW);
	/*while (result==FR_EXIST){
		fileVersionsCounter++;
		strcpy((char*)filename, basicFilename);
		strcat((char*)filename, "_");
		itoa(fileVersionsCounter, (char*)(filename+strlen((char*)filename)));
		strcat((char*)filename, FILE_EXTENSION);
		result = f_open((FIL*)&fileHandler, (TCHAR*)filename, FA_CREATE_NEW);
	}

	if (result==FR_OK){
		fileOpened = 1;
	} else {
		//zrob cos zlego
	}
*/
}

void saveFirstLine(){
	/*FRESULT result;
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
	}*/
}

void SDCardSaver_saveAllUnsavedData(){
	/*FRESULT result;
	UINT bytesWritten;
	//TODO jakis mutex na danych
	volatile uint16_t* toSaveData = SnapshotMaker_getLeftSnapshotPointer();
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
	}*/
}

void SDCardSaver_stopSaving(){
	/*FRESULT result = f_close(&fileHandler);
	if (result!=FR_OK){
		//zrob cos zlego
	}*/
}
