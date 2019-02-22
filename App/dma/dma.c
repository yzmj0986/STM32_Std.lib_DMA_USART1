#include "dma.h"

void DMAp_Init(DMA_Channel_TypeDef* DMAy_Channelx,u32 pe_ad,u32 me_ad,u16 buffsize)   //防止与库函数重复 加p
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr=pe_ad;
	DMA_InitStructure.DMA_MemoryBaseAddr=me_ad;
	DMA_InitStructure.DMA_BufferSize=buffsize;
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST; //存储器到外设
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //外设地址无增量
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable; //存储器地址有增量
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;  //外设数据大小是字节
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;  //存储器数据大小是字节
	DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;    //不循环，正常单次传输
	DMA_InitStructure.DMA_Priority=DMA_Priority_Medium; 
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable; 
	DMA_Init(DMAy_Channelx,&DMA_InitStructure);  // 串口发送在DMA1的通道4
	
	
}

void DMAp_Enable(DMA_Channel_TypeDef* DMAy_Channelx,u16 setsize)   //开启DMA传输
{
	DMA_Cmd(DMAy_Channelx,DISABLE); // 关闭DMA
	DMA_SetCurrDataCounter(DMAy_Channelx,setsize);
	DMA_Cmd(DMAy_Channelx,ENABLE);
}


