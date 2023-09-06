#include "stm32f10x.h"       // Device header
#include "MAX7219ins.h"
#include "Delay.h"
void Write_CSS(uint8_t BitVal)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitVal );
}


void SPI_Start(void)
{
 Write_CSS(0);
}

void SPI_Stop(void)
{
 Write_CSS(1);
}

void Write_data(uint8_t TXdata)
{
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET);
	SPI_I2S_SendData(SPI1, TXdata);
}


void MAX7219_W(uint8_t addr, uint8_t data)
{
  SPI_Start();
	Write_data(addr);
	Delay_ms(300);
	Write_data(data);
	Delay_ms(300);
	SPI_Stop();	
}

void Max7219_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	GPIO_InitTypeDef Max7219_InitStructure;
	Max7219_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	Max7219_InitStructure.GPIO_Pin = GPIO_Pin_4;
	Max7219_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &Max7219_InitStructure);
	
	Max7219_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	Max7219_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	Max7219_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &Max7219_InitStructure);
	
	Max7219_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	Max7219_InitStructure.GPIO_Pin = GPIO_Pin_6;
	Max7219_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &Max7219_InitStructure);
	
	SPI_InitTypeDef MAX7219_InitStructure;
	MAX7219_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	MAX7219_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	MAX7219_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	MAX7219_InitStructure.SPI_CRCPolynomial = 7;
	MAX7219_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	MAX7219_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	MAX7219_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	MAX7219_InitStructure.SPI_Mode = SPI_Mode_Master;
	MAX7219_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI1, &MAX7219_InitStructure);
	
	SPI_Cmd(SPI1, ENABLE);
	
	Write_CSS(1);
	
	MAX7219_W(DecodeMode, 0x00);
	MAX7219_W(Intensity, 0x02);
	MAX7219_W(ScanLimit, 0x07);
	MAX7219_W(Shutdowm, 0x01);
	MAX7219_W(Displaytest, 0x00);
}


