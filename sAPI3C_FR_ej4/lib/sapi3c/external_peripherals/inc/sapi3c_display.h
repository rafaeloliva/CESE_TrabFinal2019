/**
  ******************************************************************************
  * File Name          : sapi3c_display.h
  * Description        : This file contains all the functions prototypes for 
  *                      the Display on CL3
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
  * Adapted for CL3 board: R.Oliva 07-2019
  ******************************************************************************
  **/
  /**
  ******************************************************************************
  * @file    sapi3c_display.h
  * @author  R.Oliva
  * @brief   This file holds header info for CL3 display - rev 4.8.19
  *          Uses SPI1 module, requires HAL SPI1 module initialization
  *
 **/

/* Date: 2019-06-10 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DISPLAY_H
#define __DISPLAY_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "sapi3c_datatypes.h"
#include "sapi3c_board.h"

 // Required for SPI - ILI941 12.8.19
#include <stdarg.h>
#include "ili9341.h"
#include "ili9341_touch.h"
#include "fonts.h"

// #include "testimg.h"


typedef enum {
   ILI9341 = 0, // Default Display
   DISP2,       // Alternative 2
   DISP3        // Alternative 3
   } display_t;

typedef enum {
   WELCOME = 0,   // Default Welcome Screen
   SCREEN1,       // Alternative Screen 1
   SCREEN2,       // Alternative Screen 2
   SCREEN3,       // Alternative Screen 3
   SCREEN4        // Alternative Screen 3
   } screen_t;

extern SPI_HandleTypeDef hspi1;
   
uint8_t displaycl3_Config(display_t distype);
uint8_t displaycl3_Screen(screen_t screen);
void CL3_SPI1_Init(void);


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
