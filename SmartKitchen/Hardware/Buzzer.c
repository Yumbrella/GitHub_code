#include "stm32f10x.h"                  // Device header
#include "Buzzer.h"

void Buzzer_Init()
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStru;
	GPIO_InitStru.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStru.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStru.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStru);
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
}

void Buzzer_On()
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
}

void Buzzer_OFF()
{
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
}