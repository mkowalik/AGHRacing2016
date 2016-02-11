#include "data_snapshot_maker.h"
#include "current_data_provider.h"
#include "logged_data_types.h"
#include "current_data_provider.h"

volatile uint16_t makedSnapshots[MAX_SNAPSHOT_NUMBER][CHANNEL_NUMBER];
static volatile uint8_t leftPointer = 0;
static volatile uint8_t rightPointer = 0;

void SnapshotMaker_makeSnapshot(){
	if (leftPointer>=rightPointer) return; //if not free placeholder skip data

	volatile uint16_t* currentDataPointer = getCurrentData();

	//TODO jakiœ mutex na actual data by sie przydal
	for (int i=0; i<CHANNEL_NUMBER; i++){
		makedSnapshots[rightPointer][i] = currentDataPointer[i];
	}
	rightPointer++;
	//TODO zwolnic mutex

	if (leftPointer>MAX_SNAPSHOT_NUMBER && rightPointer>MAX_SNAPSHOT_NUMBER){
		leftPointer-=MAX_SNAPSHOT_NUMBER;
		rightPointer-=MAX_SNAPSHOT_NUMBER;
	}
}

volatile uint16_t* SnapshotMaker_getLeftSnapshotPointer(){
	return makedSnapshots[leftPointer];
}

void SnapshotMaker_leftSnaphotReadNotification(){
	leftPointer++;
}
