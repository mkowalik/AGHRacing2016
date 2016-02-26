#include "uart_wrapper.h"
#include "mxconstants.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "cmsis_os.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

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

void UART1_ReceiveDataFromECU_DMA(volatile uint8_t* ecuData){
	  HAL_UART_StateTypeDef state = huart1.gState;
	  while ((state != HAL_UART_STATE_READY) && (state != HAL_UART_STATE_BUSY_TX)){
		  state = huart1.gState;
	  }	//TODO jakos zrobic zeby bylo non-blocking

	    /* Enable the UART Data Register not empty Interrupt */
	  HAL_StatusTypeDef status = HAL_UART_Receive_DMA(&huart1, (uint8_t*)ecuData, ECU_BUFFER_SIZE);
	  __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
	  if (status!=HAL_OK){
		  while(1){
			  HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
			  HAL_Delay(100);
		  }
	  }
}
