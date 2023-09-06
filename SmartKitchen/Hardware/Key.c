#include "stm32f10x.h"                  // Device header
#include "Key.h"


void Key_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//配置AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10);
	
	
	//配置EXTI
	EXTI_InitTypeDef extiStru;
	extiStru.EXTI_Line=EXTI_Line10;
	extiStru.EXTI_LineCmd=ENABLE;
	extiStru.EXTI_Mode=EXTI_Mode_Interrupt;
	extiStru.EXTI_Trigger=EXTI_Trigger_Falling; //
	EXTI_Init(&extiStru);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_InitTypeDef NVIC_initStru;
	NVIC_initStru.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_initStru.NVIC_IRQChannelCmd=ENABLE;
	NVIC_initStru.NVIC_IRQChannelPreemptionPriority=14;
	NVIC_initStru.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_initStru);
	
}

