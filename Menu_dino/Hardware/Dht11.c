#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
void DHT11_OInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
}

void DHT11_IInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t Dht11_start(void)
{
	DHT11_OInit();
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	Delay_ms(20);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	Delay_us(15);

	DHT11_IInit();
//	OLED_ShowString(1,1,"pp");
	if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))
	{
//		OLED_ShowString(2,1,"pp");
		while(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0));
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0));
		return 1;			
	}
	return 0;
}


uint8_t Dht11_Getdata(void)
{
	uint8_t buff = 0;
	for(int i = 0; i < 8; i++)
	{
		buff <<= 1;
		while(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0));
		Delay_us(30);
		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) ? (buff |= 0x01) : (buff &= ~0x01);
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0));
	}
	return buff;
}

uint8_t DTH11_Data(uint8_t buffer[])
{  
	if(Dht11_start())
	{
		buffer[0] = Dht11_Getdata();
		buffer[1] = Dht11_Getdata();
		buffer[2] = Dht11_Getdata();
		buffer[3] = Dht11_Getdata();
		Delay_us(60);
	}
	if(buffer[4] == (buffer[0]+buffer[1]+buffer[2]+buffer[3])) 
	{
    		
	return 1;
	}	
	else return 0;
}





