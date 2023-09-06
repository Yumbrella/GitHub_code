#include "stm32f10x.h"                  // Device header
#include "AD.h"

uint16_t ADValue[5];


void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //72mhz/6
	GPIO_InitTypeDef GPIO_InitStru;
	GPIO_InitStru.GPIO_Mode=GPIO_Mode_AIN; //选择模拟输入模式
	GPIO_InitStru.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStru.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStru);
	
	//把通道1 放入序列1
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_4,5,ADC_SampleTime_55Cycles5);
	
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode=ADC_Mode_Independent; //独立模式还是双ADC模式
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;	//左对齐还是右对齐
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;	//对应ppt88页外部触发源选择，这里不选择
	//对应ppt91页扫描模式
	ADC_InitStruct.ADC_ContinuousConvMode=ENABLE;		//指定连续模式还是单次模式
	ADC_InitStruct.ADC_ScanConvMode=ENABLE;			//指定是扫描模式(多通道) 还是非扫描模式(单通道)
	ADC_InitStruct.ADC_NbrOfChannel=5;			//指定规则组里通道的数目 1-16之间
	ADC_Init(ADC1,&ADC_InitStruct);
	
	
	DMA_InitTypeDef DMA_InitStruct;
	DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)&ADC1->DR;		//外设站点的基地址 
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;	//传送数据的大小
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;		//地址自增 也就是说发完这个后增加继续发下一个
	DMA_InitStruct.DMA_MemoryBaseAddr=(uint32_t)ADValue;	//存储器站点的地址
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;	
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;		//存储器站点地址自增
	DMA_InitStruct.DMA_BufferSize=5;		//其实就是赋值给传输计数器 传几次
	DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralSRC;	//传输方向 是存储器到外设还是外设到存储器
	DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;	//memory_to_memory
	DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;	//自动重装和软件不能同时触发 
	DMA_InitStruct.DMA_Priority=DMA_Priority_Medium;	//选择转运优先级
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	ADC_DMACmd(ADC1,ENABLE); //这应该是选择ADC触发DMA
	
	ADC_Cmd(ADC1,ENABLE);
	
	//根据手册的建议需要跟ADC进行校准
	ADC_ResetCalibration(ADC1);		//复位校准
	while(ADC_GetResetCalibrationStatus(ADC1)==SET);		//等待复位校准完成
	ADC_StartCalibration(ADC1);		//开始校准
	while(ADC_GetCalibrationStatus(ADC1)==SET);		//
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
}


