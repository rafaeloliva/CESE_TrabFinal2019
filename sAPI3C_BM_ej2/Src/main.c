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
  * @brief   Ej 02 This file Tests basic operations for CL3
  *          rev 4.8.19
  *
 **/  
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "sapi3c.h"

//global space for debug string
char usr_msg[100]={0};
bool_t valor = 1;


/**
  * @brief  main() - The application entry point.
  * @retval int
  */
int main(void)
{
  // CL3 board configuration
  boardInitCL3();
  
  // CL3 Terminal @UART 6, 115200 configuration
  uartConfig(UART_TER, BAUD_115200);
  
  sprintf(usr_msg,"\r\n Trabajo Final R.Oliva 2019 \r\n");
  printmsg_cl3(usr_msg); 
  
  while (1)
  {
    valor = !gpioRead(KBD_ABJ);
	if(valor) {
		sprintf(usr_msg,"\r\n Tecla Abajo Presionada");
        printmsg_cl3(usr_msg); 
	}
	HAL_Delay(500);
    gpioWrite(OLED_PB2, ON);
    HAL_Delay(500);
    gpioWrite(OLED_PB2, OFF);
    
  }
}


