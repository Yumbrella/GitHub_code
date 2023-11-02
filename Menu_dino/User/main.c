#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Timfig.h"
#include "MyRTC.h"
#include "Menu.h"


int main(void)
{
	OLED_Init();
	Key_Init();
  MyRTC_Init();
	TIM2_Init();
	
	while (1)
	{
		MyRTC_ReadTime();
		Menu_key_set();

  }
}
