#ifndef TIMER_H_
#define TIMER_H_


#include "../../tm4c123gh6pm.h"
#include "../../bitwise_operation.h"

typedef enum{false, true} bool;

void delay_ms(unsigned long delay);
void delay_s(unsigned long delay);
void delay_one_second();

void SysTickDisable(void);
void SysTickEnable(void);
unsigned long SysTickPeriodGet(void);
void SysTickPeriodSet(unsigned long ui32Period);
unsigned long SysTickValueGet(void);
bool SysTick_Is_Time_out(void);

#endif