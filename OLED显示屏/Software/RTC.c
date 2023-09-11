#include "stm32f10x.h"                  // Device header
#include "time.h"

uint16_t MyRTC_DataTime[] = {2024, 7, 17, 00, 00, 00};

void RTC_SetTime(void);
void RTC_Init(void)
{
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_BKP, ENABLE);

	PWR_BackupAccessCmd(ENABLE);

	if(BKP_ReadBackupRegister( BKP_DR1 ) == 0xA5A5)
	{
		BKP_DeInit();
		RCC_LSEConfig(RCC_LSE_ON);
		while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);

		RTC_WaitForSynchro();
		RTC_WaitForLastTask();

		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);		
		
		RTC_SetTime();
	}

	else 
	{
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();

	}
}

void RTC_SetTime(void)
{
	time_t time_cnt;
	struct tm time_data;

	time_data.tm_year = MyRTC_DataTime[0]-1900;
	time_data.tm_mon = MyRTC_DataTime[1]-1;
	time_data.tm_mday = MyRTC_DataTime[2];
	time_data.tm_hour = MyRTC_DataTime[3];
	time_data.tm_min = MyRTC_DataTime[4];
	time_data.tm_sec = MyRTC_DataTime[5];

	time_cnt = mktime(&time_data);
	RTC_SetCounter(time_cnt);
	RTC_WaitForLastTask();
}


void RTC_ReadTime(void)
{
	time_t time_cnt;
	struct tm time_data;
	time_cnt = RTC_GetCounter();
	time_data = *localtime(&time_cnt);

	MyRTC_DataTime[0] = time_data.tm_year+1900;
	MyRTC_DataTime[1] = time_data.tm_mon+1;
	MyRTC_DataTime[2] = time_data.tm_mday;
	MyRTC_DataTime[3] = time_data.tm_hour;
	MyRTC_DataTime[4] = time_data.tm_min;
	MyRTC_DataTime[5] = time_data.tm_sec;
}
