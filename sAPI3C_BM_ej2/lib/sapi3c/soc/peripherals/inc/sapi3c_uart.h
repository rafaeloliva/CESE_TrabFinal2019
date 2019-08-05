/* Copyright 2015-2018, Eric Pernia.
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
 * sapi3c_uart.h
 * Adapted for CL3 board: R.Oliva 06-2019 rev 4.8.19
 *
 */
/* Date: 2019-06-10 */

#ifndef _SAPI_UART_H_
#define _SAPI_UART_H_

/*==================[inclusions]=============================================*/

#include "sapi3c_board.h"
#include "sapi3c_datatypes.h"



/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

#define uartConfig uartInit

/*==================[typedef]================================================*/

/* In sapi3c_board.h */ 
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
   } uartBaudR_t;    
   
 Typical use: uartConfig(UART_TER, BAUD_115200);
 */
   
 
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

//-------------------------------------------------------------
// UART Initialization
bool_t uartInit( uartMap_t uart, uartBaudR_t baudR);

// Prints Debug message out on Terminal - UART6..
// 18.4.2019 Use LL_USART functions as in STM32F4 LL_Examples
void printmsg_cl3(char *msg);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _SAPI_UART_H_ */
