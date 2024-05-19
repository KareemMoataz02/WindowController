#include "DIO.h"


void DIO_Init(port_type port, pin_type pin)
{
  SYSCTL_RCGCGPIO_R |= 1 << pin;
  
  switch(port)
  {
  case DIO_PORTC: GPIO_PORTC_LOCK_R = 0x4C4F434B;
    break;
  case DIO_PORTD: GPIO_PORTD_LOCK_R = 0x4C4F434B;
    break;
  case DIO_PORTF: GPIO_PORTF_LOCK_R = 0x4C4F434B;
    break;
  default:
    break;
  }
}

void DIO_WritePin(port_type port, pin_type pin, state_type state)
{
  switch(port)
  {
  case DIO_PORTA:
        (state == HIGH)? Set_Bit(GPIO_PORTA_DATA_R, pin) : Clear_Bit(GPIO_PORTA_DATA_R,pin);
        break;
    
  case DIO_PORTB:
      (state == HIGH)? Set_Bit(GPIO_PORTB_DATA_R, pin) : Clear_Bit(GPIO_PORTB_DATA_R,pin);
      break;
    
  case DIO_PORTC:
      (state == HIGH)? Set_Bit(GPIO_PORTC_DATA_R, pin) : Clear_Bit(GPIO_PORTC_DATA_R,pin);
      break;
    
  case DIO_PORTD:
      (state == HIGH)? Set_Bit(GPIO_PORTD_DATA_R, pin) : Clear_Bit(GPIO_PORTD_DATA_R,pin);
      break;
    
  case DIO_PORTE:
      (state == HIGH)? Set_Bit(GPIO_PORTE_DATA_R, pin) : Clear_Bit(GPIO_PORTE_DATA_R,pin);
      break;
    
  case DIO_PORTF:
      (state == HIGH)? Set_Bit(GPIO_PORTF_DATA_R, pin) : Clear_Bit(GPIO_PORTF_DATA_R,pin);
    break;
  }
}

void DIO_WritePort(port_type port, pin_type pin, dir_type dir)
{
  switch(port)
  {
  case DIO_PORTA: (dir == OUTPUT)? Set_Bit(GPIO_PORTA_DIR_R, pin) : Clear_Bit(GPIO_PORTA_DIR_R,pin);
    break;
  case DIO_PORTB: (dir == OUTPUT)? Set_Bit(GPIO_PORTB_DIR_R, pin) : Clear_Bit(GPIO_PORTB_DIR_R,pin);
    break;
  case DIO_PORTC: (dir == OUTPUT)? Set_Bit(GPIO_PORTC_DIR_R, pin) : Clear_Bit(GPIO_PORTC_DIR_R,pin);
    break;
  case DIO_PORTD: (dir == OUTPUT)? Set_Bit(GPIO_PORTD_DIR_R, pin) : Clear_Bit(GPIO_PORTD_DIR_R,pin);
    break;
  case DIO_PORTE: (dir == OUTPUT)? Set_Bit(GPIO_PORTE_DIR_R, pin) : Clear_Bit(GPIO_PORTE_DIR_R,pin);
    break;
  case DIO_PORTF: (dir == OUTPUT)? Set_Bit(GPIO_PORTF_DIR_R, pin) : Clear_Bit(GPIO_PORTF_DIR_R,pin);
    break;
  }

}

state_type DIO_ReadPin(port_type port, pin_type pin)
{
    state_type state_temp;
	
    switch(port)
    {
    case DIO_PORTA: state_temp =  Get_Bit(GPIO_PORTA_DATA_R, pin);
      break;
    case DIO_PORTB: state_temp =  Get_Bit(GPIO_PORTB_DATA_R, pin);
      break;
    case DIO_PORTC: state_temp =  Get_Bit(GPIO_PORTC_DATA_R, pin);
      break;
    case DIO_PORTD: state_temp =  Get_Bit(GPIO_PORTD_DATA_R, pin);
      break;
    case DIO_PORTE: state_temp =  Get_Bit(GPIO_PORTE_DATA_R, pin);
      break;
    case DIO_PORTF: state_temp =  Get_Bit(GPIO_PORTF_DATA_R, pin);
      break;
    }

     return state_temp;
}

dir_type DIO_ReadPort(port_type port, pin_type pin)
{
  dir_type temp = INPUT;
  switch(port)
  {
  case DIO_PORTA: temp = (Get_Bit(GPIO_PORTA_DIR_R,pin)) ? OUTPUT : INPUT;
    break;
  case DIO_PORTB: temp = Get_Bit(GPIO_PORTB_DIR_R,pin) ? OUTPUT : INPUT;
    break;
  case DIO_PORTC: temp = Get_Bit(GPIO_PORTC_DIR_R,pin) ? OUTPUT : INPUT;
    break;
  case DIO_PORTD: temp = Get_Bit(GPIO_PORTD_DIR_R,pin) ? OUTPUT : INPUT;
    break;
  case DIO_PORTE: temp = Get_Bit(GPIO_PORTE_DIR_R,pin) ? OUTPUT : INPUT;
    break;
  case DIO_PORTF: temp = Get_Bit(GPIO_PORTF_DIR_R,pin) ? OUTPUT : INPUT;
    break;
  }
  return temp;
}