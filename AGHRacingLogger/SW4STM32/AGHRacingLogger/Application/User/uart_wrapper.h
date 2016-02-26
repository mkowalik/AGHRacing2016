#include "ecumaster.h"

void UART2_TransmitData(volatile uint8_t* data, uint16_t size);
void UART1_ReceiveDataFromECU_DMA(volatile uint8_t* ecuData);
