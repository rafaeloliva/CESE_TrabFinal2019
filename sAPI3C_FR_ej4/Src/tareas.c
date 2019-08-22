/**
  ******************************************************************************
  * @file           : tareas.c
  * @brief          : Tareas de FreeRTOS en ej04 - Sapi3C
  ******************************************************************************
  *
  ******************************************************************************
  */
  /**
  ******************************************************************************
  * @author  R.Oliva
  * @brief   Ej 04 This file contains Tasks in FreeRTOS for ej04 
  *          with sApi3c for CL3
  *          rev 12.8.19
  *
 **/  
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "tareas.h"
#include "sapi3c.h"
#include "general.h"

//task handles
TaskHandle_t xTaskHandleDisplay   = NULL;   // Task 1 Display Handle
TaskHandle_t xTaskHandleChkMeteo  = NULL;   // Task 2 CheckMeteo Handle
TaskHandle_t xTaskHandleProcOutd  = NULL;   // Task 3 ProcessOutdoorInfo Handle
TaskHandle_t xTaskHandleWrUart6   = NULL;   // Task 4 Write_Uart6 Handle
TaskHandle_t xTaskHandlePrintErr  = NULL;   // Task 5 PrintError
TaskHandle_t xTaskHandleHeartBeat = NULL;   // Task 6 OLED Heartbeat 21.4.19
TaskHandle_t xTaskHandleUart6CmdH = NULL;   // Task 7 Uart6 CmdHandling 21.4.19
TaskHandle_t xTaskHandleUart6CmdP = NULL;   // Task 8 Uart6 CmdProcess 21.4.19
TaskHandle_t xTaskHandleDisplayLCD = NULL;   // Task 9 Display LCDhandle 21.8.2019

//Queue handle
QueueHandle_t packet_queue       = NULL;   // ok packets queue handle
QueueHandle_t output_write_queue = NULL;   // output write queue handle
QueueHandle_t command_queue      = NULL;   // comandos via UART6 Terminal

//software timer handle
TimerHandle_t led_timer_handle = NULL;

// Mutex handle declaration
SemaphoreHandle_t xMutex       = NULL;    // Protects sensor_data

// Binary Semaphore Handle
SemaphoreHandle_t xSem1        = NULL;

// Para CL3_FREETOS_Init()
osThreadId defaultTaskHandle;

// Tareas de U_LL5 04.19

void CL3_FREERTOS_Init(void) {
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
}

void StartDefaultTask(void const * argument)
{
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
}
// RTOSi - Implementacion de Task handlers
// TP Final R.Oliva 2019

// Task 1 - Display Menu por UART6
void vTask_Display(void *params)
{
char *pData = menu;
#ifdef DEBUG_VERBOSE
printmsg("\n\rTsk1");
#endif
vTaskDelay(20);
	while(1)
	{
		xQueueSend(output_write_queue,&pData,portMAX_DELAY);

		//Esperar indefinidamente.
		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);
		vTaskDelay(pdMS_TO_TICKS(50)); //23.4.19

	}
}

// Task2 vTask_Check_Meteo_packet - Verifica lo que llega
// de METEO por UART1, y lo pasa a la cola de paquetes ok
// En modo Demo, envía cada 1000 ms un paquete de muestra
// espera notificación de un paquete via UART1
// 27.4.2019 Sacamos modo Demo, solo String ISR_UART1
// Copiado y pasado al Packet queue, delay 0
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
//      TestCStr[] = "UUU$29335.10156.2562.15100.125.dfbe*QQQ";
// 27.4.2019 nuevo ISR detecta $ y copia hasta *, reemplaza este por un /0 termination..


void vTask_Check_Meteo_packet(void *params)
{
//	typedef struct PACKET_OK
//	{
//	  char packet_content[PACK_OK_LEN+2];
//	} PACKET_OK_t;
// PACKET_OK_t new_packet; // (as global)
//
#ifdef DEBUG_VERBOSE
   printmsg("\n\rTsk2");
#endif
//vTaskDelay(20);
	while(1)
	{
        // 27.4.2019 - Sacamos modo Demo, esperamos String de ISR_UART1
		// se utiliza xTskNotfromISR() allí.
		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);

		// Cada 0.5 seg - enviaba string de prueba
		// vTaskDelay(pdMS_TO_TICKS(500));

		// 1. allocate space.. Not used
	    // new_packet = (PACKET_OK_t*) pvPortMalloc(sizeof(PACKET_OK_t));

		taskENTER_CRITICAL();

		// packet_buffer es generado por la ISR hasta que encuentra el caracter '*' de terminación
		// nuevo packet 27.4.19 desde '$? hasta '*' con null termination
		strncpy(new_packet.packet_content, (char *)(packet_buffer),PACK_OK_LEN);

        #ifdef DEMO_STRING_COPIED
		// Copiamos uno de muestra (corregido 25.42019)
	    // char okTestCStr[] = "UUU$29335.10156.2562.15100.125.dfbe";
		strncpy(new_packet.packet_content, okTestCStr,PACK_OK_LEN);
        #endif

		taskEXIT_CRITICAL();

		xQueueSend(packet_queue,&new_packet, portMAX_DELAY);
		// 24.4.2019 Delay
		vTaskDelay(pdMS_TO_TICKS(50));
	}

}

// Task3 vTask_Process_OutdoorInfo - el paquete
// de METEO por UART1 es procesado para sacar la info
// 24.4.2019
// Menu por USART 6
// Nuevo menu 24.4.2019
// char menu[]={"
// Imprime Viento de METEO   ----> 1
// Imprime TempExterior MET  ----> 2
// Imprime DirViento METEO   ----> 3
// Imprime Info S Completo MET---> 4
// nDetener e imprimir Menu   ----> 0
// 24.4.19 Copiar datos a
// Control
// int16_t  g_chk = 0;
// in t16_t  g_items = 0;
//    V_SENSOR_t sensor_val;
//typedef struct sensor_holder {
//        int16_t IS_Aero;      // Current in 0-5V - Sampled
//        int16_t Vs_Vbat;      // Bat. Voltage in 0-5V - Sampled
//        int16_t Vs_OWind;     // OutDoor Wind Freq [Hz] from METEO / COM1
//        int16_t Vs_OWDir;     // OutDoor WindDirection 0-360.0 [º] from METEO / COM1
//        int16_t Vs_OTemp;     // External Temp 0-5V from METEO+NOMAD2/COM1
//        int16_t Vs_OBaro;     // Barometric Pressure 0-5V from METEO+NOMAD2/COM1
// V_SENSOR_t;
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
//      MAXLEN without UUU is 31
//      TestCStr[] = "UUU$29335.10156.2562.15100.125.1095*QQQ";


void vTask_Process_OutdoorInfo(void *params)
{
	// PACKET_OK_t *new_packet;
	// char task_msg[50];
	// char out_id[6];
	uint16_t chk = 0;
    int16_t items = 0;
	int16_t out_t =0;
	int16_t out_b = 0;
	int16_t out_w_speed = 0;
	int16_t out_vbat = 0;
    int16_t out_w_dir = 0;
	uint16_t checksum = 0;  // temporary variables 25.4.19 checksum unsigned
	//uint32_t toggle_duration = pdMS_TO_TICKS(500);
    #ifdef DEBUG_VERBOSE
	 printmsg("\n\rTsk3");
    #endif

	while(1)
	{
		xQueueReceive(packet_queue,(void*)&new_packet,portMAX_DELAY);
        // printmsg("\n\r1");

		// 27.4.2019 Now UART1 ISR starts detection from '$' and ends in '*'
		// So out_id is not required..
		// Start from out_t
		items = sscanf(new_packet.packet_content,"%5hd.%5hd.%4hd.%5hd.%3hd.%4hx",&out_t,
		 &out_b, &out_w_dir,&out_w_speed, &out_vbat,&checksum);
		
		// print_items_message(items);
		// void print_items_message(char *task_msg, int16_t items)
		// sprintf("\n\r I %d, o_v %d", items, out_vbat);
		// printmsg(task_msg);
		
		chk = out_t + out_b + out_w_dir;
	    chk += out_w_speed + out_vbat;

	    // Protect Access
        xSemaphoreTake(xMutex, portMAX_DELAY);

        sensor_val.Vs_OTemp = out_t;
        sensor_val.Vs_OBaro = out_b;
        sensor_val.Vs_OWind = out_w_speed;
        sensor_val.Vs_OWDir = out_w_dir;
        g_checksum = checksum;
        g_chk = chk;
        g_items = items;

        xSemaphoreGive(xMutex);

        /* solucion anterior
	    if((chk == checksum) && (items == 7))
		{
		print_Wind_Speed(task_msg, out_w_speed);
		}
		else
		{
		print_error_message(task_msg);
		}
		*/
		// enviar a QB_output a Terminal, delay 0
		// xQueueSend(output_write_queue,&task_msg, portMAX_DELAY);

		// liberar memoria de new_packet - ya no usado
		// vPortFree(new_packet);
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

// Task5 vTask_PrintError solo en caso de recepcion erronea UART1
// 27.4.2019 _Incrementa contador de errores global, no envía a imprimir
void vTask_PrintError(void *params)
{
	// char pData[] = "Error en Recepcion";
	printmsg("\n\rTsk5");
	vTaskDelay(20);
	while(1)
	{
		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);


		// Protect Access, increment counter
        xSemaphoreTake(xMutex, portMAX_DELAY);
        g_Rx_Errors++;
        xSemaphoreGive(xMutex);
        // Counter can be later printed with Task UART6
		// xQueueSend(output_write_queue,&pData,portMAX_DELAY);

		vTaskDelay(pdMS_TO_TICKS(50));
	}

}



// Task6 vTask_Write_UART6 todo lo que llega a la cola de output va a la UART6 a 115200
void vTask_Write_Uart6(void *params)
{
	char *pData = NULL;
	printmsg("\n\rTs4..");
	vTaskDelay(20);
	while(1)
	{

        xQueueReceive(output_write_queue,&pData,portMAX_DELAY);
		printmsg(pData);
		vTaskDelay(pdMS_TO_TICKS(50));

	}
}

// Task 6 = OLED Heartbeat 21.4.19
void vTask_HeartBeat(void *params)
{

	while(1){
		vTaskDelay(pdMS_TO_TICKS(500));
		// OLED_GPIO_Port, OLED_Pin
		LL_GPIO_TogglePin(OLED_GPIO_Port,OLED_Pin);
	}
}

// void vTask_uart6_cmd_handling - decodifica el comando que le llega del usuario
// a traves de terminal UART6, según el menu, y lo manda a la cola de comandos
void vTask_uart6_cmd_handling(void *params)   // Task 7 = Terminal UART6 Cmd_Handling
{
	uint8_t command_code=0;
	APP_CMD_t *new_cmd;
	char dbg_msg[20];

	while(1)
	{
		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);
		//1. send command to queue
		#ifdef DEBUG_USART6
			sprintf(dbg_msg,"\r\nRxCmh");
			printmsg(dbg_msg);
		#endif
		new_cmd = (APP_CMD_t*) pvPortMalloc(sizeof(APP_CMD_t));

		taskENTER_CRITICAL();
		command_code = getCommandCode(command_buffer);
		new_cmd->COMMAND_NUM = command_code;
		getArguments(new_cmd->COMMAND_ARGS);
		taskEXIT_CRITICAL();
		#ifdef DEBUG_USART6
			sprintf(dbg_msg,"\r\n Cm%d",command_code);
			printmsg(dbg_msg);
		#endif
		// enviar al command queue 21.4.19
		xQueueSend(command_queue,&new_cmd,portMAX_DELAY);
		vTaskDelay(pdMS_TO_TICKS(50));
	}
}


// Task 8 void vTask_uart6_cmd_processing - ejecuta los comandos de la cola
// de comandos alimentada por el task anterior
// int16_t out_t =0;
// int16_t out_b = 0;
// int16_t out_w_speed = 0;
// int16_t out_vbat = 0;
// int16_t out_w_dir = 0;
// uint16_t checksum = 0;  // temporary variables
// Valores del String transmitido por METEO:
// v6 for use with METEO v20 uses packet "UUU$ttttt.bbbbb.dddd.sssss.vvv.CRCC*QQQ":  (WSpeed is 5 chars long)
//      UUU$   start identifier
//      ttttt is 00000 08191 Raw Temperature ADC reading, can be 0-5V( Direct sensor with G=2) or 1-5V (4-20mA)
//      bbbbb is 00000 08191 Raw BaroPressure ADC reading, can be 0-5V( Direct sensor with G=1) or 1-5V (4-20mA)
//      dddd  is 0000 to 3600, WDIR*10 in UWORD
//      sssss is 00000 to 99999 from Anemometer / Thies.
//      vvv   was voltage, not used.
//      CRCC  is simple checksum
//      *QQQ  end identifier
// Si se usa el de muestra:
// char okTestCStr[] = "UUU$29335.10156.2562.15100.125.1095";
//  Imprime Viento de METEO   ----> 1
//  Imprime TempExterior MET  ----> 2
//  Imprime DirViento METEO   ----> 3
//  Imprime Info String MET    ---> 4
//  Impresion continua         ---> 5
//  Detener e imprimir Menu   ----> 0
//  Tipee su opcion : "};

// Task 8 = Terminal UART6 proceso comandos

void vTask_uart6_cmd_processing(void *params)
{
	APP_CMD_t *new_cmd;
	char task_msg[100];
	static uint8_t local_command_sel = 1;
	uint16_t u6chk = 0;
    int16_t u6items = 0;
    int16_t outtemp=0;
	int16_t u6outbaro = 0;
	int16_t u6outwindspeed = 0;
    int16_t u6outwinddir = 0;
	uint16_t u6checksum = 0;
	uint32_t u6_Rx_Errors; // Added 27.4.2019 from Task 5
    TickType_t QDelay = portMAX_DELAY;
	// pdMS_TO_TICKS(2000)

	while(1)
	{
		xQueueReceive(command_queue,(void*)&new_cmd, QDelay );

		#ifdef DEBUG_USART6
			sprintf(task_msg,"\r\n C_N:%d", new_cmd->COMMAND_NUM);
			printmsg(task_msg);
		#endif

	    xSemaphoreTake(xMutex, portMAX_DELAY);
	    outtemp = sensor_val.Vs_OTemp;
	    u6outbaro = sensor_val.Vs_OBaro;
	    u6outwindspeed = sensor_val.Vs_OWind;
	    u6outwinddir = sensor_val.Vs_OWDir;
	    u6checksum = g_checksum;
	    u6chk  = g_chk;
	    u6items = g_items;
	    u6_Rx_Errors= g_Rx_Errors; // Added 27.4.2019 from Task 5
	    xSemaphoreGive(xMutex);

		if(new_cmd->COMMAND_NUM == 1)
		{
			//print_Uart6_messageCmd1(task_msg);
			print_Wind_Speed(task_msg, u6outwindspeed);
			QDelay = portMAX_DELAY;
		}
		else if(new_cmd->COMMAND_NUM == 2)
		{
			print_Out_Temp(task_msg, outtemp);
			QDelay = portMAX_DELAY;
		}
		else if(new_cmd->COMMAND_NUM == 3)
		{
			print_Wind_Dir(task_msg, u6outwinddir);
			QDelay = portMAX_DELAY;
		}
		else if(new_cmd->COMMAND_NUM == 4 )
		{
			print_String_Items(task_msg, u6checksum, u6chk, u6items);
			QDelay = portMAX_DELAY;
		}
		else if(new_cmd->COMMAND_NUM == 5 )
		{
//		print_String_Complete(char *task_msg,
//					int16_t temp,
//					int16_t wsp,
//					int16_t wdir,
//					uint16_t u6checksum,
//					uint16_t u6chk,
//					int16_t u6items
//                  uint32_t u6_Rx_Errors)
			local_command_sel = 1;
			print_String_Complete(task_msg,outtemp,u6outwindspeed,u6outwinddir,u6checksum,u6chk,u6items, u6_Rx_Errors);
			// Para impresión continua, cambiamos a 1000 Ticks, ojo no hacer vMallocfree..
			QDelay = pdMS_TO_TICKS(1000);
            // Autosend command 5..
			// new_cmd->COMMAND_NUM = 5;
			// xQueueSend(command_queue,&new_cmd,portMAX_DELAY);
		} else
		{
			local_command_sel = 0;
			QDelay = portMAX_DELAY;
			print_Uart6_error_message(task_msg);
		}

		// liberar memoria asignada a new_cmd, solo si estamos recibiendo
		// por Puerto Serie: Si no llegó nada (Delay < PortMaxDelay) no libere
		if (QDelay == portMAX_DELAY){
		 vPortFree(new_cmd);
		}
		vTaskDelay(pdMS_TO_TICKS(50));
		// Llamar al menu solo si comando no reconocido
		if (local_command_sel == 0){
			xTaskNotify(xTaskHandleDisplay,0,eNoAction);
			local_command_sel = 1;
		}
	}
}

// Task 9 vTask_DisplayLCD - maneja pantallas
void vTask_DisplayLCD(void *params)
{
bool_t valor = 0;
#define CTR_DMAX 100
int16_t winddir = 0;
uint8_t disp_status = 0;
uint16_t disp_counter = CTR_DMAX;
char task_msg[100];
#ifdef DEBUG_VERBOSE
printmsg("\n\rTsk9");
#endif
vTaskDelay(20);
	while(1)
	{
		xSemaphoreTake(xMutex, portMAX_DELAY);
		winddir = sensor_val.Vs_OWDir;
		xSemaphoreGive(xMutex);

		valor = !gpioRead(KBD_IZQ);  // Sin debounce
		if(valor) {  //F1
			WDir_Screen(task_msg, winddir);    // Definido en general.c
			disp_counter = CTR_DMAX;
			disp_status = 1;
		}
		valor = !gpioRead(KBD_ARR);
		if(valor) {  //F2
			displaycl3_Screen(SCREEN2);
			disp_counter = CTR_DMAX;
			disp_status = 2;
		}
		valor = !gpioRead(KBD_ABJ);
		if(valor) {   // F3
			displaycl3_Screen(SCREEN3);
			disp_counter = CTR_DMAX;
			disp_status = 3;
		}
		valor = !gpioRead(KBD_DER);
		if(valor) { // F4
			displaycl3_Screen(SCREEN4);
			disp_counter = CTR_DMAX;
			disp_status = 4;
		}
		if (disp_counter) { // If #1
			disp_counter--;
			switch(disp_status){
			case 1:
				WDir_Update(task_msg, winddir);
				break;
			default:
				break;
			}   // end switch
			if (disp_counter == 0)
				{
				displaycl3_Screen(WELCOME);
				}
		} // end if #1
		vTaskDelay(pdMS_TO_TICKS(200)); //
	}
}
  







