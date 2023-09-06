#include "stm32f10x.h"                  // Device header

/* Standard includes. */
#include <stdio.h>
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "timers.h"

/* my */ 
#include "serial.h"
#include "buffer.h"
#include "semphr.h"
#include "AT_command.h"
#include "myusart2.h"
#include "AT_connect.h"
#include "AT_MQTT.h"
#include "buffer_RTOS.h"
#include "OLED.h"
#include "OLEDShow.h"
#include "DHT11.h"
#include "Delay.h"
#include "AD.h"
#include "Buzzer.h"
#include "LED.h"



#define WIFI "Mi_VIPuser"
#define WIFIPWD "123789789"
#define USER "myuser"
#define ID "yry000"
#define PWD "123456"
#define URL "e7b3ce0e.cn-shenzhen.emqx.cloud"
#define PORT "15594"
#define SUBNAME "yry333"
#define PUSNAME "yry222"

extern sbuffer ATbuf;
SemaphoreHandle_t sem_ATSendOfRec;	//用于所有接收缓存的信号量
extern SemaphoreHandle_t mutexATSendOfResult;
extern SemaphoreHandle_t mutexATData;
static TimerHandle_t timerKey1Handle;//按键消抖定时器
static TimerHandle_t timerMsgPageHandle;//按键消抖定时器

extern unsigned int humiture_data[4];
extern uint16_t ADValue[5];
char myRecStr[30];
extern char MyTime[4];

unsigned char page;
unsigned char warning=0;


char temperature[15]="tmpt:20.3C";
char humidity[15]="humi:20.3%";

char gas_smoke[15]="smoke:1234AD";
char gas_CH4[15]="CH4:1234AD";
char gas_CO[15]="CO:1234AD";
char gas_fire[15]="fire:1234AD";
char rainy[15]="rainy:1234AD";



/* 	DHT11温湿度传感器模块有严格的时序 
*  	如果在读取温度过程中进入中断了
*	则此次读取无效。用来判断是否进入过中断
*/
uint8_t isEnterEXTI=0;



void ReceiveATDataFromBufAndToMyCommandOfTask(void *pvParameters);


void ConnectTask(void *pvParameters)
{	
	pdMS_TO_TICKS(500);
	System_HelloHomepage();
	OLED_ShowDeveloperName();
	AT_Send_Command("ATE0",NULL,3000);
	AT_WIFIconnect(WIFI,WIFIPWD,3000);
	while(1)
	{
		OLED_ShowInterConnecting();
		if(AT_Interconnect(USER,ID,PWD,URL,PORT,6000)==1)break;
		
	}
	Subscribe(SUBNAME,50000);
	vTaskDelete(NULL);
} 

void ReadDHT11Task(void *pvParameters)
{
	vTaskDelay(4000);
	while(1)
	{	
		vTaskSuspendAll();
		DHT11_REC_Data(); //接收温度和湿度的数据
		xTaskResumeAll();
		vTaskDelay(400);	
	}
}

void PushThemeTask(void *pvParameters)
{	

	vTaskDelay(4000);
	System_Homepage();
	page=5;
	while(1)	
	{	
		temperature[5]=humiture_data[2]/10+'0';
		temperature[6]=humiture_data[2]%10+'0';
		temperature[8]=humiture_data[3]%10+'0';
		humidity[5]=humiture_data[0]/10+'0';
		humidity[6]=humiture_data[0]%10+'0';
		humidity[8]=humiture_data[1]%10+'0';
		PushTheme(PUSNAME,temperature,10000);
		PushTheme(PUSNAME,humidity,10000);
		
		gas_smoke[6]=ADValue[0]/1000+'0';
		gas_smoke[7]=ADValue[0]/100%10+'0';
		gas_smoke[8]=ADValue[0]/10%10+'0';
		gas_smoke[9]=ADValue[0]%10+'0';
		PushTheme(PUSNAME,gas_smoke,10000);
		
		gas_CH4[4]=ADValue[1]/1000+'0';
		gas_CH4[5]=ADValue[1]/100%10+'0';
		gas_CH4[6]=ADValue[1]/10%10+'0';
		gas_CH4[7]=ADValue[1]%10+'0';
		PushTheme(PUSNAME,gas_CH4,10000);
		
		gas_CO[3]=ADValue[2]/1000+'0';
		gas_CO[4]=ADValue[2]/100%10+'0';
		gas_CO[5]=ADValue[2]/10%10+'0';
		gas_CO[6]=ADValue[2]%10+'0';
		PushTheme(PUSNAME,gas_CO,10000);
		
		gas_fire[5]=ADValue[3]/1000+'0';
		gas_fire[6]=ADValue[3]/100%10+'0';
		gas_fire[7]=ADValue[3]/10%10+'0';
		gas_fire[8]=ADValue[3]%10+'0';
		PushTheme(PUSNAME,gas_fire,10000);
		
		vTaskDelay(200);		
	}
}

void MonitorAndControlTaskTask(void *pvParameters)
{
	int i;
	vTaskDelay(4000);
	while(1)
	{
		//实时监测
		if(ADValue[3]<=2000&&warning==0){
			Buzzer_On();
			Show_WarningFire();
			warning=1;	
		}
		
		if(strstr(myRecStr, "LED_ON"))
		{
			LED1_ON();
		}
		if(strstr(myRecStr, "LED_OFF"))
		{
			LED1_OFF();
		}
		if(strstr(myRecStr, "ALARM_OFF"))
		{
			warning=0;
			Buzzer_OFF();
		}
	}
}


void MyTimeTask()
{
	uint8_t second=0;
	uint8_t minute;
	uint8_t hour;
	vTaskDelay(4000);
	while(1)
	{
		second++;
		if(second>60)
		{
			second=0;
			MyTime[3]++;
			if(MyTime[3]>'9')
			{
				MyTime[3]='0';
				MyTime[2]++;
			}
			if(MyTime[2]>='6')
			{
				MyTime[2]='0';
				MyTime[1]++;
			}
			if(MyTime[1]>'9')
			{
				MyTime[1]='0';
				MyTime[0]++;
			}
			if(MyTime[0]=='2'&&MyTime[1]=='4')
			{
				MyTime[0]='0';
				MyTime[1]='0';
			}
			
		}
		
		Show_MyTime(' ');
		vTaskDelay(pdMS_TO_TICKS(500));
		Show_MyTime(':');
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}





void Key1CallbackFun(TimerHandle_t xTimer)
{
	if(warning==1)
	{
		warning=0;
		Buzzer_OFF();
		System_Homepage();
		return ;
	}
	page--;
	if(page>=5)page=4;
	
		if(page==4)
		{
			System_Homepage();	
		}else if(page<4&&page>=2)
		{
			System_Page1();
			OLED_ShowNum(2,6,humiture_data[2],2);
			OLED_ShowChar(2,8,'.');
			OLED_ShowNum(2,9,humiture_data[3],1);
			OLED_ShowChar(2,10,'C');
			OLED_ShowNum(3,6,humiture_data[0],2);
			OLED_ShowChar(3,8,'.');
			OLED_ShowNum(3,9,humiture_data[1],1);
			OLED_ShowChar(3,10,'%');
		}else if(page>=0&&page<2)
		{
			System_Page2();
			
		}
}

void Init_Hard()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	Serial_Init();
	TIM3_Init();
	OLED_Init();
	Buffer_Init();
	MyUSAT2_Init();
	AT_Init();
	Key_Init();
	AD_Init();
	Buzzer_Init();
	LED_Init();
}


int main()
{
	Init_Hard();
	sem_ATSendOfRec=xSemaphoreCreateCounting(128,0);
	timerKey1Handle = xTimerCreate("mytimer",pdMS_TO_TICKS(50),pdFALSE, NULL, Key1CallbackFun);
	timerMsgPageHandle=xTimerCreate("mytimer",pdMS_TO_TICKS(5000),pdFALSE, NULL, Key1CallbackFun);
	xTaskCreate(AT_Task_Parser, "AT_Task_Parser", 50, "", 3, NULL);
	xTaskCreate(ConnectTask, "Connect", 110, "", 2, NULL);
	xTaskCreate(ReceiveATDataFromBufAndToMyCommandOfTask, "Rec", 100, "", 3, NULL);
	xTaskCreate(ReadDHT11Task,"",20,"",1,NULL);
	xTaskCreate(PushThemeTask,"",50,"",1,NULL);
	xTaskCreate(MonitorAndControlTaskTask,"",10,"",1,NULL);
	xTaskCreate(MyTimeTask,"",10,"",1,NULL);
	vTaskStartScheduler();
	return 0;
}


void ReceiveATDataFromBufAndToMyCommandOfTask(void *pvParameters)
{
	int i=0;

	while(1)
	{
		//没有数据 阻塞自己
		buffer_Data_Read(&myRecStr[i],portMAX_DELAY);
		myRecStr[i+1]='\0'; //把每读到一个新的字符加结束符组成字符串
		//判断是否到了数据一行的末尾
		if(i&&myRecStr[i]=='\n' && myRecStr[i-1]=='\r')
		{
			myRecStr[i-1]='\0';
			//这里用于接收后判断开关灯。
			if(strstr(myRecStr, "Msg:")!=NULL)
			{
				OLED_Clear();
				OLED_ShowString(2,2,myRecStr);
				xTimerReset(timerMsgPageHandle,pdFALSE);
				
			}else if(strstr(myRecStr, "myTime:")!=NULL)
			{
				MyTime[0]=myRecStr[7];
				MyTime[1]=myRecStr[8];
				MyTime[2]=myRecStr[9];
				MyTime[3]=myRecStr[10];
			}
			i=0;
		}else{
			i++;
		}
	}
}



void USART1_IRQHandler()
{
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET){
		Buffer_Write(USART_ReceiveData(USART1),&ATbuf);
	}
	//isEnterEXTI=1;
	xSemaphoreGiveFromISR(sem_ATSendOfRec, pdFALSE);
	USART_ClearITPendingBit(USART1,USART_FLAG_RXNE);
}


void EXTI15_10_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line10) != RESET)
	{
		xTimerResetFromISR(timerKey1Handle,pdFALSE); /* Tcur + 2000 */
		EXTI_ClearITPendingBit(EXTI_Line10);
	}
	
}











