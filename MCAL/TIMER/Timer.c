#include "Timer.h"

void delay_ms(unsigned long delay)
{
  
    SysTickPeriodSet((unsigned long) (delay * 16000) - 1);

    SysTickEnable();
    Set_Bit(NVIC_ST_CTRL_R, 2);

    Set_Bit(NVIC_ST_CTRL_R, 1);
    NVIC_ST_CURRENT_R = 0x000000;
}

void delay_s(unsigned long delay)
{
  for(unsigned long i = 0; i < delay; i++)
  {
    delay_one_second();
  }
}

void delay_one_second()
{
   SysTickPeriodSet((unsigned long) (16000000) - 1);

    SysTickEnable();
    Set_Bit(NVIC_ST_CTRL_R, 2);
    Set_Bit(NVIC_ST_CTRL_R, 1);
  
  
    NVIC_ST_CURRENT_R = 0x000000;
}

void SysTickDisable(void)
{
  Clear_Bit(NVIC_ST_CTRL_R, 0);
}

void SysTickEnable(void)
{
  Set_Bit(NVIC_ST_CTRL_R, 0);
}

unsigned long SysTickPeriodGet(void)
{
  return NVIC_ST_RELOAD_R;
}

void SysTickPeriodSet(unsigned long ui32Period)
{
  NVIC_ST_RELOAD_R = ui32Period;
}

unsigned long SysTickValueGet(void)
{
  return NVIC_ST_CURRENT_R;
}

bool SysTick_Is_Time_out(void)
{
  return Get_Bit(NVIC_ST_CTRL_R, 16);
}