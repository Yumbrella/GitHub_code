#include "stm32f10x.h"                  // Device header

void PWM1_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef PWMInitStructure;
  PWMInitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
  PWMInitStructure.GPIO_Pin = GPIO_Pin_2;
	PWMInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( GPIOA, &PWMInitStructure);

	TIM_InternalClockConfig(TIM2);

	TIM_TimeBaseInitTypeDef TIMInitStructure;
	TIMInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIMInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIMInitStructure.TIM_Prescaler = 720-1;
	TIMInitStructure.TIM_Period = 100-1;
	TIMInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIMInitStructure);

  TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = ENABLE;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);

	TIM_Cmd(TIM2, ENABLE);
}


void PWM_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM2, Compare);
}