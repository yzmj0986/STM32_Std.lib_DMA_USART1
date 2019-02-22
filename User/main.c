#include "stm32f10x.h"
#include "led.h"
#include "system.h"
#include "SysTick.h"
#include "USART.h"
#include "key.h"
#include "dac.h"
#include "dma.h"

#define send_buf_len    5000
u8 send_buf[send_buf_len];  //���û�������Ĵ�С ��5000

void Send_Data(u8 *p)   //��5000������ȫ������Ϊ5
{
	u16 i=0;
	for(i=0;i<send_buf_len;i++)
	{
		*p='5';
		p++;
	}
}

int main()
{
	u8 i=0;
	u8 key;
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�ж����ȼ�����
	KEY_Init();
	LED_Init();
	USART1_Init(9600);
	DMAp_Init(DMA1_Channel4,(u32)&USART1->DR,(u32)send_buf,send_buf_len);
	Send_Data(send_buf);
	
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY_UP)
		{
			USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); //�����������DMA����
			DMAp_Enable(DMA1_Channel4,send_buf_len);    //ʹ��DMAͨ��������ͨ�������ݴ�С
			
			while(1)
			{
				if(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=0)   //����1��ʾ������ɣ���Ҫ�˳�
				{
					DMA_ClearFlag(DMA1_FLAG_TC4);  //�����־λ���˳�ѭ��
					break;
				}
				else
				{
					led2=!led2;
					delay_ms(300);
				}
			}
		}
	
		i++;
		if(i%20==0)
		{
			led1=!led1;
		}
		delay_ms(10);
	
	}

}

