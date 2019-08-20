/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
  
  /**
  ******************************************************************************
  * @author  E.Pernia / adapted by R.Oliva
  * @brief   Header for Tests FreeRTOS with sApi3c for CL3
  *          rev 12.8.19
  *
 **/  
  

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_dma.h"

// de UART_LL_5 16.8.2019 
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "cmsis_os.h"

// Ej04 - 19.8.2019
#include "tareas.h"
#include "FreeRTOSConfig.h"
#include "general.h"



/* Private defines ----------------------------------------------------------*/
// de UART_LL_5 16.8.2019 - ya estan en sapi3c
//#define TRUE 1
//#define FALSE 0



// #define DEBUG_USART6
#define DEBUG_VERBOSE

/* USER CODE BEGIN PD */
// Nuevo Menu 21.4.19
#define TOG_DEMO_U1_SINCOMM_COMMAND 	1
#define TOG_DEMO_U1_LOOPBK_COMMAND 		2
#define TOG_LEE_U1_METEO_COMMAND 		3
#define RTC_READ_DATE_TIME_COMMAND 	    4


/* Typedefs - antes en main.c UA_LL_5 (movemos a general.h) */

/* Exported functions prototypes ---------------------------------------------*/
// moved to sapi3c_board.h / .c
// void Error_Handler(void);


/* Private defines -----------------------------------------------------------*/
// moved to sapi3c_board.h
// #define SPI_RES_Pin LL_GPIO_PIN_13
// .. etc.


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
