/**
  ******************************************************************************
  * @file    LIB_Config.h
  * @author  Waveshare Team
  * @version 
  * @date    13-October-2014
  * @brief     This file provides configurations for low layer hardware libraries.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WAVESHARE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _USE_LIB_CONFIG_H_
#define _USE_LIB_CONFIG_H_
//Macro Definition

/* Includes ------------------------------------------------------------------*/
//#include "MacroAndConst.h"

/*------------------------------------------------------------------------------------------------------*/
//SSD1306
#include "SSD1306.h"
#include "Fonts.h"
#include "mxconstants.h"
#include "stm32f4xx_hal.h"

extern SPI_HandleTypeDef hspi1;

#define SH1106
//#define SSD1306

#define INTERFACE_4WIRE_SPI     //4-wire SPI 

#define __SSD1306_CS_SET()      HAL_GPIO_WritePin(OLED_ChipSelect_GPIO_Port, OLED_ChipSelect_Pin, GPIO_PIN_SET);
#define __SSD1306_CS_CLR()      HAL_GPIO_WritePin(OLED_ChipSelect_GPIO_Port, OLED_ChipSelect_Pin, GPIO_PIN_RESET);

#define __SSD1306_RES_SET()     HAL_GPIO_WritePin(OLED_RESET_GPIO_Port, OLED_RESET_Pin, GPIO_PIN_SET);
#define __SSD1306_RES_CLR()     HAL_GPIO_WritePin(OLED_RESET_GPIO_Port, OLED_RESET_Pin, GPIO_PIN_RESET);

#define __SSD1306_DC_SET()      HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_SET);
#define __SSD1306_DC_CLR()      HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_RESET);

#define  __SSD1306_WRITE_BYTE(DATA)		HAL_SPI_Transmit(&hspi1, &DATA, 1, 10);
/*------------------------------------------------------------------------------------------------------*/


#endif

/*-------------------------------END OF FILE-------------------------------*/

