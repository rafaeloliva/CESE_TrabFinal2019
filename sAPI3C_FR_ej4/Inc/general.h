/**
  ******************************************************************************
  * @file           : general.h
  * @brief          : Header for general.c  file.
  *                   Funciones de apoyo Ej04
  ******************************************************************************
  */
  
  /**
  ******************************************************************************
  * @author  E.Pernia / adapted by R.Oliva
  * @brief   Header for general.c - Tests FreeRTOS with sApi3c for CL3
  *          rev 12.8.19
  *
 **/  
  

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GENERAL_H
#define __GENERAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

// Ej04 - 19.8.2019
#include "tareas.h"

#define PKTBUFSIZE  96
#define PACK_OK_LEN 35
// Added 27.4.2019 for UART1 Reception w/start of String..
#define PACKET_MAX 33

// 24.4.2019 -Make packet_content type char, 35+2 chars long
typedef struct PACKET_OK
{ 
  char packet_content[PACK_OK_LEN+2];
} PACKET_OK_t;
// 
// v6 for use with METEO v20 uses packet "UUU$ttttt.bbbbb.dddd.sssss.vvv.CRCC*QQQ":  (WSpeed is 5 chars long) 
//      UUU$   start identifier
//      ttttt is 00000 08191 Raw Temperature ADC reading, can be 0-5V( Direct sensor with G=2) or 1-5V (4-20mA)
//      bbbbb is 00000 08191 Raw BaroPressure ADC reading, can be 0-5V( Direct sensor with G=1) or 1-5V (4-20mA)
//      dddd  is 0000 to 3600, WDIR*10 in UWORD
//      sssss is 00000 to 99999 from Anemometer / Thies.
//      vvv   was voltage, not used.
//      CRCC  is simple checksum (paso a uint16_t)
//      *QQQ  end identifier
//      Total length from $ is: 5+1+5+1+4+1+5+1+3+1+4= then '*' =15+7+4+5 =31
//      Total length form first U is 31+4 = 35
//      TestCStr[] = "UUU$29335.10156.2562.15100.125.1095*QQQ";
//  Parsed originally (after $ detected) with
// 	c = (char)sscanf(packet,"%5d.%5d.%4d.%5d.%3d.%4x",&out_t,
//  
//  Now Parsed with UUU$ at start with:
// 	c = (uint8_t)sscanf(packet,"%4s%5d.%5d.%4d.%5d.%3d.%4x",&out_id,&out_t,
//		&out_b, &out_w_dir,&out_w_speed,
//		&out_vbat,&checksum);
// char okTestCStr[] = "UUU$29335.10156.2562.15100.125.1095";
// 27.4.2019 returned to parsing with $ detection

//UART6 command structure Implem 21.4.19
typedef struct APP_CMD
{
	uint8_t COMMAND_NUM;
	uint8_t COMMAND_ARGS[10];
}APP_CMD_t;

typedef struct sensor_holder {
        int16_t IS_Aero;      // Current in 0-5V - Sampled
        int16_t Vs_Vbat;      // Bat. Voltage in 0-5V - Sampled
        int16_t Vs_OWind;     // OutDoor Wind Freq [Hz] from METEO / COM1
        int16_t Vs_OWDir;     // OutDoor WindDirection 0-360.0 [º] from METEO / COM1
        int16_t Vs_OTemp;     // External Temp 0-5V from METEO+NOMAD2/COM1
        int16_t Vs_OBaro;     // Barometric Pressure 0-5V from METEO+NOMAD2/COM1
} V_SENSOR_t;

// Arreglo (iii)
// global space for some variable
extern char usr_msg[];

// for SPI_Display Check
extern uint8_t btest;

// packet buffer - de UART_LL_5 04.19
extern uint8_t packet_buffer[];
extern uint8_t packet_len;
extern uint8_t command_buffer[];
extern uint8_t command_len;
// 27.4.2019 packet_started flag
// For complete packet reception on UART1
extern uint8_t packet_started;

// Arreglo (iv)
extern PACKET_OK_t new_packet;

// Global Sensor values (int)
extern V_SENSOR_t sensor_val;

// Control
extern int16_t  g_chk;
extern int16_t  g_items;
extern uint16_t g_checksum; // 25.4.19
extern uint32_t g_Rx_Errors; // Added 27.4.2019 - Incremented by Task 5

// Menu por USART 6
// Nuevo menu 24.4.2019
extern char menu[];

/* Private includes ----------------------------------------------------------*/

// Auxiliary
// Funciones auxiliares 04.2019 RTOS1
// Enviar el Queue de salida a UART6
// void vTask_Write_Uart6(void *params);
// Prints message out on UART6..
void printmsg(char *msg);
// Enviar Items leidos via UART1
void print_items_message(int16_t items);
// Salida 1 - viento en UART1 - redef 25.4.2019
void print_Wind_Speed(char *task_msg, int16_t wsp);
// Salida 2 - Temp en UART1 - redef 25.4.2019
void print_Out_Temp(char *task_msg, int16_t temp);
// Salida 3 - DirViento en UART1 - redef 25.4.2019
void print_Wind_Dir(char *task_msg, int16_t wdir);
// Salida 4 - Contenidos String - redef 25.4.2019
void print_String_Items(char *task_msg, uint16_t u6checksum, uint16_t u6chk, int16_t u6items);
// Salida 5 - Impresion continua;
void print_String_Complete(char *task_msg,
		int16_t temp,
		int16_t wsp,
		int16_t wdir,
		uint16_t u6checksum,
		uint16_t u6chk,
		int16_t u6items,
		uint32_t u6_Rx_Errors);

// Salida - Error en Outdoor Info
void print_error_message(char *task_msg);
// Codigo del U6 - Terminal
uint8_t getCommandCode(uint8_t *buffer);
// Futuro: comandos UART6 - Terminal - Argumentos
void getArguments(uint8_t *buffer);
// Implementado 21.4.19 para comando 1

// 22 4 2019  -Start Reception Function
// Rutinal LL requieren habilitación
// (STMCubeF4 v1_24 - LLNucleo 411 Examples)
void Start_Reception(void);
// Salida U6 Menu - Error en Comando
void print_Uart6_error_message(char *task_msg);
// UART6 Mensaje Comando 1
void print_Uart6_messageCmd1(char *task_msg);

// Added for CL3 _TPFinal implementation
void QueueAndSemCreateAll (void);
void TaskCreateAll(void);

/* UART_LL_6 RTC function prototypes -----------------------------------------------*/
// #define RTC_FRTOS_EN
#ifdef RTC_FRTOS_EN
static void RTC_CalendarConfig(void);
static void RTC_CalendarShow(uint8_t* showtime, uint8_t* showdate);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __GENERAL_H */

/************************ R.Oliva 2019  ******************* *****END OF FILE****/
