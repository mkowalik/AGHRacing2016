#ifndef __error_logger_H
#define __error_logger_H

#include "mxconstants.h"
#include "stm32f4xx_hal.h"

void LOG_warning(char* warningString);
void LOG_error(char* errorString);
void LOG_error_ifstatus(char* errorString, HAL_StatusTypeDef status);

#endif /* __error_logger_H */
