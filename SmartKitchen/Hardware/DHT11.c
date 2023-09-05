#include "stm32f10x.h"                  // Device header
#include "DHT11.h"
#include "Delay.h"

unsigned int humiture_data[4];
extern uint8_t isEnterEXTI;

void DH11_GPIO_Init_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void DH11_GPIO_Init_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING; //????
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}


//主机发送开始信号
void DHT11_Start(void)
{
	DH11_GPIO_Init_OUT(); //输出模式
	
	dht11_high; //先拉高
	Delay_us(30);
	
	dht11_low; //拉低电平至少18ms
	Delay_ms(20);
	
	dht11_high; //拉高电平20~40us
	Delay_us(30);
	
	DH11_GPIO_Init_IN(); //输入模式
}

//获取一个字节
char DHT11_Rec_Byte(void)
{
	unsigned char i = 0;
	unsigned char data;
	
	for(i=0;i<8;i++) //1个数据就是1个字节byte，1个字节byte有8位bit
	{
		while( Read_Data == 0)
		{
			if(isEnterEXTI)
			{
				break;
			}
		}
		Delay_us(30); //延迟30us是为了区别数据0和数据1，0只有26~28us
		
		data <<= 1; //左移
		
		if( Read_Data == 1 ) //如果过了30us还是高电平的话就是数据1
		{
			data |= 1; //数据+1
		}
		
		while( Read_Data == 1 )
		{
			if(isEnterEXTI)
			{
				break;
			}
		}			
	}
	
	return data;
}


//获取数据

void DHT11_REC_Data(void)
{
	unsigned int R_H,R_L,T_H,T_L;
	unsigned char RH,RL,TH,TL,CHECK;
	
	DHT11_Start(); //主机发送信号
	dht11_high; //拉高电平
	
	if( Read_Data == 0 ) //判断DHT11是否响应
	{
		while( Read_Data == 0)
		{
			if(isEnterEXTI)
			{
				break;
			}
		}
		while( Read_Data == 1)
		{
			if(isEnterEXTI)
			{
				break;
			}
		}
		
		R_H = DHT11_Rec_Byte();
		R_L = DHT11_Rec_Byte();
		T_H = DHT11_Rec_Byte();
		T_L = DHT11_Rec_Byte();
		CHECK = DHT11_Rec_Byte(); //接收5个数据
		
		dht11_low; 
		Delay_us(55); 
		dht11_high; 
		
		if(isEnterEXTI)
		{
			isEnterEXTI=0;
			return ;
		}
		
		if(R_H + R_L + T_H + T_L == CHECK)
		{
			RH = R_H;
			RL = R_L;
			TH = T_H;
			TL = T_L;
		}
	}
	humiture_data[0] = RH;
	humiture_data[1] = RL;
	humiture_data[2] = TH;
	humiture_data[3] = TL;
}
