#include "adc_temp.h"
#include "SysTick.h"

void ADC_Temp_Init()
{

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	ADC_InitTypeDef ADC_InitStructure;
	
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;   //单扫描通道
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;  //单次扫描
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;  //不使用外部触发
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;  //右对齐
	ADC_InitStructure.ADC_NbrOfChannel=1;
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_TempSensorVrefintCmd(ENABLE);
	
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);  
	
	
}

u16 Get_ADC_Temp_Value(u8 ch,u8 times)   //获取AD转换值的结果
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

int Get_Temperature(void)
{
	u16 adc_Temp=0;
	float temperature=0;
	int temp;
	adc_Temp=Get_ADC_Temp_Value(ADC_Channel_16,10);  //得到AD值
	temperature=(float)adc_Temp*(3.3/4096);      //将AD值转换为电压
	temperature=(1.43-temperature)/0.0043+25;    //通过电压计算出温度值
	temp=temperature*100;   //保存小数点后两位，得到温度值
	return temp;
	
}

