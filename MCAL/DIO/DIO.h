#ifndef DIO_H_
#define DIO_H_

#include "../../tm4c123gh6pm.h"
#include "../../bitwise_operation.h"


typedef enum {DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD, DIO_PORTE, DIO_PORTF} port_type;
typedef enum {P0, P1, P2, P3, P4, P5, P6, P7} pin_type;
typedef enum {INPUT, OUTPUT} dir_type;
typedef enum {LOW, HIGH} state_type;


void DIO_Init(port_type port, pin_type pin);
void DIO_WritePin(port_type port, pin_type pin, state_type state);
void DIO_WritePort(port_type port, pin_type pin, dir_type dir);

state_type DIO_ReadPin(port_type port, pin_type pin);
dir_type DIO_ReadPort(port_type port, pin_type pin);


#endif