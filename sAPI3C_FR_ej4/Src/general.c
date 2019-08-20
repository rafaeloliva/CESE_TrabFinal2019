/**
  ******************************************************************************
  * @file           : general.c
  * @brief          : Rutinas de uso general en ej04 - Sapi3C
  ******************************************************************************
  *
  ******************************************************************************
  */
  /**
  ******************************************************************************
  * @author  R.Oliva
  * @brief   Ej 04 This file contains Auxiliary routines ej04 
  *          with sApi3c for CL3
  *          rev 12.8.19
  *
 **/  
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "general.h"
#include "sapi3c.h"

char TestCStr[] = "UUU$29335.10156.2562.15100.125.1095*QQQ";
// y sin el tramo final:
// (corregido al valor en hexa = 57278 = 0xdfbe
char okTestCStr[] = "UUU$29335.10156.2562.15100.125.DFBE";
/* Private variables ---------------------------------------------------------*/

//global space for some variable
char usr_msg[250]={0};

// for SPI_Display Check
uint8_t btest = 0;

// packet buffer - de UART_LL_5 04.19
uint8_t packet_buffer[PKTBUFSIZE];
uint8_t packet_len = 0;
uint8_t command_buffer[20];
uint8_t command_len = 0 ;
// 27.4.2019 packet_started flag
// For complete packet reception on UART1
uint8_t packet_started = 0;

// Pasamos a memoria global 24.4.2019
PACKET_OK_t new_packet;

// Global Sensor values (int)
V_SENSOR_t sensor_val;

// Control
int16_t  g_chk = 0;
int16_t  g_items = 0;
uint16_t g_checksum = 0; // 25.4.19
uint32_t g_Rx_Errors = 0; // Added 27.4.2019 - Incremented by Task 5


// Menu por USART 6
// Nuevo menu 24.4.2019
char menu[]={"\
\r\nImprime Viento de METEO   ----> 1 \
\r\nImprime TempExterior MET  ----> 2 \
\r\nImprime DirViento METEO   ----> 3 \
\r\nImprime Info String MET    ---> 4 \
\r\nImprime Continuamente      ---> 5 \
\r\nDetener e imprimir Menu   ----> 0 \
\r\nTipee su opcion : "};

// de UART_LL_6 - RTC use..
// en main.c -  Declaraciones de buffers y funciones de RTC_Config y Display
/* Tomamos de EJ1 – e.2.2 (Global) Buffers used for displaying Time and Date */

uint8_t aShowTime[50] = {0};
uint8_t aShowDate[50] = {0};


// Funciones generales de UART_LL_5
// Prints message out on UART6..
// 18.4.2019 Use LL_USART functions as in STM32F4 LL_Examples
void printmsg(char *msg)
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

// Funciones de Salida al UART6 18.4.19

// UART6 Mensaje Comando 1
void print_Uart6_messageCmd1(char *task_msg)
{
	sprintf( task_msg,"\r\n Comando 1\r\n");
	xQueueSend(output_write_queue,&task_msg,portMAX_DELAY);
}

// Salida 1 - viento en UART1 -25-4-19
void print_Wind_Speed(char *task_msg, int16_t wsp)
{
	sprintf( task_msg,"\r\n Veloc viento %d \r\n", wsp);
	xQueueSend(output_write_queue,&task_msg, portMAX_DELAY);
}

// Salida 2 - Temp en UART1 - redef 25.4.2019
void print_Out_Temp(char *task_msg, int16_t temp)
{
	sprintf( task_msg,"\r\n Temp Ext %d \r\n", temp);
	xQueueSend(output_write_queue,&task_msg, portMAX_DELAY);
}

// Salida 3 - DirViento en UART1 - redef 25.4.2019
void print_Wind_Dir(char *task_msg, int16_t wdir)
{
	sprintf( task_msg,"\r\n Direcc. viento %d \r\n", wdir);
	xQueueSend(output_write_queue,&task_msg, portMAX_DELAY);
}

// Salida 4 - u6checksum = g_checksum; u6chk  = g_chk;
//            u6items = g_items;
// uint16_t u6chk = 0; int16_t u6items = 0;
// redef 25.4.2019

void print_String_Items(char *task_msg, uint16_t u6checksum, uint16_t u6chk, int16_t u6items)
{
	sprintf( task_msg,"\r\n Leido: Chks %d  Calc: chk %d Items: %d\r\n",u6checksum, u6chk, u6items);
	xQueueSend(output_write_queue,&task_msg, portMAX_DELAY);
}

// Salida 5 - Impresion continua;
// Divide in two sprintf calls()..
void print_String_Complete(char *task_msg,
		int16_t temp,
		int16_t wsp,
		int16_t wdir,
		uint16_t u6checksum,
		uint16_t u6chk,
		int16_t u6items,
		uint32_t u6_Rx_Errors)
{
    vTaskDelay(pdMS_TO_TICKS(200));
	sprintf( task_msg,"\r\n Dat: T=%5hd Vv= %5hd Wd=%4hd",temp,wsp,wdir);
	xQueueSend(output_write_queue,&task_msg, portMAX_DELAY);
	vTaskDelay(pdMS_TO_TICKS(200));
	sprintf( task_msg," Rchk: %d Cchk: %d It: %d Errs:%ld\r\n",u6checksum,u6chk,u6items,u6_Rx_Errors );
	xQueueSend(output_write_queue,&task_msg, portMAX_DELAY);
}


// Salida  - Error en Outdoor Info
void print_error_message(char *task_msg)
{
	sprintf( task_msg,"\r\n Error en OutdoorInfo\r\n");
	xQueueSend(output_write_queue,&task_msg,portMAX_DELAY);
}

// UART6 Error en Comando
void print_Uart6_error_message(char *task_msg)
{
	sprintf( task_msg,"\r\n Comando no reconocido\r\n");
	xQueueSend(output_write_queue,&task_msg,portMAX_DELAY);
}

// Comandos UART6 - Terminal 21.4.19 Sacar el ASCII
uint8_t getCommandCode(uint8_t *buffer)
{

	return buffer[0]-48;
}

// Futuro: comandos UART6 - Terminal - Argumentos
void getArguments(uint8_t *buffer)
{


}


// Taken from LL_UART - Requires RXNE IT Enable
// Testing
#define RX_UART1_EN
void Start_Reception(void){
	// Habilitar Flags limpieza y Recepcion
	sprintf(usr_msg,"\r\n Inicio Recepcion UART6 \r\n");
	printmsg(usr_msg);
	// Limpiar Overrun Flag UART6
	LL_USART_ClearFlag_ORE(USART6);
	// Habilitar Interrupcion pr RXNE (Rx Not Empty)
	LL_USART_EnableIT_RXNE(USART6);
#ifdef RX_UART1_EN
	sprintf(usr_msg,"\r\n Inicio Recepcion UART1 \r\n");
	printmsg(usr_msg);
	// Limpiar Overrun Flag UART1
	LL_USART_ClearFlag_ORE(USART1);
	// Habilitar Interrupcion pr RXNE (Rx Not Empty)
	LL_USART_EnableIT_RXNE(USART1);
#endif
}

/*=================================================================================
 	 	 	Queue and Sem create
 =================================================================================*/

void QueueAndSemCreateAll (void){
  // Create packet queue (up to 10 stripped packets)
  packet_queue = xQueueCreate(10,sizeof(PACKET_OK_t));

  // Create the write queue (up to 300 chars) - 25.4.19 ++to300 chars
  output_write_queue = xQueueCreate(300,sizeof(char*));

  // 21.4.2019 create command queue
  command_queue = xQueueCreate(10,sizeof(APP_CMD_t*));

  //24.4.2019 Zona protegida de Memoria Sensores
  xMutex = xSemaphoreCreateMutex();

  // 25.4.2019
  xSem1 =  xSemaphoreCreateBinary();

  if((packet_queue != NULL) && (output_write_queue != NULL) && (command_queue != NULL) && (xMutex != NULL) && xSem1 != NULL )
    {
	  return;
    }
  else
    {
	  sprintf(usr_msg,"Fallo la creacion de las colas / mutex!\r\n");
	  printmsg(usr_msg);
    }
}

/*=================================================================================
 	 	 	 	task create
 =================================================================================*/
void TaskCreateAll(void){
	       // Create task-1 vTask_Display
		// TaskHandle_t xTaskHandleDisplay -  Task 1 Display Handle
		xTaskCreate(vTask_Display,"TASK_DISPLAY-1",500,NULL,1,&xTaskHandleDisplay);

		// Create task-2 vTask_Check_Meteo_packet
		// TaskHandle_t xTaskHandleChkMeteo - Task 2 CheckMeteo Handle
		// 27.4.2019 Give higher priority to copy UART1 stringbuffer right away..
		xTaskCreate(vTask_Check_Meteo_packet,"TASK_CHK_MET_2",500,NULL,3,&xTaskHandleChkMeteo);

		// Create task-3 vTask_Process_OutdoorInfo
		// TaskHandle_t xTaskHandleProcOutd - Task 3 ProcessOutdoorInfo Handle
		xTaskCreate(vTask_Process_OutdoorInfo,"TASK_PROCESS_OUTD_3",500,NULL,2,&xTaskHandleProcOutd);

		// Create task-4 vTask_Write_Uart6
		// TaskHandle_t xTaskHandleWrUart6  - Task 4 Write_Uart6 Handle
		xTaskCreate(vTask_Write_Uart6,"TASK4-UART-WRITE",500,NULL,2,&xTaskHandleWrUart6);

		// Create task-5 vTask_PrintError
		// TaskHandle_t xPrintError  - Task 5
		xTaskCreate(vTask_PrintError,"TASK5-PRINTERROR",500,NULL,2,&xTaskHandlePrintErr);

		// Create task-6 vTask_HeartBeat
		// TaskHandle_t HeartBeat  - Task 6
		xTaskCreate(vTask_HeartBeat,"TASK6-HrtBEAT",500,NULL,2,&xTaskHandleHeartBeat);

		//create task-7 U6 cmd handle
		xTaskCreate(vTask_uart6_cmd_handling,"TASK7-U6CMD-HANDLING",500,NULL,2,&xTaskHandleUart6CmdH);

		//create task-8 U6 cmd process 25.4.Subimos Stack
		xTaskCreate(vTask_uart6_cmd_processing,"TASK8-U6CMD-PROCESS",700,NULL,2,&xTaskHandleUart6CmdP);
}



#ifdef RTC_FRTOS_EN
// de UART_LL_6 - si RTC habilitado..
// Al final de main.c en LL_UART6
static void RTC_CalendarConfig(void)
{
  RTC_DateTypeDef sdatestructure;
  RTC_TimeTypeDef stimestructure;

  /* Configure the Date ####*/
  /* Date: Wed July 17th 2019 */
  sdatestructure.Year = 0x19;
  sdatestructure.Month = RTC_MONTH_JULY;
  sdatestructure.Date = 0x17;
  sdatestructure.WeekDay = RTC_WEEKDAY_WEDNESDAY;

  if(HAL_RTC_SetDate(&hrtc,&sdatestructure,RTC_FORMAT_BCD) != HAL_OK)
  {
    /* Error */
    Error_Handler();
  }

  /*##-2a- Configure the Time ####*/
  /* Set Time: 21:47:04 */
  stimestructure.Hours = 0x21;
  stimestructure.Minutes = 0x47;
  stimestructure.Seconds = 0x04;
  stimestructure.TimeFormat = RTC_HOURFORMAT_24;
  stimestructure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  stimestructure.StoreOperation = RTC_STOREOPERATION_RESET;

  if(HAL_RTC_SetTime(&hrtc,&stimestructure,RTC_FORMAT_BCD) != HAL_OK)
  {
    /* Error */
    Error_Handler();
  }

  /*##-3- Writes data = 0x32F2 in RTC Backup data Register0 ####*/
  HAL_RTCEx_BKUPWrite(&hrtc,RTC_BKP_DR0,0x32F2);
}



// ACCION e.2.4) 17.7.19
// Al final de main.c en LL_UART6

/**
  * @brief  Our RTC_CalShow() -> Display the current time and date 17.07.19
  * @param  showtime: pointer to buffer
  * @param  showdate: pointer to buffer
  * @retval None
  */
static void RTC_CalendarShow(uint8_t *showtime, uint8_t *showdate)
{
  #define DISPLAY_ON_DUBUGGER
  RTC_DateTypeDef sdatestructureget;
  RTC_TimeTypeDef stimestructureget;

  /* Get the RTC current Time */
  HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BIN);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);

  #ifdef DISPLAY_ON_DUBUGGER
  /* Display time Format: hh:mm:ss */
  sprintf((char*)showtime,"%02d:%02d:%02d",stimestructureget.Hours, stimestructureget.Minutes,
     stimestructureget.Seconds);
  /* Display date Format: mm-dd-yy */
  sprintf((char*)showdate,"%02d-%02d-%02d",sdatestructureget.Month, sdatestructureget.Date, 2000 +
     sdatestructureget.Year);
  #endif
}
#endif



