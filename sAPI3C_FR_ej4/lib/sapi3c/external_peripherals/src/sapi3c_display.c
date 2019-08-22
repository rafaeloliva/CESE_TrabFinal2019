/**
  ******************************************************************************
  * File Name          : sapi3c_display.c
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
#include "sapi3c_display.h"

/* External handle for SPI1 module--------------------------------------------*/                      
SPI_HandleTypeDef hspi1;

/* Local Functions -----------------------------------------------------------*/

static void Welcome_Screen(void);
static void Screen1(void);
static void Screen2(void);
static void Screen3(void);
static void Screen4(void);
static void CL3_ILI9341_init(void);

/*----------------------------------------------------------------------------*/
/* Configure Display                                                          */
/*----------------------------------------------------------------------------*/

/**
  * @brief  CL3 board - Configure Display
            typedef enum {
				ILI9341 = 0, // Default Display
				DISP2,       // Alternative 2
				DISP3        // Alternative 3
			} display_t;
			Only turns screen to Black if ILI9341
  * @param  display_t distype (0 is ILI9341)
  * @retval 0 if OK, 1 if SPI_DeInit failed,  
  *         2 or 3 SPI_DeInit/Init, 10 display not implemented 
  */
uint8_t displaycl3_Config(display_t distype)
{
      uint8_t ret_val     = 0;
	  switch(distype){
		case ILI9341:
		   CL3_SPI1_Init();  // SPI Initialize
		   HAL_Delay(500);
		   CL3_ILI9341_init();       // prepare ILI9341
		   if(HAL_SPI_DeInit(&hspi1) != HAL_OK) {
                   // means HAL_SPI_DeInit failed 
				   ret_val = 1;
		   }
           hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
		   if(HAL_SPI_Init(&hspi1) != HAL_OK) {
           // means HAL_SPI_Init failed 
				   ret_val = ret_val+2;
           }
           // Check border
           ILI9341_FillScreen(ILI9341_BLACK);
		   break;
		default:
           ret_val = 10;   // not implemented
		   break;
	  
        }
    return ret_val;
}	  
      		   
/**
* @brief  uint8_t displaycl3_Screen(screen_t screen)
          Select from one of the following ( sapi3c_display.h) 
			typedef enum {
			   WELCOME = 0,   // Default Welcome Screen
			   SCREEN1,       // Alternative Screen 1
			   SCREEN2,       // Alternative Screen 2
			   SCREEN3,       // Alternative Screen 3
			   SCREEN4        // Alternative Screen 3
			   } screen_t;
			and config_pull can be LL_GPIO_PULL_UP or LL_GPIO_PULL_NO 
* @param  inputMap_t input, uint32_t config_pull
* @retval 0 if error, 1 if ok		
*/

uint8_t displaycl3_Screen(screen_t screen)
{

  uint8_t ret_val = 1;
 
   switch(screen){
	  case WELCOME:
	    Welcome_Screen();
		break;
	   case SCREEN1:
	    Screen1();
		break;
	   case SCREEN2:
	    Screen2();
		break;
	   case SCREEN3:
	    Screen3();
		break;		
	   case SCREEN4:
	    Screen4();
		break;		
	  default:
	    ret_val = 0;  // Incorrect option
 	    break;
   }
 return ret_val;
}
		

/**
* @brief  CL3_SPI1_Init() function to setup SPI1 module
          replaces CubeMX generated function 
* @param  none
* @retval none
*/		
void CL3_SPI1_Init(void)
{

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI1)
  {
    /* SPI1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();
  
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**SPI1 GPIO Configuration    
    PB3     ------> SPI1_SCK
    PB4     ------> SPI1_MISO
    PB5     ------> SPI1_MOSI 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
    __HAL_RCC_SPI1_CLK_DISABLE();
  
    /**SPI1 GPIO Configuration    
    PB3     ------> SPI1_SCK
    PB4     ------> SPI1_MISO
    PB5     ------> SPI1_MOSI 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);

  }
}  


/**
* @brief  CL3_ILI9341_init() function replaces init() in Afiskon lib
          initializes the Display after resetting it.
* @param  none
* @retval none
*/
void CL3_ILI9341_init(){
    ILI9341_Unselect();
    ILI9341_TouchUnselect();
    ILI9341_Init();
}

/**
* @brief  Welcome_Screen()
          Sets up initial border, content message.
* @param  none
* @retval none
*/

void Welcome_Screen(void){   

    for(int x = 0; x < ILI9341_WIDTH; x++) {
        ILI9341_DrawPixel(x, 0, ILI9341_RED);
        ILI9341_DrawPixel(x, ILI9341_HEIGHT-1, ILI9341_RED);
    }

    for(int y = 0; y < ILI9341_HEIGHT; y++) {
        ILI9341_DrawPixel(0, y, ILI9341_RED);
        ILI9341_DrawPixel(ILI9341_WIDTH-1, y, ILI9341_RED);
    }
	
	HAL_Delay(500);

    // Check fonts
    ILI9341_FillScreen(ILI9341_BLACK);
	/*                x_coord, y_coord, *str                                                    Font       Color        BGColor      */ 
    ILI9341_WriteString(20, 10, "CESE - Especializacion en         Sistemas Embebidos - FIUBA", Font_7x10, ILI9341_RED, ILI9341_BLACK);
    ILI9341_WriteString(10, 6*10, " Rafael Oliva - CL3", Font_11x18, ILI9341_GREEN, ILI9341_BLACK);
    ILI9341_WriteString(20, 4*10+4*18, "Trabajo Final", Font_16x26, ILI9341_BLUE, ILI9341_BLACK);
    ILI9341_WriteString(80, 4*10+6*18, "2019", Font_16x26, ILI9341_BLUE, ILI9341_BLACK);

    HAL_Delay(1000);
	ILI9341_WriteString(20, 4*10+12*18, "  Presione F1 a F4  ", Font_11x18, ILI9341_GREEN, ILI9341_BLACK); // Agregado 16.8.2019
    // ILI9341_InvertColors(true);
    // HAL_Delay(1000);
    // ILI9341_InvertColors(false);
	   
}


static void Screen1(void)
{
    // F1 - Green Screen - IZQ
    ILI9341_FillScreen(ILI9341_CYAN);
	ILI9341_WriteString(20, 4*10+4*18, "F1 Dir.Viento", Font_16x26, ILI9341_BLACK, ILI9341_CYAN ); // Agregado 16.8.2019
	HAL_Delay(1000);
}

static void Screen2(void)
{
    // F2 - RED Screen - ARRIBA
    ILI9341_FillScreen(ILI9341_RED);
	ILI9341_WriteString(20, 4*10+4*18, "F2 Vel.Viento", Font_16x26, ILI9341_BLACK, ILI9341_RED); // Agregado 16.8.2019
	HAL_Delay(1000);
}
static void Screen3(void)
{
    // F3 - BLUE Screen - ABJ
    ILI9341_FillScreen(ILI9341_BLUE);
    ILI9341_WriteString(10, 4*10+4*18, "F3 Temperatura", Font_16x26, ILI9341_BLACK, ILI9341_BLUE); // Agregado 16.8.2019
                                     /* "  Presione F1 a F4  " */
	HAL_Delay(1000);
}
static void Screen4(void)
{
	// F4 - WHITE Screen - DER
    ILI9341_FillScreen(ILI9341_BLACK);
	ILI9341_WriteString(10, 4*10+4*18, "F4 Presion.Atm", Font_16x26, ILI9341_WHITE, ILI9341_BLACK); // Agregado 16.8.2019
	HAL_Delay(1000);
	
}





/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
