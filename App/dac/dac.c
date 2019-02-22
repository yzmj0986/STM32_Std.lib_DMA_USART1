#include "dac.h"

void DAC1_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	DAC_InitStructure.DAC_Trigger=DAC_Trigger_None; //不使用触发
	DAC_InitStructure.DAC_WaveGeneration=DAC_WaveGeneration_None; //不产生波形
	DAC_InitStructure.DAC_OutputBuffer=DAC_OutputBuffer_Disable;  //关闭输出缓存
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;  //关闭幅值
	DAC_Init(DAC_Channel_1,&DAC_InitStructure);
	
	DAC_Cmd(DAC_Channel_1,ENABLE);
	
	DAC_SetChannel1Data(DAC_Align_12b_R,0);  //设置DAC的位数与对齐方式，DOR寄存器初值为0
	
}

