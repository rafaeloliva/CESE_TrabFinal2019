/* Copyright 2014, Pablo Ridolfi (UTN-FRBA).
 * Copyright 2014, Juan Cecconi.
 * Copyright 2015-2017, Eric Pernia.
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * sapi3c_uart.c
 * Adapted for CL3 board: R.Oliva 06-2019 rev 4.8.19
 *
 */
/* Date: 2019-06-10 */

/*==================[inclusions]=============================================*/

#include "sapi3c_uart.h"
#include "string.h"


/*==================[macros]=================================================*/

/* on sapi3c_board.h */
/* typedef enum {
   UART_TER  = 0, // Hardware UART6 (RS232_2 connector - Terminal)
   UART_485  = 1, // Hardware UART1 via RS_485 A, B and GND Borns
   UART_2    = 2  // Hardware UART2 (RS232_1 connector or ESP8266)
   } uartMap_t;

typedef enum {
   BAUD_9600  = 0,  // Lowest Baud rate 9600
   BAUD_19200 ,     // Intermediate 19200
   BAUD_38400 ,     // For METEO
   BAUD_115200      // Highest 115200
   } uartBaudR_t;    */


/*==================[typedef]================================================*/

//-------------------------------------------------------------
// UART Initialization
bool_t uartInit( uartMap_t uart, uartBaudR_t baudR ){

bool_t error = 0;
uint32_t baudRate;
switch(baudR){
	case BAUD_9600:
	   baudRate = 9600;
	   break;
	case BAUD_19200:
	   baudRate = 19200;
	   break;
	case BAUD_38400:
	   baudRate = 38400;
	   break;
    case BAUD_115200:
	   baudRate = 115200;
	   break;	   
	default:
	   baudRate = 115200;
	   error = 1; 
	   break;	   
}
  LL_USART_InitTypeDef USART_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

/* USART1=UART_485 init function */
if( uart == UART_485 ) {
  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  /**USART1 GPIO Configuration  
  PA9   ------> USART1_TX
  PA10   ------> USART1_RX 
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_9|LL_GPIO_PIN_10;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USART1 interrupt Init */
  NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5, 0));
  NVIC_EnableIRQ(USART1_IRQn);

  USART_InitStruct.BaudRate = baudRate;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART1, &USART_InitStruct);
  LL_USART_ConfigAsyncMode(USART1);
  LL_USART_Enable(USART1);
}

else if (uart == UART_TER ){
  /* USART6 init function */
  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART6);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  /**USART6 GPIO Configuration  
  PC6   ------> USART6_TX
  PC7   ------> USART6_RX 
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_6|LL_GPIO_PIN_7;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_8;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USART6 interrupt Init */
  NVIC_SetPriority(USART6_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5, 0));
  NVIC_EnableIRQ(USART6_IRQn);

  USART_InitStruct.BaudRate = baudRate;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART6, &USART_InitStruct);
  LL_USART_ConfigAsyncMode(USART6);
  LL_USART_Enable(USART6);
}
else {
  /* UART2 not implem yet */	
  error = 1;	
}	
return(error);
}


// Prints message out on Terminal UART6 - blocking
// 18.4.2019 Use LL_USART functions as in STM32F4 LL_Examples
void printmsg_cl3(char *msg)
{
	for(uint32_t i=0; i < strlen(msg); i++)
	{
		while(!LL_USART_IsActiveFlag_TXE(USART6)){
			; // Wait forever
		}
		// while (USART_GetFlagStatus(USART6,USART_FLAG_TXE) != SET);
		LL_USART_TransmitData8(USART6,msg[i]);
	}

	while (!LL_USART_IsActiveFlag_TC(USART6)){
		;  // Wait again forever
	}

}

/*==================[internal data declaration]==============================*/

/*==================[end of file]============================================*/
