#include <FreeRTOS.h>
#include <stdint.h>
#include <stdio.h>
#include <task.h>
#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include "MCAL/DIO/DIO.h"
#include <semphr.h>
#include "queue.h"
#include "motor.h"

void switchTask();
void upDownDriverAuto();
void upDownDriverManual();
void upDownPassengerAuto();
void upDownPassengerManual();
void Jam();