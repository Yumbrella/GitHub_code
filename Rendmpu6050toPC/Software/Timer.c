#include "stm32f10x.h"                  // Device header


void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_InternalClockConfig(TIM2);

	TIM_TimeBaseInitTypeDef TimerBaseInitstructure;
	TimerBaseInitstructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TimerBaseInitstructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimerBaseInitstructure.TIM_Period = 10000-1;
	TimerBaseInitstructure.TIM_Prescaler = 36000 - 1;
	TimerBaseInitstructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM2, &TimerBaseInitstructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init( &NVIC_InitStructure);

	TIM_Cmd(TIM2 ,ENABLE);
}

