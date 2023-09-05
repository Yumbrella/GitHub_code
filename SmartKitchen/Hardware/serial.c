#include "stm32f10x.h"                  // Device header
#include "serial.h"





void Serial_Init()
{
	unsigned long ulWantedBaud=115200;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable USART1 clock */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE );

	/* Configure USART1 Rx (PA10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init( GPIOA, &GPIO_InitStructure );

	/* Configure USART1 Tx (PA9) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
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
	

	USART_Init( USART1, &USART_InitStructure );

	//USART_ITConfig( USART1, USART_IT_RXNE, ENABLE );
	//开启中断方式读取数据
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	//中断优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_InitTypeDef NVIC_initStru;
	NVIC_initStru.NVIC_IRQChannel=USART1_IRQn;
	NVIC_initStru.NVIC_IRQChannelCmd=ENABLE;
	NVIC_initStru.NVIC_IRQChannelPreemptionPriority=13;
	NVIC_initStru.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_initStru);

	USART_Cmd( USART1, ENABLE );

}

void Serial_Putc(uint8_t ch)
{
	static int i=0;
	USART_TypeDef* USARTx=USART1;
	while((USARTx->SR & (1<<7)) == 0);
	USARTx->DR=ch;
	
}

void Serial_Write(char *wbuf,int len)
{
	int i;
	for(i=0;i<len;i++)
	{
		Serial_Putc(wbuf[i]);
	}
}


