/**
  ******************************************************************************
  * @file           : tareas.h
  * @brief          : Header for tareas.c  file.
  *                   Tareas en FreeRTOS - Ej04
  ******************************************************************************
  */
  
  /**
  ******************************************************************************
  * @author  E.Pernia / adapted by R.Oliva
  * @brief   Header for Tareas.c - Tests FreeRTOS with sApi3c for CL3
  *          rev 21.8.19
  *
 **/  
  

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TAREAS_H
#define __TAREAS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "cmsis_os.h"
#include "sapi3c.h"
#include "string.h"
#include "stdlib.h"

/* Private includes ----------------------------------------------------------*/
// Los definimos como extern en tareas.h,

extern TaskHandle_t xTaskHandleDisplay;    // Task 1 Display Handle
extern TaskHandle_t xTaskHandleChkMeteo;   // Task 2 CheckMeteo Handle
extern TaskHandle_t xTaskHandleProcOutd;   // Task 3 ProcessOutdoorInfo Handle
extern TaskHandle_t xTaskHandleWrUart6;    // Task 4 Write_Uart6 Handle
extern TaskHandle_t xTaskHandlePrintErr;   // Task 5 PrintError
extern TaskHandle_t xTaskHandleHeartBeat;  // Task 6 OLED Heartbeat 21.4.19
extern TaskHandle_t xTaskHandleUart6CmdH;  // Task 7 Uart6 CmdHandling 21.4.19
extern TaskHandle_t xTaskHandleUart6CmdP;  // Task 8 Uart6 CmdProcess 21.4.19
extern TaskHandle_t xTaskHandleDisplayLCD; // Task 9 Display LCDhandle 21.8.2019

//Queue handle
extern QueueHandle_t packet_queue;         // ok packets queue handle
extern QueueHandle_t output_write_queue;   // output write queue handle
extern QueueHandle_t command_queue;        // comandos via UART6 Terminal

//software timer handle
extern TimerHandle_t led_timer_handle;

// Mutex handle declaration
extern SemaphoreHandle_t xMutex;           // Protects sensor_data

// Binary Semaphore Handle
extern SemaphoreHandle_t xSem1;

// Functions:
void CL3_FREERTOS_Init(void);
void StartDefaultTask(void const * argument);

//tasks prototypes - RTOS1
void vTask_Display(void *params);              // Task 1 = Display
void vTask_Check_Meteo_packet(void *params);   // Task 2 = Check Meteo Packet
void vTask_Process_OutdoorInfo(void *params);  // Task 3 = ProcessOutdoorInfo
void vTask_Write_Uart6(void *params);          // Task 4 = Write to UART6 -Terminal
void vTask_PrintError(void *params);           // Task 5 = Imprimeerror
void vTask_HeartBeat(void *params);            // Task 6 = OLED Heartbeat 21.4.19
void vTask_uart6_cmd_handling(void *params);   // Task 7 = Terminal UART6 Cmd_Handling
void vTask_uart6_cmd_processing(void *params); // Task 8 = Terminal UART6 proceso comandos
void vTask_DisplayLCD(void *params);           // Task 9 = Display LCD 21.8.2019

#ifdef __cplusplus
}
#endif

#endif /* __TAREAS_H */

/************************ R.Oliva 2019  ******************* *****END OF FILE****/
