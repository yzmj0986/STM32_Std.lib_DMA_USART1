#include "adc.h"
#include "SysTick.h"

void ADCp_Init()    //为跟库函数区分 加了角标p
{
  GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //分频因子是6
	
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;   //单扫描通道
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;  //单次扫描
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;  //不使用外部触发
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;  //右对齐
	ADC_InitStructure.ADC_NbrOfChannel=1;
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);   //开启软件触发
	
}

u16 Get_ADC_Value(u8 ch,u8 times)   //获取AD转换值的结果
{
	u8 t;
	u8 temp_val=0;
	ADC_RegularChannelConfig(ADC1,ch,1,ADC_SampleTime_239Cycles5); //最大的转换周期，239.5个
	
	for (t=0;t<times;t++)
	{
		ADC_SoftwareStartConvCmd(ADC1,ENABLE); 
		while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));  //转换完成后退出
		temp_val+=ADC_GetConversionValue(ADC1);
		delay_ms(5);
	}
	return temp_val/times;
}


	
		
	
	
	
	
	
}

