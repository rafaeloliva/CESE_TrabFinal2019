/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
  * @brief   This file Tests basic operations for CL3
  *          rev 4.8.19
  *
 **/  
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "sapi3c.h"


/**
  * @brief  main() - The application entry point.
  * @retval int
  */
int main(void)
{
  // CL3 board configuration
  boardInitCL3();

  while (1)
  {
    delay_cl3(500);
    gpioWrite(OLED_PB2, ON);
    delay_cl3(500);
    gpioWrite(OLED_PB2, OFF);
    
  }
}


