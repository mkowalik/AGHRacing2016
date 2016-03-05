#include "sd_card_saver.h"
#include "stm32f4xx_hal.h"
#include "ff.h"
#include "data_snapshot_maker.h"
#include "itoa.h"
#include "string.h"
#include "mxconstants.h"
#include "error_logger.h"
#include "current_data_provider.h"

#define MAX_FILENAME_PREFIX_LENGTH	128
#define MAX_FILENAME_LENGTH			(MAX_FILENAME_PREFIX_LENGTH+26)
#define FILE_NAME_PREFIX			"/AGHRT_Log_"
#define FILE_EXTENSION				".aghlog"

static TCHAR filename[MAX_FILENAME_LENGTH+1];

FATFS SDCardHandler;
static FIL fileHandler;

extern RTC_HandleTypeDef hrtc;
extern SD_HandleTypeDef hsd;

extern osMutexId currentDataMutexHandle;

void SDCardSaver_checkIferror(FRESULT result, char* comment){
	char buffer[20];
	if (result!=FR_OK){
		LOG_warning("SD Card Saver Error");
		itoa(result, buffer);
		LOG_warning(buffer);
		LOG_warning(comment);
		//TODO moze jakas inicjalizacja ponowna czy cos?
	}
}

void SDCardSaver_checkIferrorWithBytesWritten(FRESULT result, UINT bytesWritten, UINT bytesShouldBeWritten, char* comment){
	if (bytesWritten!=bytesShouldBeWritten){
		SDCardSaver_checkIferror(result==FR_OK ? FR_DISK_ERR : result, comment);
	}
	SDCardSaver_checkIferror(result, comment);
}

uint8_t SDCardSaver_isSDCardInSlot(){
	if (HAL_GPIO_ReadPin(SD_Card_Select_GPIO_Port, SD_Card_Select_Pin)==GPIO_PIN_SET){
		return FR_OK;
	}
	return FR_DISK_ERR;
}

FRESULT SDCardSaver_init(){
	FRESULT result = f_mount(&SDCardHandler, "", 0);
	SDCardSaver_checkIferror(result, "Error in init procedure.");
	if (result!=FR_OK) return result;
	result = SDCardSaver_isSDCardInSlot();
	SDCardSaver_checkIferror(result, "Insert SD Card to slot.");
	return result;
}

RTC_DateTypeDef actualDate(){
	static RTC_DateTypeDef sDate;
	HAL_RTC_GetDate(&hrtc, &sDate, FORMAT_BCD);
	return sDate;
}

RTC_TimeTypeDef actualTime(){
	static RTC_TimeTypeDef sTime;
	HAL_RTC_GetTime(&hrtc, &sTime, FORMAT_BCD);
	return sTime;
}


FRESULT saveFirstLine(){
	FRESULT result;
	UINT bytesWritten;
	HAL_Delay(1000);
	for (uint16_t i=0; i<CHANNEL_NUMBER; i++){
		result = f_write(&fileHandler, DataTypes_fullName[i], strlen(DataTypes_fullName[i]), &bytesWritten);
		SDCardSaver_checkIferrorWithBytesWritten(result, bytesWritten, strlen(DataTypes_fullName[i]), "Error while saving first line to file.");
		if (result!=FR_OK) return result;
		//HAL_Delay(100);
		if (i+1<CHANNEL_NUMBER){
			result = f_write(&fileHandler, ",", strlen(","), &bytesWritten);
			SDCardSaver_checkIferrorWithBytesWritten(result, bytesWritten, strlen(","), "Error while saving first line to file.");
			if (result!=FR_OK) return result;
		}
		//HAL_Delay(100);
	}
	result = f_write(&fileHandler, "\r\n", strlen("\r\n"), &bytesWritten);
	SDCardSaver_checkIferrorWithBytesWritten(result, bytesWritten, strlen("\r\n"), "Error while saving first line to file.");
	return result;
}


FRESULT SDCardSaver_initNewFile(){

	char basicFilename[MAX_FILENAME_LENGTH+1];
	RTC_TimeTypeDef sTime = actualTime();
	RTC_DateTypeDef sDate = actualDate();

	strcpy((char*)filename, FILE_NAME_PREFIX);
	itoa(sDate.Year, filename+strlen(filename));
	strcat(filename, "-");
	itoa(sDate.Month, filename+strlen(filename));
	strcat(filename, "-");
	itoa(sDate.Date, filename+strlen(filename));
	strcat(filename, "_");

	itoa(sTime.Hours, filename+strlen(filename));
	strcat(filename, "_");
	itoa(sTime.Minutes, filename+strlen(filename));
	strcat(filename, "_");
	itoa(sTime.Seconds, filename+strlen(filename));

	strcpy(basicFilename, (char*)filename);
	strcat((char*)filename, FILE_EXTENSION);

	HAL_Delay(10);//TODO
//	HAL_SD_TransferStateTypedef tmp1 = HAL_SD_GetStatus(&hsd);
	FRESULT result = f_open((FIL*)&fileHandler, (TCHAR*)filename, (FA_READ|FA_WRITE|FA_CREATE_NEW));
	for (uint8_t versionCounter=0; result==FR_EXIST; versionCounter++){
		strcpy((char*)filename, basicFilename);
		strcat((char*)filename, "_");
		itoa(versionCounter, (char*)(filename+strlen((char*)filename)));
		strcat((char*)filename, FILE_EXTENSION);

//		HAL_SD_TransferStateTypedef tmp3 = HAL_SD_GetStatus(&hsd);
		result = f_open((FIL*)&fileHandler, (TCHAR*)filename, (FA_READ|FA_WRITE|FA_CREATE_NEW));
	}


//	HAL_SD_TransferStateTypedef tmp2 = HAL_SD_GetStatus(&hsd);

	SDCardSaver_checkIferror(result, "Error while opening file.");
	if (result!=FR_OK) return result;

	HAL_SD_TransferStateTypedef tmp = HAL_SD_GetStatus(&hsd);

	result = saveFirstLine();

	return result;
}


FRESULT SDCardSaver_saveAllUnsavedData(){
	FRESULT result=0;
	UINT bytesWritten;
	char buffer[20];

	/** Take mutex for current data **/
	if (osMutexWait(currentDataMutexHandle, 500)!=osOK){
		LOG_warning("Error (timeout probably) while waiting for mutex for current data in sd_card_saver.");
		return FR_DISK_ERR;
	}

	volatile uint16_t* toSaveData = SnapshotMaker_getLeftSnapshotPointer();
	while (toSaveData!=NULL){
		for (uint16_t i=0; i<CHANNEL_NUMBER; i++){
			itoa(toSaveData[i], buffer);
			result = f_write(&fileHandler, buffer, strlen(buffer), &bytesWritten);
			SDCardSaver_checkIferrorWithBytesWritten(result, bytesWritten, strlen(buffer), "Error while saving snapshot data");
			if (result!=FR_OK) {
				return result;
			}
			if (i+1<CHANNEL_NUMBER){
				result = f_write(&fileHandler, ",", strlen(","), &bytesWritten);
				SDCardSaver_checkIferrorWithBytesWritten(result, bytesWritten, strlen(","), "Error while saving first line to file.");
				if (result!=FR_OK) {
					return result;
				}
			}
		}
		result = f_write(&fileHandler, "\r\n", strlen("\r\n"), &bytesWritten);
		SDCardSaver_checkIferrorWithBytesWritten(result, bytesWritten, strlen("\r\n"), "Error while saving snapshot data");
		if (result!=FR_OK) {
			return result;
		}
		SnapshotMaker_leftSnaphotReadNotification();
		toSaveData = SnapshotMaker_getLeftSnapshotPointer();
	}

	/** Release mutex for current data **/
	if (osMutexRelease(currentDataMutexHandle)!=osOK){
		LOG_warning("Error while releasing mutex for current data in sd_card_saver.");
		return FR_DISK_ERR;
	}

	return result;
}

FRESULT SDCardSaver_stopSaving(){
	FRESULT result = f_close(&fileHandler);
	SDCardSaver_checkIferror(result, "Error while closing file.");
	return result;
}

uint8_t SDCardSaver_shouldRecordData(){

	uint8_t val = 1;//TODO FOR DEBUG
	return val;//TODO FOR DEBUG

	uint16_t value;
	static uint8_t ret = 0;

	/** Take mutex for current data **/
	if (osMutexWait(currentDataMutexHandle, 500)!=osOK){
		LOG_warning("Error (timeout probably) while waiting for mutex for current data in data_snapshot_maker.");
		return ret;
	}

	value = getCurrentData()[TRIGGER_CHANNEL];

	/** Release mutex for current data **/
	if (osMutexRelease(currentDataMutexHandle)!=osOK){
		LOG_warning("Error while releasing mutex for current data in data_snapshot_maker.");
		return ret;
	}

	if (value>TRIGGER_VALUE_GREATHER_THEN){
		return 1;
	}
	return 0;
}

