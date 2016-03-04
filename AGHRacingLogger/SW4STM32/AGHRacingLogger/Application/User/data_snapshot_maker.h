#ifndef __data_snapshot_maker_H
#define __data_snapshot_maker_H

#include <stdint.h>

#define MAX_SNAPSHOT_NUMBER 10

void SnapshotMaker_makeSnapshot();
volatile uint16_t* SnapshotMaker_getLeftSnapshotPointer();
void SnapshotMaker_leftSnaphotReadNotification();

#endif /* __data_snapshot_maker_H */
