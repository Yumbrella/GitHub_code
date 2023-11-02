#include "stm32f10x.h"                  // Device header

#include "Control.h"
#include "OLED.h"
#include "Dinogame.h"
#include "stdlib.h"
#include "Delay.h"

unsigned char key_num = 0;
unsigned char cactus_category = 0;
unsigned char cactus_length = 8;
unsigned int score = 0;
unsigned int highest_score=0;
int height = 0;
int cactus_pos = 128;
unsigned char cur_speed = 30;
char failed = 0;
char reset = 0;

int get_key(void)
{
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)==0)
	{
		Delay_ms(10);
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)==0)
		{
			return 1;
		}
	}
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14)==1)
	{
		Delay_ms(10);
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14)==1)
		{
			return 2;
		}
	}
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)==1)
	{
		Delay_ms(10);
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)==1)
		{
			return 3;
		}
		return 0;
	}
}

void Game_control(void)
{
	while(1)
	{
		if(get_key() == 1)
		{
			break;
		}
		if(failed == 1)
		{
			
			OLED_DrawRestart();
			key_num = get_key();
			if(key_num == 2 && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)==0))
			{
				if(score > highest_score) highest_score = score;
				score = 0;
				failed = 0;
				height = 0;
				reset = 1;
				OLED_DrawDinoJump(reset);
				OLED_DrawCactusRandom(cactus_category, reset);
				OLED_Clear();
			}
			continue;
		}
		score++;
		if(height<=0) key_num = get_key();
		
		OLED_DrawGround();
		OLED_DrawCloud();
		
		if(height>0 || key_num == 3) height = OLED_DrawDinoJump(reset);
		else OLED_DrawDino();
		
		cactus_pos = OLED_DrawCactusRandom(cactus_category, reset);
		if(cactus_category == 0) cactus_length = 8;
		else if(cactus_category == 1) cactus_length = 16;
		else cactus_length = 24;
		
		if(cactus_pos + cactus_length < 0)
		{
			cactus_category = rand()%4;
			OLED_DrawCactusRandom(cactus_category, 1);
		}
		if ((height < 16) && ( (cactus_pos>=16 && cactus_pos <=32) || (cactus_pos + cactus_length>=16 && cactus_pos + cactus_length <=32)))
		{
			failed = 1;
		}
		OLED_ShowChar(2, 1, 'H',4);
		OLED_ShowNum(3, 1, highest_score, 5, 16);
		OLED_ShowNum(4, 1, score, 5, 16);
		
		reset = 0;
		
		cur_speed = score/7;
		if(cur_speed > 29) cur_speed = 29;
		Delay_ms(30 - cur_speed);
		//Delay_ms(500);
		key_num = 0;
	}
}