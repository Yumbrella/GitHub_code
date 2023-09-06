#include "stm32f10x.h"                  // Device header
#include "LED.h"

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStru;
	GPIO_InitStru.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStru.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStru.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStru);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
}

void LED1_ON()
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
}

void LED1_OFF()
{
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
}

