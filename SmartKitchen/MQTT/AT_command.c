#include "AT_command.h"
#include "FreeRTOS.h"
#include "serial.h"
#include "buffer_RTOS.h"
#include "buffer.h"
#include <string.h>
#include <stdio.h>
#include "semphr.h"

#define SUBNAME "yry333"

SemaphoreHandle_t mutexATSendOfResult;	//主动发送AT命令后返回结果的锁
SemaphoreHandle_t mutexATData;			//接收服务器的数据后存到数据环形区的信号量

/*
*	0 err
*	1 ok	
* 	2 timeout
*/
unsigned char ATStatus;
extern sbuffer DATAbuf;

char rbuf[256];

char g_at_resp[128];


void AT_Init()
{
	 mutexATSendOfResult=xSemaphoreCreateBinary();
	 mutexATData=xSemaphoreCreateCounting(128,0);
}


/*发送AT命令后，会收OK或者其他*/
int AT_Send_Command(char *abuf,char *resp,int timeout)
{
	int ret;
	/* 发送AT命令 */
	
	Serial_Write(abuf,strlen(abuf));
	Serial_Write("\r\n",2);
	
	/* 
	* 得到锁，成功返回1 失败返回0
	*/
	ret=xSemaphoreTake(mutexATSendOfResult,timeout);
	if(ret)
	{
		/* 判断返回值 */
		if(ATStatus==1 && resp) //AT后，成功获得OK
		{
			strcpy(resp,g_at_resp);
			return 1;
			
		}else if(ATStatus==1)
		{
			return 1;
		}
		else return 0;	//	err
		
	}
	else return 2;	//超时
}



/*
* 需要解析特殊数据的函数
* 比如IPD
* 
*/
void ParserATString(char *s,int i)
{
	int len=0;
	int j=0;
	int status=0;
	while(1)
	{
		buffer_OS_Read(&s[i],portMAX_DELAY);
		if (s[i] >= '0'&& s[i] <= '9')
		{
			len = len * 10 + (s[i] - '0');
			status=1;
		}
		else if(status==1 && s[i] == ',')
		{
			i++;
			break;
		}
		i++;
	}
	
	
	while(1)
	{
		buffer_OS_Read(&s[i], portMAX_DELAY);
		/* 把数据放入环形buffer */
		Buffer_Write(s[i],&DATAbuf);
		i++;
		j++;
		xSemaphoreGive(mutexATData);
		if(j>=len+2)break;
		
				
	}
	
}



/* 	发送AT命令后，解析回收后的值
*	方法一 一行一行的解析
*	这也是一个监听端口的任务
*/
void AT_Task_Parser(void *param)
{
	int i=0;
	while(1)
	{
		//没有数据 阻塞自己
		buffer_OS_Read(&rbuf[i],portMAX_DELAY);
		rbuf[i+1]='\0'; //把每读到一个新的字符加结束符组成字符串
		//判断是否到了数据一行的末尾
		if(i&&rbuf[i]=='\n' && rbuf[i-1]=='\r')
		{
			//开始解析
			if(strstr(rbuf, "OK\r\n")!=NULL)
			{
				memcpy(g_at_resp,rbuf,i+1);
				ATStatus=1;
				i=0;
				xSemaphoreGive(mutexATSendOfResult);
			}
			else if (strstr(rbuf, "ERROR\r\n"))
			{
				memcpy(g_at_resp,rbuf,i+1);
				ATStatus=0;
				i = 0;
				xSemaphoreGive(mutexATSendOfResult);		
			}
			else 
			{
				i=0;
			}
		}else if(strstr(rbuf, SUBNAME)!=NULL)//解析主题
		{
			//转去新的函数接收数据 因为这不是命令的反馈
			ParserATString(rbuf,i+1);
			i = 0;
		}
		else
		{
			i++;
		}
		
		
	}
}



