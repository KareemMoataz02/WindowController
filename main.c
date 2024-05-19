#include <FreeRTOS.h>
#include <stdint.h>
#include <stdio.h>
#include <task.h>
#include "TM4C123GH6PM.h"
#include "bitwise_operation.h"
#include "MCAL/DIO/DIO.h"
#include <Semphr.h>
#include "control.h"
#include "queue.h"
#include <semphr.h>

xQueueHandle xQueuePD;

xTaskHandle switchTaskHandle;
xTaskHandle upDownDriverAutoHandler;
xTaskHandle upDownDriverManualHandler;
xTaskHandle upDownPassengerAutoHandler;
xTaskHandle upDownPassengerManualHandler;
xTaskHandle JamHandler;


xSemaphoreHandle 	xBinarySemaphoreDriverAuto;
xSemaphoreHandle xBinarySemaphoreDriverManual;
xSemaphoreHandle xBinarySemaphorePassengerAuto;
xSemaphoreHandle xBinarySemaphorePassengerManual;
xSemaphoreHandle xBinarySemaphoreJam;


void vApplicationIdleHook()
{
	for( ;; )
	{
	}
}

void PORTF_init()
{
      DIO_Init(DIO_PORTF, P5);
      GPIO_PORTF_CR_R |= 0x1F;
      
      DIO_WritePort(DIO_PORTF, P1, OUTPUT);
      DIO_WritePort(DIO_PORTF, P2, OUTPUT);
      DIO_WritePort(DIO_PORTF, P3, OUTPUT);
      
      DIO_WritePort(DIO_PORTF, P0, INPUT);
      DIO_WritePort(DIO_PORTF, P4, INPUT);
      
      GPIO_PORTF_PUR_R |= 0x11;
      GPIO_PORTF_DEN_R |= 0x1F;      
}

void PORTD_init()
{
      DIO_Init(DIO_PORTD, P3);
      GPIO_PORTD_CR_R |= 0xFF;
      
      DIO_WritePort(DIO_PORTD, P0, INPUT);
      DIO_WritePort(DIO_PORTD, P1, INPUT);
      DIO_WritePort(DIO_PORTD, P2, INPUT);
      DIO_WritePort(DIO_PORTD, P3, INPUT);
      DIO_WritePort(DIO_PORTD, P6, INPUT);
			DIO_WritePort(DIO_PORTD, P7, INPUT);    
	
      GPIO_PORTD_DEN_R |= 0xFF; 
			GPIO_PORTD_PDR_R |= 0xFF;
	
}

void PORTB_init()
{
			DIO_Init(DIO_PORTB, P1);
			GPIO_PORTB_LOCK_R = 0x4C4F434B; 
			GPIO_PORTB_CR_R |= 0xFF;

			GPIO_PORTB_CR_R |= 0xFF; 
			GPIO_PORTB_DIR_R|= 0x00;
			GPIO_PORTB_PDR_R |= 0xFF;
			GPIO_PORTB_DEN_R|= 0xFF;
}

void PORTA_init()
{	
	SYSCTL_RCGCGPIO_R|=0x1;
  while((SYSCTL_PRGPIO_R & 0x1)!= 0x1); 
  GPIO_PORTA_LOCK_R = 0x4C4F434B; 
  GPIO_PORTA_CR_R = 0xFF; 
  GPIO_PORTA_DIR_R = 0x3F;
  GPIO_PORTA_PDR_R = 0xC0;
  GPIO_PORTA_DEN_R = 0xFF;
}

int main()
{
		PORTF_init();
		PORTD_init();
		PORTB_init();
		PORTA_init();
	
		xBinarySemaphoreDriverAuto = xSemaphoreCreateBinary();
		xBinarySemaphoreDriverManual = xSemaphoreCreateBinary();
		xBinarySemaphorePassengerAuto = xSemaphoreCreateBinary();
		xBinarySemaphorePassengerManual = xSemaphoreCreateBinary();
		xBinarySemaphoreJam = xSemaphoreCreateBinary();
	
		xTaskCreate(upDownDriverAuto,"upDownDriverAuto",130,NULL,2,&upDownDriverAutoHandler);
		xTaskCreate(upDownDriverManual,"upDownDriverManual",130,NULL,2,&upDownDriverManualHandler);
		xTaskCreate(upDownPassengerAuto,"upDownPassengerAuto",130,NULL,2,&upDownPassengerAutoHandler);
		xTaskCreate(upDownPassengerManual,"upDownPassengerManual",130,NULL,2,&upDownPassengerManualHandler);
	
		xTaskCreate(Jam,"Jam",130,NULL,2,&JamHandler);
	
		xTaskCreate(switchTask,"switchTask",130,NULL,1,&switchTaskHandle);
		
	
	vTaskStartScheduler();
	
	for (;;);
	
}
