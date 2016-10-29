#include "error_logger.h"

void LOG_warning(char* warningString){

}

void LOG_error(char* errorString){
	while(1){
	  HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
	  HAL_Delay(100);
	}
}

void LOG_error_ifstatus(char* errorString, HAL_StatusTypeDef status){
	if (status!=HAL_OK){
		LOG_error(errorString);
	}
}
