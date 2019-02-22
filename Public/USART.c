#include "USART.h"


int fputc(int ch,FILE *p)     //Printf重定向
{
	USART_SendData(USART1,(u8)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}


void USART1_Init(u32 btl)
	
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;     //PA9是串口1的发送引脚
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;     //PA10是串口1的接收引脚，输入模式 不需要配置速度。
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=btl;                 //串口参数的设置，波特率、字长、停止位、奇偶校验、硬件流、模式
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART1,&USART_InitStructure);
	
	USART_Cmd(USART1,ENABLE);   //使能USART1位
	
	USART_ClearFlag(USART1,USART_FLAG_TC);  //清除标志位
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);   //设置串口中断类型并使能
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;    //中断优先级配置 抢占式和响应式均为最低的1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void USART1_IRQHandler(void)
{
	u8 r;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{
		r=USART_ReceiveData(USART1);
		USART_SendData(USART1,r);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	}
	USART_ClearFlag(USART1,USART_FLAG_TC);
}

