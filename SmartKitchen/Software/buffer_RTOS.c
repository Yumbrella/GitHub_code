#include "buffer_RTOS.h"

#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "semphr.h"
#include "buffer.h"



extern sbuffer ATbuf;
extern sbuffer DATAbuf;
extern SemaphoreHandle_t sem_ATSendOfRec;
extern SemaphoreHandle_t mutexATData;

void buffer_OS_Read(char *s,int timeout)
{
	while(1)
	{	
		xSemaphoreTake(sem_ATSendOfRec,portMAX_DELAY);
		Buffer_Read(s,&ATbuf);
		return ;
	}
	
}

void buffer_Data_Read(char *s,int timeout)
{
	while(1)
	{	
		xSemaphoreTake(mutexATData,portMAX_DELAY);
		Buffer_Read(s,&DATAbuf);
		return ;
	}
}
	


