#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"


void LED_Init( )
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructuer  ;
	
	GPIO_InitStructuer.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructuer.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructuer.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;

	GPIO_Init(GPIOA, &GPIO_InitStructuer);
	
}

void LED_ON2()
{
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		
}

void LED_ON3()
{
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
		
}

void LED_ON4()
{
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
		
}

void LED_OFF2()
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
}

void LED_OFF3()
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
}

void LED_OFF4()
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
}

