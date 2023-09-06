#include "stm32f10x.h"                  // Device header

uint16_t Rx_flag = 0;
uint8_t Data;


void HC04_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
  GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef HC04_InitStructure;
	HC04_InitStructure.USART_BaudRate = 9600;
	HC04_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	HC04_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	HC04_InitStructure.USART_Parity = USART_Parity_No;
	HC04_InitStructure.USART_StopBits = USART_StopBits_1;
	HC04_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &HC04_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructer;
	NVIC_InitStructer.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructer.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructer.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructer.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructer);
	
	USART_Cmd(USART1, ENABLE);
}

void Send_Data(uint8_t Data)
{
  USART_SendData(USART1, Data);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
}


uint8_t Get_flag(void)
{
	if(Rx_flag == 1)
	{
		Rx_flag = 0;
	  return 1;
  }
	return 0;
}

uint8_t Get_RxData(void)
{
		return Data;
}

void USART1_IRQHandler(void)
{
	
  if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
	   Data = USART_ReceiveData(USART1);
		 Rx_flag = 1;
		 USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}