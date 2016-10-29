#ifndef __data_snapshot_maker_H
#define __data_snapshot_maker_H

#include <stdint.h>

#define MAX_SNAPSHOT_NUMBER 10

/**
 * This function saves all actual data from sensors as it is to MAX_SNAPSHOT_NUMBER -size buffer which should be saved to SD card.
 */
void SnapshotMaker_makeSnapshot();

/**
 * Returns pointer to oldest not-saved snapshot.
 */
volatile uint16_t* SnapshotMaker_getLeftSnapshotPointer();

/**
 * This function increases pointer to oldest snapshot, and allows it to be deleted.
 */
void SnapshotMaker_leftSnaphotReadNotification();

#endif /* __data_snapshot_maker_H */
