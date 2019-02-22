#include "stm32f10x.h"
#include "led.h"
#include "system.h"
#include "SysTick.h"
#include "USART.h"
#include "key.h"
#include "dac.h"
#include "dma.h"

#define send_buf_len    5000
u8 send_buf[send_buf_len];  //设置缓存数组的大小 是5000

void Send_Data(u8 *p)   //将5000个数据全部设置为5
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //中断优先级分组
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
			USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); //开启了外设的DMA功能
			DMAp_Enable(DMA1_Channel4,send_buf_len);    //使能DMA通道，设置通道和数据大小
			
			while(1)
			{
				if(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=0)   //等于1表示传输完成，则要退出
				{
					DMA_ClearFlag(DMA1_FLAG_TC4);  //清除标志位后退出循环
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

