#include "motor.h"

void Up_Motor()
{
	GPIO_PORTA_DATA_R = 0x04;
}

void Stop_Motor()
{
	GPIO_PORTA_DATA_R = 0x00;
}

void Down_Motor()
{
	GPIO_PORTA_DATA_R = 0x08;
}