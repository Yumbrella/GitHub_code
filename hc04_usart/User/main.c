#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "HC_04.h"


uint8_t RxData ;

int main(void)
{
	OLED_Init();
	HC04_Init();
	OLED_ShowString(1, 1, "RxData:");
	
	while (1)
	{
    if(Get_flag() == 1)
		{
			RxData = Get_RxData();
			Send_Data(RxData);
			OLED_ShowHexNum(1, 8, RxData, 2);
		}			
	}
}
