#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "RTC.h"

int main(void)
{
	OLED_Init();
	RTC_Init();

	OLED_ShowString(1,3,"Hello world!");
	
  OLED_ShowChinese(2,0,0);
	OLED_ShowChinese(2,18,1);
	OLED_ShowChar(2, 6, ':');

  OLED_ShowChinese(4, 0, 3);
	OLED_ShowChinese(4, 18, 4);
	OLED_ShowChar(3, 6, ':');
	
	OLED_ShowChinese(6, 0, 5);
	OLED_ShowChinese(6, 18, 6);
	OLED_ShowChar(4, 6, ':');
    
	while (1)
	{
	 	RTC_ReadTime();
		OLED_ShowNum(2, 7,RTC_GetCounter() , 10);

		OLED_ShowNum(3, 7, MyRTC_DataTime[0], 4);
		OLED_ShowNum(3, 12, MyRTC_DataTime[1], 2);
		OLED_ShowNum(3, 15, MyRTC_DataTime[2], 2);
		
		OLED_ShowNum(4, 9, MyRTC_DataTime[3], 2);
		OLED_ShowNum(4, 12, MyRTC_DataTime[4], 2);
		OLED_ShowNum(4, 15, MyRTC_DataTime[5], 2);
	}
}
