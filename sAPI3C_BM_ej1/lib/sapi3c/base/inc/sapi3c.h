/* Copyright 2015-2017, Eric Pernia.
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
 *
 * sapi3c.h
 * Adapted for CL3 board: R.Oliva 06-2019 - rev 4.8.19
 *
 */

/* Date: 2019-06-10 */

#ifndef _SAPI_H_
#define _SAPI_H_

/*==================[inclusions]=============================================*/

#include "sapi3c_datatypes.h"

// Peripheral Drivers

#include "sapi3c_board.h"                  // Use clock peripheral

#include "sapi3c_gpio.h"                   // Use GPIO peripherals
#include "sapi3c_delay.h"                  // Use embd module

#ifdef SECOND_TEST
#include "sapi3c_uart.h"                   // Use UART peripherals
#include "sapi3c_adc.h"                    // Use ADC1 peripheral
#include "sapi3c_i2c.h"                    // Use I2C1 peripheral
#include "sapi3c_spi.h"                    // Use SPI1 peripheral
#include "sapi3c_rtc.h"                    // Use RTC peripheral


// High Level drivers

#include "sapi3c_stdio.h"                  // Use sapi_uart module

#include "sapi3c_consolePrint.h"           // Use sapi_print module

#include "sapi3c_convert.h"                // Use <string.h>


#include "sapi3c_circularBuffer.h"         // It has no dependencies

// External Peripheral Drivers

#include "sapi3c_keypad.h"                 // Use sapi_gpio and sapi_delay modules
#include "sapi3c_ili9341.h"                // Use sapi_gpio peripherals

// #include "sapi_esp8266.h"                // Use sapi_uart module

#endif



/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* #ifndef _SAPI_H_ */
