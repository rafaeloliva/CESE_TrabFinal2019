/**
  ******************************************************************************
  * File Name          : sapi3c_gpio.h
  * Description        : This file contains all the functions prototypes for 
  *                      the gpio  
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
  * Adapted for CL3 board: R.Oliva 06-2019
  ******************************************************************************
  **/
  /**
  ******************************************************************************
  * @file    sapi3c_gpio.h
  * @author  E.Pernia / adapted by R.Oliva
  * @brief   This file holds gpio header info for CL3 - rev 4.8.19
  *          
  *
 **/

/* Date: 2019-06-10 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "sapi3c_datatypes.h"
#include "sapi3c_board.h"


void   gpioInitEnable(void);
bool_t gpioInitInput( inputMap_t input, uint32_t config_pull );
bool_t gpioInitOutput( outputMap_t output);
void   gpioInit_INT1(void);
bool_t gpioRead( inputMap_t input );
bool_t gpioWrite( outputMap_t output, bool_t value);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
