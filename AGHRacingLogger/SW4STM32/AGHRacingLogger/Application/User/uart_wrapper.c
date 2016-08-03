#include "uart_wrapper.h"
#include "mxconstants.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "cmsis_os.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

uint8_t uart1_stopped = 1;

void UART2_TransmitData(volatile uint8_t* data, uint16_t size){
	HAL_UART_StateTypeDef state = huart2.gState;
	while ((state != HAL_UART_STATE_READY) && (state != HAL_UART_STATE_BUSY_RX)){
	  state = huart2.gState;
	} //TODO jakos zrobic zeby bylo non-blocking
	volatile HAL_StatusTypeDef status = HAL_UART_Transmit_DMA(&huart2, (uint8_t*)data, size);
	if (status!=HAL_OK){
	  while(1){
		  HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		  HAL_Delay(100);
	  }
	}
}

volatile uint8_t* ecuDataPointer;

void UART1_ReceiveDataFromECU_DMA_init(volatile uint8_t* ecuDataPointerArg){

	ecuDataPointer = ecuDataPointerArg;

	//
	HAL_StatusTypeDef status;
	uint8_t tmpData[5];
	do {
		status = HAL_UART_Receive(&huart1, tmpData, 1, 50);
		HAL_UART_IRQHandler(&huart1);
	} while ((status!=HAL_OK && status!=HAL_TIMEOUT) || (huart1.ErrorCode != HAL_UART_ERROR_NONE));

}


void UART1_ReceiveDataFromECU_DMA(){
	if (!uart1_stopped) return;
	HAL_UART_StateTypeDef state = huart1.gState;
	while ((state != HAL_UART_STATE_READY) && (state != HAL_UART_STATE_BUSY_TX)){
	  state = huart1.gState;
	}	//TODO jakos zrobic zeby bylo non-blocking

	/* Enable the UART Data Register not empty Interrupt */
//	HAL_UART_Receive(&huart1, (uint8_t*)ecuDataPointer, 1280, ECU_BUFFER_SIZE);//TODO bez tego z jakiegos powodu nie dziala :-/

	HAL_StatusTypeDef status = HAL_UART_Receive_DMA(&huart1, (uint8_t*)ecuDataPointer, ECU_BUFFER_SIZE);
	uart1_stopped = 0;
	__HAL_UART_CLEAR_FLAG(&huart1, UART_FLAG_RXNE);
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
	if (status!=HAL_OK){
	  while(1){
		  HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		  HAL_Delay(100);
	  }
	}
}

void UART1_ITEnable(){
	  __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
}

void UART1_ITDisable(){
	  __HAL_UART_DISABLE_IT(&huart1, UART_IT_RXNE);
}

void UART1_Pause(){
	HAL_StatusTypeDef status = HAL_UART_DMAPause(&huart1);
	if (status!=HAL_OK){//TODO
	  while(1){
		  HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		  HAL_Delay(100);
	  }
	}
}

void UART1_Resume(){
	HAL_StatusTypeDef status = HAL_UART_DMAResume(&huart1);
	if (status!=HAL_OK){
	  while(1){
		  HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		  HAL_Delay(100);
	  }
	}
}

void UART1_Stop(){
	if (uart1_stopped) return;
	UART1_ITDisable();
	HAL_StatusTypeDef status = HAL_UART_DMAStop(&huart1);
	if (status!=HAL_OK){
	  while(1){
		  HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		  HAL_Delay(100);
	  }
	}
	uart1_stopped = 1;
}
