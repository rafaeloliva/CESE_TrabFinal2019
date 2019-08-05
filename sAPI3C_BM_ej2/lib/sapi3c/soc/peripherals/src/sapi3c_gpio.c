/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
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
  * Adapted for CL3 board: R.Oliva 06-2019
  ******************************************************************************
  **/

/* Date: 2019-06-10 */

/* Includes ------------------------------------------------------------------*/
#include "sapi3c_gpio.h"

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/

/**
  * @brief  CL3 board - Configure GPIO and clocks, Reset outputs
            Call first, similar to gpioInit(0, GPIO_ENABLE) on sAPI 
  * @param  None
  * @retval None
  */
void gpioInitEnable(void)
{

  /* GPIO Ports Clock Enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);

  /**/
  LL_GPIO_ResetOutputPin(GPIOC, SPI_RES_Pin);

  /**/
  LL_GPIO_ResetOutputPin(GPIOA, PA0_EN_EXP_PW_Pin|PA1_EN_LCD_PW_Pin);

  /**/
  LL_GPIO_ResetOutputPin(GPIOB, OLED_Pin|RS485_DE_Pin|LCD_DATA_Pin|LCD_CLK_Pin 
                          |SPI_CS_Pin|SPI_DC_Pin|PB8_EN_IOT_PW_Pin|PB9_EN_SER_PWR_Pin);
}


/**
* @brief  bool_t gpioInitInput( inputMap_t input, uint32_t config_pull )
          Select from one of the following ( sapi3c_board.h) 
  		  typedef enum {
			   KBD_ABJ    = 0,  // K_ABJ_PB0_Pin 
			   KBD_DER    = 1,  // K_DER_PB1_Pin 
			   KBD_IZQ    = 2,  // K_IZQ_PC4_Pin
			   KBD_ARR    = 3,  // K_ARR_PC5_Pin
			   SDIO_CD    = 4,  // SDIO_CD_Pin_PC11 (former CS)
			   SDIO_INS   = 5   // SD_INS_Pin_PC10
			} inputMap_t;
			and config_pull can be LL_GPIO_PULL_UP or LL_GPIO_PULL_NO 
* @param  inputMap_t input, uint32_t config_pull
* @retval 0 if error, 1 if ok		
*/

bool_t gpioInitInput( inputMap_t input, uint32_t config_pull )
{

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  bool_t ret_val     = 1;
 
 /* Common parameters */
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = config_pull;
  switch(input){
	  case KBD_ABJ:
	    GPIO_InitStruct.Pin = K_ABJ_PB0_Pin;
		LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		break;
	   case KBD_DER:
	    GPIO_InitStruct.Pin = K_DER_PB1_Pin;
		LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		break;
	  case KBD_IZQ:
	    GPIO_InitStruct.Pin = K_IZQ_PC4_Pin;
		LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		break;	
	  case KBD_ARR:
	    GPIO_InitStruct.Pin = K_ARR_PC5_Pin;
		LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		break;		
	  case SDIO_INS:
	    GPIO_InitStruct.Pin = SD_INS_Pin;
		LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		break;	
	  case SDIO_CD:
	    GPIO_InitStruct.Pin = SDIO_CD_Pin;
		LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		break;			
	  default:
	    ret_val = 0;
	    break;
   }
 return ret_val;
}
		

/**
* @brief  bool_t gpioInitOutput( outputMap_t output)
          Select from one of the following ( sapi3c_board.h) 
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
* @param  outputMap_t output
* @retval 0 if error, 1 if ok		
*/		
 
   
bool_t gpioInitOutput( outputMap_t output)
{
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  bool_t ret_val     = 1;
  /*
  * Common: Pushpull outputs, LowSpeed, no pullups
  */
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  
  switch(output){
	  case EXP_PW_PA0:
	    GPIO_InitStruct.Pin = PA0_EN_EXP_PW_Pin;
		LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		break;
	   case LCD_PW_PA1:
	    GPIO_InitStruct.Pin = PA1_EN_LCD_PW_Pin;
		LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		break;
	  case OLED_PB2:
	    GPIO_InitStruct.Pin = OLED_Pin;
		LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		break;	
	  case IOT_PW_PB8:
	    GPIO_InitStruct.Pin = PB8_EN_IOT_PW_Pin;
		LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		break;		
	  case SER_PW_PB9:
	    GPIO_InitStruct.Pin = PB9_EN_SER_PWR_Pin;
		LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		break;	
	  case RS485_DE_PB10:
	    GPIO_InitStruct.Pin = RS485_DE_Pin;
		LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		break;
	  case LCD_CLK_PB12:
	    GPIO_InitStruct.Pin = LCD_CLK_Pin;
		LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		break;
	  case LCD_DATA_PB13:
	    GPIO_InitStruct.Pin = LCD_DATA_Pin;
		LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		break;
	  case SPI_CS_PB14:
	    GPIO_InitStruct.Pin = SPI_CS_Pin;
		LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		break;
	  case SPI_DC_PB15:
	    GPIO_InitStruct.Pin = SPI_DC_Pin;
		LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		break;
	  case SPI_RES_PC13:
	    GPIO_InitStruct.Pin = SPI_RES_Pin;
		LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		break;		
	  default:
	    ret_val = 0;
	    break;
   }
 return ret_val;
}


/**
  * @brief  gpioInit_INT1(void) on CL3 board configure INT1 
            for I2C bus - external
  * @param  None
  * @retval None
  */
	
void gpioInit_INT1(void)
{

  LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
		
  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE15);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_15;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  LL_GPIO_SetPinPull(INT1_N_GPIO_Port, INT1_N_Pin, LL_GPIO_PULL_NO);

  /**/
  LL_GPIO_SetPinMode(INT1_N_GPIO_Port, INT1_N_Pin, LL_GPIO_MODE_INPUT);

}

/**
  * @brief  bool_t gpioRead( inputMap_t input )
            uses: LL_GPIO_IsInputPinSet
			__STATIC_INLINE uint32_t LL_GPIO_IsInputPinSet(GPIO_TypeDef *GPIOx, uint32_t PinMask)
			{
				return (READ_BIT(GPIOx->IDR, PinMask) == (PinMask));
			}
            Return if input data level for several pins of dedicated port is high or low.
  * @rmtoll IDR          IDy           LL_GPIO_IsInputPinSet
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  *         @arg @ref LL_GPIO_PIN_ALL
  * @retval State of bit (1 or 0).
*/

bool_t gpioRead( inputMap_t input )
{

uint32_t ret_val = 0;
switch(input){
	  case KBD_ABJ:
	    ret_val = LL_GPIO_IsInputPinSet(GPIOB, K_ABJ_PB0_Pin);
		break;
      case KBD_DER:
		ret_val = LL_GPIO_IsInputPinSet(GPIOB, K_DER_PB1_Pin);
		break;
	  case KBD_IZQ:
	    ret_val = LL_GPIO_IsInputPinSet(GPIOC, K_IZQ_PC4_Pin);
		break;	
	  case KBD_ARR:
	    ret_val = LL_GPIO_IsInputPinSet(GPIOC, K_ARR_PC5_Pin);	  
		break;		
	  case SDIO_INS:
	    ret_val = LL_GPIO_IsInputPinSet(GPIOC, SD_INS_Pin);	  	  
		break;	
	  case SDIO_CD:
	  	ret_val = LL_GPIO_IsInputPinSet(GPIOC, SDIO_CD_Pin);
		break;			
	  default:
	    ret_val = 1;
	    break;
    }     
   return ((bool_t)ret_val);
}

/**
* @brief  bool_t gpioWrite( outputMap_t output, bool_t value)
          Select from one of the following ( sapi3c_board.h) 
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
	(original sapi: gpioWrite( gpioMap_t pin, bool_t value ) ) 
* @param  outputMap_t output
* @param  bool_t value
* @retval 0 if error, 1 if ok		
*/		
 

bool_t gpioWrite( outputMap_t output, bool_t value)
{
  bool_t ret_val     = 1;
  
  switch(output){
	  case EXP_PW_PA0:
	    if (value) { LL_GPIO_SetOutputPin(GPIOA,PA0_EN_EXP_PW_Pin); }
		else { LL_GPIO_ResetOutputPin(GPIOA,PA0_EN_EXP_PW_Pin); }
		break;
	   case LCD_PW_PA1:
	    if (value) { LL_GPIO_SetOutputPin(GPIOA, PA1_EN_LCD_PW_Pin); }
		else { LL_GPIO_ResetOutputPin(GPIOA,PA1_EN_LCD_PW_Pin); }
		break;
	  case OLED_PB2:
	    if (value) { LL_GPIO_SetOutputPin(GPIOB, OLED_Pin); }
		else { LL_GPIO_ResetOutputPin(GPIOB,OLED_Pin); }
		break;	
	  case IOT_PW_PB8:
	    if (value) { LL_GPIO_SetOutputPin(GPIOB, PB8_EN_IOT_PW_Pin); }
		else { LL_GPIO_ResetOutputPin(GPIOB,PB8_EN_IOT_PW_Pin); }	  
		break;		
	  case SER_PW_PB9:
	    if (value) { LL_GPIO_SetOutputPin(GPIOB, PB9_EN_SER_PWR_Pin); }
		else { LL_GPIO_ResetOutputPin(GPIOB,PB9_EN_SER_PWR_Pin); }	  	  
		break;	
	  case RS485_DE_PB10:
	    if (value) { LL_GPIO_SetOutputPin(GPIOB, RS485_DE_Pin); }
		else { LL_GPIO_ResetOutputPin(GPIOB,RS485_DE_Pin); }	  	  	  
	    break;
	  case LCD_CLK_PB12:
	    if (value) { LL_GPIO_SetOutputPin(GPIOB, LCD_CLK_Pin); }
		else { LL_GPIO_ResetOutputPin(GPIOB,LCD_CLK_Pin); }	  	  	  
		break;
	  case LCD_DATA_PB13:
	    if (value) { LL_GPIO_SetOutputPin(GPIOB, LCD_DATA_Pin); }
		else { LL_GPIO_ResetOutputPin(GPIOB,LCD_DATA_Pin); }	  	  	  
		break;
	  case SPI_CS_PB14:
	    if (value) { LL_GPIO_SetOutputPin(GPIOB, SPI_CS_Pin); }
		else { LL_GPIO_ResetOutputPin(GPIOB, SPI_CS_Pin); }	  	  	  
		break;
	  case SPI_DC_PB15:
	    if (value) { LL_GPIO_SetOutputPin(GPIOB, SPI_DC_Pin); }
		else { LL_GPIO_ResetOutputPin(GPIOB, SPI_DC_Pin); }	  	  	  
		break;
	  case SPI_RES_PC13:
	    if (value) { LL_GPIO_SetOutputPin(GPIOC, SPI_RES_Pin); }
		else { LL_GPIO_ResetOutputPin(GPIOC, SPI_RES_Pin); }	  	  	  
		break;		
	  default:
	    ret_val = 0;
	    break;
   }
 return ret_val;
}





/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
