//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "stm32f0xx_hal.h"
#include "can.h"

// ----------------------------------------------------------------------------
//
// Standalone STM32F0 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

CanTxMsgTypeDef tx_msg;

volatile bool gear_up_flag = false, gear_down_flag = false,
		clutch_on_flag = false, clutch_off_flag = false,
		send_neutral_flag = false;
const volatile uint32_t CUT_TIME = 100,
		VALVE_UP_TIME = 80,
		GEAR_CLUTCH_TIME = 60,
		GEAR_AFTER_CLUTCH_TIME = 40,
		GEAR_SW_DELAY = 200,
		CLUTCH_SW_DELAY = 400;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

int
main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed.


	  tx_msg.IDE = CAN_ID_STD;
	  tx_msg.StdId = 100;
	  tx_msg.RTR = CAN_RTR_DATA;
	  tx_msg.DLC = 1;
	  hcan.pTxMsg = &tx_msg;


	uint32_t prev_tick = 0;

  while (1)
  {
	  uint32_t curr_tick = HAL_GetTick();
	  if(prev_tick > HAL_GetTick())
	  {
		  uint32_t tick_diff = ((2^32)-1) - prev_tick;
		  if(curr_tick + tick_diff > 100) send_neutral_flag = true;
	  } else if(curr_tick > prev_tick + 100) send_neutral_flag = true;

	  if(send_neutral_flag)
	  {
		  tx_msg.Data[0] = HAL_GPIO_ReadPin(NEUTRAL_IN_GPIO_Port, NEUTRAL_IN_Pin) ? 0x00 : 0xFF;
		  //HAL_CAN_Transmit(&hcan, 20);

		  send_neutral_flag = false;
	  }

	  if(gear_up_flag)
	  {
		  // Ignition cut and gear change (No neutral - PIN HIGH)
		  if(HAL_GPIO_ReadPin(NEUTRAL_IN_GPIO_Port, NEUTRAL_IN_Pin))
		  {
			  HAL_GPIO_WritePin(GEAR_CUT_GPIO_Port, GEAR_CUT_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GEAR_UP_OUT_GPIO_Port, GEAR_UP_OUT_Pin, GPIO_PIN_SET);

			  // Gear up wait time
			  HAL_Delay(VALVE_UP_TIME);
			  HAL_GPIO_WritePin(GEAR_UP_OUT_GPIO_Port, GEAR_UP_OUT_Pin, GPIO_PIN_RESET);


			  HAL_Delay(CUT_TIME - VALVE_UP_TIME);
			  HAL_GPIO_WritePin(GEAR_CUT_GPIO_Port, GEAR_CUT_Pin, GPIO_PIN_RESET);

			  HAL_Delay(GEAR_SW_DELAY - CUT_TIME);


		  }
		  // Gear change w/o ignition cut (from neutral)
		  else
		  {
			  HAL_GPIO_WritePin(GEAR_UP_OUT_GPIO_Port, GEAR_UP_OUT_Pin, GPIO_PIN_SET);
			  HAL_Delay(VALVE_UP_TIME);
			  HAL_GPIO_WritePin(GEAR_UP_OUT_GPIO_Port, GEAR_UP_OUT_Pin, GPIO_PIN_RESET);

			  HAL_Delay(GEAR_SW_DELAY - VALVE_UP_TIME);
		  }


		  gear_up_flag = false;

	  } else if(gear_down_flag)
	  {

		  // Clutch and gear down
		  HAL_GPIO_WritePin(CLUTCH_OUT_GPIO_Port, CLUTCH_OUT_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GEAR_DOWN_OUT_GPIO_Port, GEAR_DOWN_OUT_Pin, GPIO_PIN_SET);
		  HAL_Delay(GEAR_CLUTCH_TIME);

		  // Clutch off, gear still on
		  HAL_GPIO_WritePin(CLUTCH_OUT_GPIO_Port, CLUTCH_OUT_Pin, GPIO_PIN_RESET);
		  HAL_Delay(GEAR_AFTER_CLUTCH_TIME);

		  // Gear off
		  HAL_GPIO_WritePin(GEAR_DOWN_OUT_GPIO_Port, GEAR_DOWN_OUT_Pin, GPIO_PIN_RESET);

		  HAL_Delay(GEAR_SW_DELAY - GEAR_CLUTCH_TIME - GEAR_AFTER_CLUTCH_TIME);
		  gear_down_flag = false;

	  } else if(clutch_on_flag)
	  {
		  HAL_GPIO_WritePin(CLUTCH_OUT_GPIO_Port, CLUTCH_OUT_Pin, GPIO_PIN_SET);

		  HAL_Delay(CLUTCH_SW_DELAY);
		  clutch_on_flag = false;

	  } else if(clutch_off_flag)
	  {
		  HAL_GPIO_WritePin(CLUTCH_OUT_GPIO_Port, CLUTCH_OUT_Pin, GPIO_PIN_RESET);

		  HAL_Delay(CLUTCH_SW_DELAY);
		  clutch_off_flag = false;

	  }

  }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		__HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_CC1OF);

		if(HAL_GPIO_ReadPin(CLUTCH_TIM_GPIO_Port, CLUTCH_TIM_Pin))
			clutch_off_flag = true;
		else
			clutch_on_flag = true;
	} else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
	{
		__HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_CC2OF);

		gear_down_flag = true;
	} else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
	{
		__HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_CC3OF);

		gear_up_flag = true;
	}

}

#pragma GCC diagnostic pop
