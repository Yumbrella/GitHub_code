#include "myusart2.h"
#include "stm32f10x.h"                  // Device header
#include <stdio.h>

void MyUSAT2_Init()
{
	unsigned long ulWantedBaud=115200;
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable USART2 clock */
	RCC_APB2PeriphClockCmd( RCC_APB1Periph_USART2 | RCC_APB2Periph_GPIOA, ENABLE );

	/* Configure USART2 Rx (PA3) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init( GPIOA, &GPIO_InitStructure );

	/* Configure USART2 Tx (PA2) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init( GPIOA, &GPIO_InitStructure );

	USART_InitStructure.USART_BaudRate = ulWantedBaud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	/*USART_InitStructure.USART_Clock = USART_Clock_Disable;
	USART_InitStructure.USART_CPOL = USART_CPOL_Low;
	USART_InitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_InitStructure.USART_LastBit = USART_LastBit_Disable;*/
	

	USART_Init( USART2, &USART_InitStructure );

	USART_Cmd( USART2, ENABLE );

}

void MyUSAT2_SendByte(uint8_t Msg)
{
	USART_SendData(USART2,Msg);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	
}

int fputc(int ch,FILE *f)
{
	MyUSAT2_SendByte(ch);
	return ch;
}
