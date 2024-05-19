#include "control.h"

extern xQueueHandle xQueuePD;

extern xTaskHandle switchTaskHandle;
extern xTaskHandle upDownDriverAutoHandler;
extern xTaskHandle upDownDriverManualHandler;
extern xTaskHandle upDownPassengerAutoHandler;
extern xTaskHandle upDownPassengerManualHandler;
extern xTaskHandle JamHandler;

extern xSemaphoreHandle xBinarySemaphoreDriverAuto;
extern xSemaphoreHandle xBinarySemaphoreDriverManual;
extern xSemaphoreHandle xBinarySemaphorePassengerAuto;
extern xSemaphoreHandle xBinarySemaphorePassengerManual;
extern xSemaphoreHandle xBinarySemaphoreJam;

int Locked = 0;

void delayMs(unsigned long n)
{
  volatile unsigned long i,j;             
	for(i=0;i<n;i++)
		for(j=0;j<3180;j++)         
		{}
}

void Jam()
{
	while(1)
	{
		xSemaphoreTake(xBinarySemaphoreJam,portMAX_DELAY); 
		Stop_Motor();
		Down_Motor();
		delayMs(500);
		Stop_Motor();
		vTaskPrioritySet(NULL,2);
		taskYIELD();
	}
}

void upDownDriverAuto()
{
	int direction;
	while(1)
	{
			xSemaphoreTake(xBinarySemaphoreDriverAuto, portMAX_DELAY);
	 
			xQueueReceive(xQueuePD,&direction ,portMAX_DELAY);
		
			if(direction == 1)
				{
					Up_Motor();
					while( (Get_Bit(GPIO_PORTD_DATA_R, 3) == 0) && (Get_Bit(GPIO_PORTB_DATA_R, 1) == 0) && (Get_Bit(GPIO_PORTD_DATA_R, 1) == 0) );
					if(Get_Bit(GPIO_PORTD_DATA_R, 3) == 1){
						xSemaphoreGive(xBinarySemaphoreJam);
						vTaskPrioritySet(JamHandler, 3);
					}
					int x = 0;
				}else if (direction == 0)
				{
						Down_Motor();
						while( (Get_Bit(GPIO_PORTB_DATA_R, 2) == 0) && (Get_Bit(GPIO_PORTD_DATA_R, 0) == 0));
						int x = 0;
				}
			Stop_Motor();
			taskYIELD();
	}
}

void upDownDriverManual()
{
    int direction;
    while(1)
    {
            xSemaphoreTake(xBinarySemaphoreDriverManual, portMAX_DELAY);

            xQueueReceive(xQueuePD, &direction, portMAX_DELAY);

            if(direction == 1)
                {
                    Up_Motor();
                    while( (Get_Bit(GPIO_PORTD_DATA_R, 3) == 0) && (Get_Bit(GPIO_PORTB_DATA_R, 1) == 0) && (Get_Bit(GPIO_PORTD_DATA_R, 0) == 1) );
                }
                else if (direction == 0)
                {
                        Down_Motor();
                        while( (Get_Bit(GPIO_PORTB_DATA_R, 2) == 0) && (Get_Bit(GPIO_PORTD_DATA_R, 1) == 1));
                }
            Stop_Motor();
            taskYIELD();
    }
}

void upDownPassengerAuto()
{
    int direction;
    while(1)
    {
            xSemaphoreTake(xBinarySemaphorePassengerAuto, portMAX_DELAY);

            xQueueReceive(xQueuePD,&direction ,portMAX_DELAY);

            if(direction == 1)
                {
                    Up_Motor();
                    while( (Get_Bit(GPIO_PORTD_DATA_R, 3) == 0) && (Get_Bit(GPIO_PORTB_DATA_R, 1) == 0) && (Get_Bit(GPIO_PORTD_DATA_R, 1) == 0) && (Get_Bit(GPIO_PORTD_DATA_R, 0) == 0) && (Get_Bit(GPIO_PORTD_DATA_R, 2) == 0) && (Get_Bit(GPIO_PORTD_DATA_R, 7) == 0));
                    if(Get_Bit(GPIO_PORTD_DATA_R, 3) == 1){//jam
												xSemaphoreGive(xBinarySemaphoreJam);
												vTaskPrioritySet(JamHandler, 3);
                    }
										if(Get_Bit(GPIO_PORTD_DATA_R, 2) == 1)
										{
											if(Locked == 0)
													Locked =1;
											else
													Locked = 0;
										}
                    int x = 0;
                }else if (direction == 0)
                {
                        Down_Motor();
                        while( (Get_Bit(GPIO_PORTB_DATA_R, 2) == 0) && (Get_Bit(GPIO_PORTD_DATA_R, 1) == 0) && (Get_Bit(GPIO_PORTD_DATA_R, 0) == 0) && (Get_Bit(GPIO_PORTD_DATA_R, 2) == 0) && (Get_Bit(GPIO_PORTD_DATA_R, 6) == 0) );
                        if(Get_Bit(GPIO_PORTD_DATA_R, 2) == 1)
												{
													if(Locked == 0)
															Locked =1;
													else
															Locked = 0;
												}
												int x = 0;
                }
            Stop_Motor();
            taskYIELD();
    }
}

void upDownPassengerManual()
{
    int direction;
    while(1)
    {
            xSemaphoreTake(xBinarySemaphorePassengerManual, portMAX_DELAY);

            xQueueReceive(xQueuePD, &direction, portMAX_DELAY);

            if(direction == 1)
                {
                    Up_Motor();
                    while( (Get_Bit(GPIO_PORTD_DATA_R, 3) == 0) && (Get_Bit(GPIO_PORTB_DATA_R, 1) == 0) && (Get_Bit(GPIO_PORTD_DATA_R, 0) == 0) && (Get_Bit(GPIO_PORTD_DATA_R, 1) == 0) && (Get_Bit(GPIO_PORTD_DATA_R, 6) == 1) && (Get_Bit(GPIO_PORTD_DATA_R, 2) == 0));
                    if(Get_Bit(GPIO_PORTD_DATA_R, 2) == 1)
										{
											if(Locked == 0)
													Locked =1;
											else
													Locked = 0;
										}
										int x = 0;
                }
                else if (direction == 0)
                {
                        Down_Motor();
                        while( (Get_Bit(GPIO_PORTB_DATA_R, 2) == 0) && (Get_Bit(GPIO_PORTD_DATA_R, 0) == 0) && (Get_Bit(GPIO_PORTD_DATA_R, 1) == 0) && (Get_Bit(GPIO_PORTD_DATA_R, 7) == 1) && (Get_Bit(GPIO_PORTD_DATA_R, 2) == 0));
                        if(Get_Bit(GPIO_PORTD_DATA_R, 2) == 1)
												{
													if(Locked == 0)
															Locked =1;
													else
															Locked = 0;
												}
												int x = 0;
                }
            Stop_Motor();
            taskYIELD();
    }
}


void switchTask()
{
	int up =1;
	int down =0;
	int driver_auto_flag = 0;
	int passenger_auto_flag = 0;
	xQueuePD = xQueueCreate(1 , sizeof(long));
	
	
	while(1){
		
		if(Get_Bit(GPIO_PORTD_DATA_R, 0) == 1){ 			// Driver up
			xQueueSend(xQueuePD, &up, 0);	
			
			driver_auto_flag = 1;
			delayMs(1000);
			if(Get_Bit(GPIO_PORTD_DATA_R, 0) == 1)
				{
					driver_auto_flag = 0;
					Toggle_Bit(GPIO_PORTF_DATA_R, 1);
					xSemaphoreGive(xBinarySemaphoreDriverManual);
				}
	
		}else if(Get_Bit(GPIO_PORTD_DATA_R, 1) == 1){		// Driver down
			xQueueSend(xQueuePD, &down, 0);	
			
					driver_auto_flag = 1;
					delayMs(1000);
					if(Get_Bit(GPIO_PORTD_DATA_R, 1) == 1)
					{
						driver_auto_flag = 0;
						Toggle_Bit(GPIO_PORTF_DATA_R, 1);
						xSemaphoreGive(xBinarySemaphoreDriverManual);
					}
		}
		else if(Get_Bit(GPIO_PORTD_DATA_R, 6) == 1 && !Locked){		// passenger up
			xQueueSend(xQueuePD, &up, 0);	
			
			passenger_auto_flag = 1;
			delayMs(1000);
			if(Get_Bit(GPIO_PORTD_DATA_R, 6) == 1)
				{
					passenger_auto_flag = 0;
					Toggle_Bit(GPIO_PORTF_DATA_R, 1);
					xSemaphoreGive(xBinarySemaphorePassengerManual);
				}
		}
		else if(Get_Bit(GPIO_PORTD_DATA_R, 7) == 1 && !Locked){		// passenger down
			xQueueSend(xQueuePD, &down, 0);	
			
			passenger_auto_flag = 1;
			delayMs(1000);
			if(Get_Bit(GPIO_PORTD_DATA_R, 7) == 1)
				{
					passenger_auto_flag = 0;
					Toggle_Bit(GPIO_PORTF_DATA_R, 1);
					xSemaphoreGive(xBinarySemaphorePassengerManual);
				}
	
		}
		else if(Get_Bit(GPIO_PORTD_DATA_R, 2) == 1){		// lock	
			if(Locked == 0)
					Locked =1;
			else
					Locked = 0;
			delayMs(100);
			Toggle_Bit(GPIO_PORTF_DATA_R, 2);
		}
		if (driver_auto_flag )
		{
			driver_auto_flag = 0;
			Toggle_Bit(GPIO_PORTF_DATA_R, 3);
			xSemaphoreGive(xBinarySemaphoreDriverAuto);
		}else if (passenger_auto_flag)
		{
			passenger_auto_flag = 0;
			Toggle_Bit(GPIO_PORTF_DATA_R, 3);
			xSemaphoreGive(xBinarySemaphorePassengerAuto);
		}
		
	}
}
