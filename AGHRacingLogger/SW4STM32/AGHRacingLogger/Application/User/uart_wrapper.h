#ifndef __uart_wrapper_H
#define __uart_wrapper_H

#include "ecumaster.h"

void UART2_TransmitData(volatile uint8_t* data, uint16_t size);
void UART1_ReceiveDataFromECU_DMA_init(volatile uint8_t* ecuDataPointerArg);
void UART1_ReceiveDataFromECU_DMA();

void UART1_ITEnable();
void UART1_ITDisable();

void UART1_Pause();
void UART1_Resume();
void UART1_Stop();

#endif /* __uart_wrapper_H */
