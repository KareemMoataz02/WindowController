#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"

#include "MCAL/DIO/DIO.h"
#include "bitwise_operation.h"

void Up_Motor();
void Stop_Motor();
void Down_Motor();