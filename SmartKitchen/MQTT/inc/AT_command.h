#ifndef __AT_command_H
#define __AT_command_H

#include "FreeRTOS.h"
#include "semphr.h"

extern SemaphoreHandle_t mutexATSendOfResult;

void AT_Init();
void AT_Task_Parser(void *param);
int AT_Send_Command(char *abuf,char *resp,int timeout);





#endif
