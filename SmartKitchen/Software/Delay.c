#include "stm32f10x.h"
#include "Delay.h"

void TIM6_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//tim2是apb1时钟
	TIM_InternalClockConfig(TIM3);//
	//配置时基单元
	TIM_TimeBaseInitTypeDef timBIni;
	timBIni.TIM_ClockDivision=TIM_CKD_DIV1;//分频
	timBIni.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
	timBIni.TIM_Period=10000-1; //
	timBIni.TIM_Prescaler=72-1;//
	timBIni.TIM_RepetitionCounter=0;//重复计数器的值
	TIM_TimeBaseInit(TIM3,&timBIni);
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	
	//72HZ 分频后 1 000 000hz  也就是说记一次数是1us
}




/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void Delay_us(uint32_t xus)
{
	TIM_Cmd(TIM3,ENABLE); //启动定时器
	while(TIM3->CNT < xus);
	TIM3->CNT = 0;
	TIM_Cmd(TIM3,DISABLE); //关闭定时器
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
} 
