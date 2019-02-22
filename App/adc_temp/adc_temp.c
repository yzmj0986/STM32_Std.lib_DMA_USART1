#include "adc_temp.h"
#include "SysTick.h"

void ADC_Temp_Init()
{

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	ADC_InitTypeDef ADC_InitStructure;
	
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;   //��ɨ��ͨ��
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;  //����ɨ��
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;  //��ʹ���ⲿ����
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;  //�Ҷ���
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

u16 Get_ADC_Temp_Value(u8 ch,u8 times)   //��ȡADת��ֵ�Ľ��
{
	u8 t;
	u8 temp_val=0;
	ADC_RegularChannelConfig(ADC1,ch,1,ADC_SampleTime_239Cycles5); //����ת�����ڣ�239.5��
	
	for (t=0;t<times;t++)
	{
		ADC_SoftwareStartConvCmd(ADC1,ENABLE); 
		while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));  //ת����ɺ��˳�
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
	adc_Temp=Get_ADC_Temp_Value(ADC_Channel_16,10);  //�õ�ADֵ
	temperature=(float)adc_Temp*(3.3/4096);      //��ADֵת��Ϊ��ѹ
	temperature=(1.43-temperature)/0.0043+25;    //ͨ����ѹ������¶�ֵ
	temp=temperature*100;   //����С�������λ���õ��¶�ֵ
	return temp;
	
}

