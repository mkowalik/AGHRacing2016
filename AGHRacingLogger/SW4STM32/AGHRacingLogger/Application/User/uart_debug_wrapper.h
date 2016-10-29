#ifndef __uart_debug_wrapper_H
#define __uart_debug_wrapper_H

#include "ecumaster.h"

/**
 * Used only for debug.
 */
void UART2_TransmitData(volatile uint8_t* data, uint16_t size);

#endif /* __uart_debug_wrapper_H */
