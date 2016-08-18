#ifndef __sd_card_saver_H
#define __sd_card_saver_H

#include "logged_data_types.h"
#include "ff.h"

#define TRIGGER_CHANNEL ECU_RPM
#define TRIGGER_VALUE_GREATHER_THEN	0

FRESULT SDCardSaver_init();
FRESULT SDCardSaver_initNewFile();
FRESULT SDCardSaver_saveAllUnsavedData();
FRESULT SDCardSaver_stopSaving();
uint8_t SDCardSaver_shouldRecordData();

#endif /* __sd_card_saver_H */
