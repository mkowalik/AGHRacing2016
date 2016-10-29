#ifndef __error_logger_H
#define __error_logger_H

#include "mxconstants.h"
#include "stm32f4xx_hal.h"

/**
 * Function for logging warnings.
 * TODO Not implemented yet.
 */
void LOG_warning(char* warningString);

/**
 * Function for logging errors. Stops working of MCU
 * TODO Not implemented yet. Starts to blinking LED.
 */
void LOG_error(char* errorString);

/**
 * Function for logging errors. Goes into only if status!=HAL_OK. Stops working of MCU
 * TODO Not implemented yet. Starts to blinking LED.
 */
void LOG_error_ifstatus(char* errorString, HAL_StatusTypeDef status);

#endif /* __error_logger_H */
