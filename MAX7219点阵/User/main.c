#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MAX7219.h"
#include "Delay.h"
#include "MAX7219ins.h"

uint8_t addr[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
uint8_t data[8] = {0x42,0xFF,0x4A,0xFF,0x20,0x7E,0xA2,0x3E};
int main(void)
{
	uint8_t i;
	
	OLED_Init();
  Max7219_Init();
	Delay_us(500);
	
	OLED_ShowString(1, 1, "HelloWorld!");
	
	for(i=0; i<8; i++)
	{
		MAX7219_W(addr[i], data[i]);
	}
	while(1)
	{

	}
}
