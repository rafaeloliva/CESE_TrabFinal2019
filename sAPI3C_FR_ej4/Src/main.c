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
  * @brief   Ej 04 This file Tests FreeRTOS with sApi3c for CL3
  *          rev 12.8.19
  *
 **/  
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "sapi3c.h"
#include "FreeRTOSConfig.h"
#include "tareas.h"
#include "general.h"

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
  
  // CL3 METEO @UART 1, 38400 configuration
  uartConfig(UART_485, BAUD_38400);
  
  sprintf(usr_msg,"\r\n Trabajo Final R.Oliva 2019 \r\n");
  printmsg_cl3(usr_msg); 
  btest = displaycl3_Config(ILI9341);
  if(btest) {
	sprintf(usr_msg,"\r\n Error Init Display %d \r\n",btest);
    printmsg_cl3(usr_msg); 
  }
  displaycl3_Screen(WELCOME);
  
  // Initialize & Create Idle Task
  CL3_FREERTOS_Init();
  
  // Start Reception - Habilita Flags USARTs
  Start_Reception();

  // Queue and semaphore creation
  QueueAndSemCreateAll();

  // Task creation
  TaskCreateAll();
  
  // start the scheduler
  vTaskStartScheduler();
  
  while (1)
  {
  // Infinite loop    
  }
}




// Implementar localmente las ISR.. 22.4.19 14:00
// USART1_ISR R.Oliva 18.4.2019 moved to main 24.4.2019
// 27.4.2019 - Added FSM for start '$' and end '*' of packet detection
// adds global variable packet_started = 0;
void USART1_IRQHandler(void)
{
  	uint8_t data_byte;  // LL_ requiere 8 bit
	//a data byte is received from the user
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	// char dbg_msg[20];

	if( LL_USART_IsActiveFlag_RXNE(USART1) && LL_USART_IsEnabledIT_RXNE(USART1))
	{
		data_byte = LL_USART_ReceiveData8(USART1);
        // (A0) 27.4.2019 - Add startofpacket detection
		if((data_byte == '$' ) && (packet_started == 0)){
			packet_started = 1;
		    // Point (A)
		} else if (packet_started == 1){
			// Point (B1)
			packet_buffer[packet_len++] = data_byte;
			if((data_byte == '*' ) && (packet_len < PACKET_MAX)){
				{
				//then packet is ok.. (E1)
				packet_buffer[packet_len]= '\0';   // Null Terminate the string
				packet_started = 0;
				//notify the CheckMeteoHand task (to copy the buffer)
				xTaskNotifyFromISR(xTaskHandleChkMeteo,0,eNoAction,&xHigherPriorityTaskWoken);
				//reset the packet_len variable
				packet_len = 0;
				} // F1
			if (packet_len > PACKET_MAX){
				packet_len = 0;
				xTaskNotifyFromISR(xTaskHandlePrintErr,0,eNoAction,&xHigherPriorityTaskWoken);
			    }
			}   // End
		} // Point G1
	  }
	  // if the above freertos apis wake up any higher priority task, then yield the processor to the
	  //higher priority task which is just woken up.
      if(xHigherPriorityTaskWoken)
	  {
			taskYIELD();
	  }
}

void USART6_IRQHandler(void)
{
  /* USER CODE BEGIN USART6_IRQn 0 */
	uint8_t data_byte;  // LL_ requirese 8 bit
	//a data byte is received from the user
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	// char dbg_msg[20];

	if( LL_USART_IsActiveFlag_RXNE(USART6) && LL_USART_IsEnabledIT_RXNE(USART6))
		{

		// Former USART6_Reception_Callback();
		data_byte = LL_USART_ReceiveData8(USART6);

		#ifdef DEBUG_USART6B
		      sprintf(dbg_msg,"\r\n %c",data_byte);
		      printmsg(dbg_msg);
		#endif

		command_buffer[command_len++] = data_byte;

		if(data_byte == '\r')
			{
				//then user is finished entering the data
				//reset the command_len variable
				command_len = 0;

		        #ifdef DEBUG_USART6B
		          sprintf(dbg_msg,"\r\n NotCmh");
		          printmsg(dbg_msg);
			    #endif
				// Avisar al command handling task
				xTaskNotifyFromISR(xTaskHandleUart6CmdH,0,eNoAction,&xHigherPriorityTaskWoken);
		        // y despues al que imprime el menu.. 24.4.2019 dejar para el 0 de usuario..
				// xTaskNotifyFromISR(xTaskHandleDisplay,0,eNoAction,&xHigherPriorityTaskWoken);

			}
			#ifdef DEBUG_USART6B
				sprintf(dbg_msg,"\r\n NtCmHE");
				printmsg(dbg_msg);
			#endif
			// if the above freertos apis wake up any higher priority task, then yield the processor to the
			//higher priority task which is just woken up.
			if(xHigherPriorityTaskWoken)
			{
				taskYIELD();
			}


		}

}

