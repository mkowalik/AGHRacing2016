#include "data_snapshot_maker.h"
#include "current_data_provider.h"
#include "logged_data_types.h"
#include "current_data_provider.h"
#include "cmsis_os.h"
#include "itoa.h"
#include "mxconstants.h"
#include "error_logger.h"
#include "stm32f4xx_hal.h"
#include <stddef.h>

volatile uint16_t makedSnapshots[MAX_SNAPSHOT_NUMBER][CHANNEL_NUMBER];
static volatile uint8_t leftPointer = 0;
static volatile uint8_t rightPointer = 0;

extern osMutexId currentDataMutexHandle;

void SnapshotMaker_makeSnapshot(){
	if ((rightPointer-leftPointer) > MAX_SNAPSHOT_NUMBER) return; //if not free placeholder skip data
    HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);//TODO DEBUG

	volatile uint16_t* currentDataPointer = getCurrentData();

	/** Take mutex for current data **/
	if (osMutexWait(currentDataMutexHandle, 10)!=osOK){
		LOG_warning("Error (timeout probably) while waiting for mutex for current data in data_snapshot_maker.");
		return;
	}

	for (int i=0; i<CHANNEL_NUMBER; i++){
		makedSnapshots[rightPointer%MAX_SNAPSHOT_NUMBER][i] = currentDataPointer[i];
	}

	rightPointer++;

	/** Release mutex for current data **/
	if (osMutexRelease(currentDataMutexHandle)!=osOK){
		LOG_warning("Error while releasing mutex for current data in data_snapshot_maker.");
	}

	if (leftPointer>MAX_SNAPSHOT_NUMBER && rightPointer>MAX_SNAPSHOT_NUMBER){
		leftPointer-=MAX_SNAPSHOT_NUMBER;
		rightPointer-=MAX_SNAPSHOT_NUMBER;
	}
}

volatile uint16_t* SnapshotMaker_getLeftSnapshotPointer(){
	if (leftPointer < rightPointer){
		return makedSnapshots[leftPointer%MAX_SNAPSHOT_NUMBER];
	} else {
		return NULL;
	}
}

void SnapshotMaker_leftSnaphotReadNotification(){
	leftPointer++;
}
