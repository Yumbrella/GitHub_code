#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void KeyInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef KeyInitStructure;

	KeyInitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	KeyInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	KeyInitStructure.GPIO_Pin = GPIO_Pin_1;

   GPIO_Init( GPIOB, &KeyInitStructure);
		
}


uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
		Delay_ms(20);
		KeyNum = 1;
	}
	return KeyNum;
}

