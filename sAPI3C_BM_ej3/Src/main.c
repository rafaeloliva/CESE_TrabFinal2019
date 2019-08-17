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
  * @brief   Ej 03 This file Tests UART+Display for CL3
  *          rev 10.8.19
  *
 **/  
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "sapi3c.h"

#define MAX_LOOPS 15
//global space for debug string
char usr_msg[100]={0};
bool_t  valor = 1;
uint8_t btest = 0;
uint8_t loop_count = MAX_LOOPS;

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
  btest = displaycl3_Config(ILI9341);
  if(btest) {
	sprintf(usr_msg,"\r\n Error Init Display %d \r\n",btest);
    printmsg_cl3(usr_msg); 
  }
  displaycl3_Screen(WELCOME);
  
  while (1)
  {
    valor = !gpioRead(KBD_IZQ);
	if(valor) {
    	sprintf(usr_msg,"\r\n Tecla Izquierda Presionada (F1)");
	    printmsg_cl3(usr_msg);
	    displaycl3_Screen(SCREEN1);
	}
    valor = !gpioRead(KBD_ARR);
	if(valor) {
		sprintf(usr_msg,"\r\n Tecla Arriba Presionada (F2)");
        printmsg_cl3(usr_msg);
		displaycl3_Screen(SCREEN2);
	}
	valor = !gpioRead(KBD_ABJ);
	if(valor) {
		sprintf(usr_msg,"\r\n Tecla Abajo Presionada (F3)");
        printmsg_cl3(usr_msg); 
		displaycl3_Screen(SCREEN3);
	}
    valor = !gpioRead(KBD_DER);
	if(valor) {
		sprintf(usr_msg,"\r\n Tecla Derecha Presionada (F4)");
        printmsg_cl3(usr_msg);
		displaycl3_Screen(SCREEN4);
	}

	HAL_Delay(500);
    gpioWrite(OLED_PB2, ON);
    HAL_Delay(500);
    gpioWrite(OLED_PB2, OFF);
	if(--loop_count == 0){
		loop_count = MAX_LOOPS;
		displaycl3_Screen(WELCOME);
	}
    
  }
}


