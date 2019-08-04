/* Copyright 2015-2016, Eric Pernia.
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
 * sapi3c_board.h
 * Adapted for CL3 board: R.Oliva 06-2019 rev 4.8.19
 *
 */
/* Date: 2019-06-10 */

#ifndef _SAPI_BOARD_H_
#define _SAPI_BOARD_H_

/*==================[inclusions]=============================================*/

#include "sapi3c_datatypes.h"
/* Includes ------------------------------------------------------------------*/
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


/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

#define boardConfigCL3 boardInitCL3

/* Private defines -----------------------------------------------------------*/
#define SPI_RES_Pin LL_GPIO_PIN_13
#define SPI_RES_GPIO_Port GPIOC
#define AN10_PC0_Pin LL_GPIO_PIN_0
#define AN10_PC0_GPIO_Port GPIOC
#define AN11_PC1_Pin LL_GPIO_PIN_1
#define AN11_PC1_GPIO_Port GPIOC
#define AN12_PC2_Pin LL_GPIO_PIN_2
#define AN12_PC2_GPIO_Port GPIOC
#define AN13_PC3_Pin LL_GPIO_PIN_3
#define AN13_PC3_GPIO_Port GPIOC
#define PA0_EN_EXP_PW_Pin LL_GPIO_PIN_0
#define PA0_EN_EXP_PW_GPIO_Port GPIOA
#define PA1_EN_LCD_PW_Pin LL_GPIO_PIN_1
#define PA1_EN_LCD_PW_GPIO_Port GPIOA
#define AN4_PA4_Pin LL_GPIO_PIN_4
#define AN4_PA4_GPIO_Port GPIOA
#define AN5_PA5_Pin LL_GPIO_PIN_5
#define AN5_PA5_GPIO_Port GPIOA
#define AN6_PA6_Pin LL_GPIO_PIN_6
#define AN6_PA6_GPIO_Port GPIOA
#define AN7_PA7_Pin LL_GPIO_PIN_7
#define AN7_PA7_GPIO_Port GPIOA
#define K_IZQ_PC4_Pin LL_GPIO_PIN_4
#define K_IZQ_PC4_GPIO_Port GPIOC
#define K_ARR_PC5_Pin LL_GPIO_PIN_5
#define K_ARR_PC5_GPIO_Port GPIOC
#define K_ABJ_PB0_Pin LL_GPIO_PIN_0
#define K_ABJ_PB0_GPIO_Port GPIOB
#define K_DER_PB1_Pin LL_GPIO_PIN_1
#define K_DER_PB1_GPIO_Port GPIOB
#define OLED_Pin LL_GPIO_PIN_2
#define OLED_GPIO_Port GPIOB
#define RS485_DE_Pin LL_GPIO_PIN_10
#define RS485_DE_GPIO_Port GPIOB
#define LCD_DATA_Pin LL_GPIO_PIN_12
#define LCD_DATA_GPIO_Port GPIOB
#define LCD_CLK_Pin LL_GPIO_PIN_13
#define LCD_CLK_GPIO_Port GPIOB
#define SPI_CS_Pin LL_GPIO_PIN_14
#define SPI_CS_GPIO_Port GPIOB
#define SPI_DC_Pin LL_GPIO_PIN_15
#define SPI_DC_GPIO_Port GPIOB
#define INT1_N_Pin LL_GPIO_PIN_15
#define INT1_N_GPIO_Port GPIOA
#define SD_INS_Pin LL_GPIO_PIN_10
#define SD_INS_GPIO_Port GPIOC
#define SDIO_CD_Pin LL_GPIO_PIN_11
#define SDIO_CD_GPIO_Port GPIOC
#define SPI_CLK_Pin LL_GPIO_PIN_3
#define SPI_CLK_GPIO_Port GPIOB
#define SPI_MISO_Pin LL_GPIO_PIN_4
#define SPI_MISO_GPIO_Port GPIOB
#define SPI_MOSI_Pin LL_GPIO_PIN_5
#define SPI_MOSI_GPIO_Port GPIOB
#define PB8_EN_IOT_PW_Pin LL_GPIO_PIN_8
#define PB8_EN_IOT_PW_GPIO_Port GPIOB
#define PB9_EN_SER_PWR_Pin LL_GPIO_PIN_9
#define PB9_EN_SER_PWR_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
/*==================[typedef]================================================*/

/* Defined for sapi3c_uart.h */

typedef enum {
   UART_TER  = 0, // Hardware UART6 (RS232_2 connector - Terminal)
   UART_485  = 1, // Hardware UART1 via RS_485 A, B and GND Borns
   UART_2    = 2  // Hardware UART2 (RS232_1 connector or ESP8266)
   } uartMap_t;

typedef enum {
   KBD_ABJ    = 0,  // K_ABJ_PB0_Pin 
   KBD_DER    = 1,  // K_DER_PB1_Pin 
   KBD_IZQ    = 2,  // K_IZQ_PC4_Pin
   KBD_ARR    = 3,  // K_ARR_PC5_Pin
   SDIO_CD    = 4,  // SDIO_CD_Pin_PC11 (former CS)
   SDIO_INS   = 5   // SD_INS_Pin_PC10
} inputMap_t;



//  CL3_Board output map 
//  LL_GPIO_ResetOutputPin(GPIOA, PA0_EN_EXP_PW_Pin|PA1_EN_LCD_PW_Pin);
//  LL_GPIO_ResetOutputPin(GPIOB, OLED_Pin = PB.2
//  |PB8_EN_IOT_PW_Pin
//  |PB9_EN_SER_PWR_Pin);
//  |RS485_DE_Pin = PB.10
//  |LCD_DATA_Pin = PB.12
//  |LCD_CLK_Pin = PB.13
//  |SPI_CS_Pin = oldLCD_E =PB.14
//  |SPI_DC_Pin = oldLCD_BL =PB.15
//  LL_GPIO_ResetOutputPin(GPIOC, SPI_RES_Pin); oldSD_WREN  = PC.13

typedef enum {
   EXP_PW_PA0   = 0,   // PA0_EN_EXP_PW_Pin 
   LCD_PW_PA1   ,      // PA1_EN_LCD_PW_Pin
   OLED_PB2     ,      // PB2_OLED_Pin
   IOT_PW_PB8   ,      // PB8_EN_IOT_PW_Pin
   SER_PW_PB9   ,      // PB9_EN_SER_PWR_Pin
   RS485_DE_PB10,      // PB10_RS485_DE_Pin
   LCD_CLK_PB12 ,      // PB12_LCD_CLK_pin
   LCD_DATA_PB13,      // PB13_LCD_DATA_pin
   SPI_CS_PB14  ,      // PB14_(exLDC_E)_SPI_CS_Pin
   SPI_DC_PB15  ,      // PB15_(exLDC_BL)_SPI_DC_Pin
   SPI_RES_PC13        // PC13_(exSD_WREN)_SPI_RES_Pin 
} outputMap_t;

   

/*==================[external data declaration]==============================*/
/*==================[external functions declaration]=========================*/

void boardInitCL3(void);
void SystemClock_Config(void);
void Error_Handler(void);

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
}
#endif
/*==================[end of file]============================================*/
#endif /* #ifndef _SAPI_BOARD_H_ */
