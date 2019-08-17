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
 * sapi3c_board.c
 * Adapted for CL3 board: R.Oliva 06-2019
 *
 */

 /**
  ******************************************************************************
  * @file    sapi3c_board.c
  * @author  E.Pernia / adapted by R.Oliva
  * @brief   This file holds board-specific configuration for CL3
  *          rev. 4.8.19
  *
 **/
 
/* Date: 2019-06-10 */

/*==================[inclusions]=============================================*/

#include "sapi3c_board.h"
#include "sapi3c_gpio.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
// Only use when functions defined..
// #define PRELIMINARY_TEST 1

/*==================[external functions definition]==========================*/
 
/**
  * @brief  boardInitCL3() - Set up and initialize CL3 board hardware
  *         First call the system Clock configuration,
  *         Then enable all gpio_inputs (clocks & reset outputs)
  *         Then configure all gpio_inputs, all gpio_outputs
  *         Finally the -INT1 EXTI interrupt 
  * @param  None
  * @retval None
  */
void boardInitCL3(void)
{
   
   // STM32 HAL initialization
   HAL_Init();
   // STM32 System Clock Config STM32F411RE on CL3
   SystemClock_Config();

   // Configure GPIO pins for CL3 board
   
   // Inicializar GPIOs
   // gpioInit( 0, GPIO_ENABLE );
   gpioInitEnable();

   // Configuracion de pines de entrada de CL3
   // Similar to gpioInit( DI0, GPIO_INPUT ); in EDUCIAA
	  /*
	   KBD_ABJ    = 0,  // K_ABJ_PB0_Pin 
       KBD_DER    = 1,  // K_DER_PB1_Pin 
       KBD_IZQ    = 2,  // K_IZQ_PC4_Pin
       KBD_ARR    = 3,  // K_ARR_PC5_Pin
       SDIO_CD    = 4,  // SDIO_CD_Pin_PC11 (former CS)
       SDIO_INS   = 5   // SD_INS_Pin_PC10
	   and config_pull can be LL_GPIO_PULL_UP or LL_GPIO_PULL_NO
	  */
	  
    gpioInitInput( KBD_ABJ, LL_GPIO_PULL_UP);
	gpioInitInput( KBD_DER, LL_GPIO_PULL_UP);
	gpioInitInput( KBD_IZQ, LL_GPIO_PULL_UP);
	gpioInitInput( KBD_ARR, LL_GPIO_PULL_UP);
	gpioInitInput( SDIO_CD, LL_GPIO_PULL_UP);
	gpioInitInput( SDIO_INS, LL_GPIO_PULL_NO);
	  
    // Configuracion de pines de salida de CL3
	// bool_t gpioInitOutput( outputMap_t output);
    // Similar a gpioInit( DO0, GPIO_OUTPUT );
	  // EXP_PW_PA0   = 0,   // PA0_EN_EXP_PW_Pin 
	  // LCD_PW_PA1   ,      // PA1_EN_LCD_PW_Pin
      // OLED_PB2     ,      // PB2_OLED_Pin
      // IOT_PW_PB8   ,      // PB8_EN_IOT_PW_Pin
      // SER_PW_PB9   ,      // PB9_EN_SER_PWR_Pin
      // RS485_DE_PB10,      // PB10_RS485_DE_Pin
      // LCD_CLK_PB12 ,      // PB12_LCD_CLK_pin
      // LCD_DATA_PB13,      // PB13_LCD_DATA_pin
      // SPI_CS_PB14  ,      // PB14_(exLDC_E)_SPI_CS_Pin
      // SPI_DC_PB15  ,      // PB15_(exLDC_BL)_SPI_DC_Pin
      // SPI_RES_PC13        // PC13_(exSD_WREN)_SPI_RES_Pin 
	  
    gpioInitOutput(EXP_PW_PA0);
	gpioInitOutput(LCD_PW_PA1);
	gpioInitOutput(OLED_PB2);
	gpioInitOutput(IOT_PW_PB8);
	gpioInitOutput(SER_PW_PB9);
    gpioInitOutput(RS485_DE_PB10);
	gpioInitOutput(LCD_CLK_PB12);
	gpioInitOutput(LCD_DATA_PB13);
	gpioInitOutput(SPI_CS_PB14);
	gpioInitOutput(SPI_DC_PB15);
	gpioInitOutput(SPI_RES_PC13);
	  
	// Configuración Entrada _INT1 de Interrupcion
	gpioInit_INT1();

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}


/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */


/*==================[end of file]============================================*/
