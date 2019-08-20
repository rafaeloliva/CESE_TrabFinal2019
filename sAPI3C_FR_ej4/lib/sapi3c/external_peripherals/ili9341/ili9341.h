/* vim: set ai et ts=4 sw=4: */
/*
* Original Afiskon/Github Driver for ILI9341 - 2018 ili9341.h
* Modified for CL3b - R.Oliva 07.2019
*/
#ifndef __ILI9341_H__
#define __ILI9341_H__

#include "fonts.h"
#include <stdbool.h>

#define ILI9341_MADCTL_MY  0x80
#define ILI9341_MADCTL_MX  0x40
#define ILI9341_MADCTL_MV  0x20
#define ILI9341_MADCTL_ML  0x10
#define ILI9341_MADCTL_RGB 0x00
#define ILI9341_MADCTL_BGR 0x08
#define ILI9341_MADCTL_MH  0x04

/*** Redefine if necessary ***/
#define ILI9341_SPI_PORT hspi1
extern SPI_HandleTypeDef ILI9341_SPI_PORT;

// Original definitions afk - 2018
// #define ILI9341_RES_Pin       GPIO_PIN_7
// #define ILI9341_RES_GPIO_Port GPIOC
// #define ILI9341_CS_Pin        GPIO_PIN_6
// #define ILI9341_CS_GPIO_Port  GPIOB
// #define ILI9341_DC_Pin        GPIO_PIN_9
// #define ILI9341_DC_GPIO_Port  GPIOA

// Now for UART_LL_6 testing 10.7.19 in gpio.c 
// LL_GPIO_ResetOutputPin(OLED_GPIO_Port, OLED_Pin);
// Add SPI_CS = PB14 = LCD_E, SPI_DC = PB15 =LCD_BL
//  LL_GPIO_ResetOutputPin(GPIOB, OLED_Pin|SPI_CS_Pin|SPI_DC_Pin);
// Add former SD_WRENpin = PC13 as output for SPI_RST
//  LL_GPIO_ResetOutputPin(GPIOC, SPI_RST_Pin); 

// 10.7.2019 for SPI_ILI9341 testing..
#define SPI_RST_Pin LL_GPIO_PIN_13
#define SPI_CS_Pin LL_GPIO_PIN_14
#define SPI_DC_Pin LL_GPIO_PIN_15

#define ILI9341_RES_Pin       SPI_RST_Pin
#define ILI9341_RES_GPIO_Port GPIOC
#define ILI9341_CS_Pin        SPI_CS_Pin
#define ILI9341_CS_GPIO_Port  GPIOB
#define ILI9341_DC_Pin        SPI_DC_Pin
#define ILI9341_DC_GPIO_Port  GPIOB


// default orientation
#define ILI9341_WIDTH  240
#define ILI9341_HEIGHT 320
#define ILI9341_ROTATION (ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR)

// rotate right
/*
#define ILI9341_WIDTH  320
#define ILI9341_HEIGHT 240
#define ILI9341_ROTATION (ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR)
*/

// rotate left
/*
#define ILI9341_WIDTH  320
#define ILI9341_HEIGHT 240
#define ILI9341_ROTATION (ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR)
*/

// upside down
/*
#define ILI9341_WIDTH  240
#define ILI9341_HEIGHT 320
#define ILI9341_ROTATION (ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR)
*/

/****************************/

// Color definitions
#define	ILI9341_BLACK   0x0000
#define	ILI9341_BLUE    0x001F
#define	ILI9341_RED     0xF800
#define	ILI9341_GREEN   0x07E0
#define ILI9341_CYAN    0x07FF
#define ILI9341_MAGENTA 0xF81F
#define ILI9341_YELLOW  0xFFE0
#define ILI9341_WHITE   0xFFFF
#define ILI9341_COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

// call before initializing any SPI devices
void ILI9341_Unselect();

void ILI9341_Init(void);
void ILI9341_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ILI9341_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);
void ILI9341_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ILI9341_FillScreen(uint16_t color);
void ILI9341_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);
void ILI9341_InvertColors(bool invert);

#endif // __ILI9341_H__
