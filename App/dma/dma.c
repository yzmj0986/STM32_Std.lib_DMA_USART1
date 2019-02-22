#include "dma.h"

void DMAp_Init(DMA_Channel_TypeDef* DMAy_Channelx,u32 pe_ad,u32 me_ad,u16 buffsize)   //��ֹ��⺯���ظ� ��p
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr=pe_ad;
	DMA_InitStructure.DMA_MemoryBaseAddr=me_ad;
	DMA_InitStructure.DMA_BufferSize=buffsize;
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST; //�洢��������
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //�����ַ������
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable; //�洢����ַ������
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;  //�������ݴ�С���ֽ�
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;  //�洢�����ݴ�С���ֽ�
	DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;    //��ѭ�����������δ���
	DMA_InitStructure.DMA_Priority=DMA_Priority_Medium; 
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable; 
	DMA_Init(DMAy_Channelx,&DMA_InitStructure);  // ���ڷ�����DMA1��ͨ��4
	
	
}

void DMAp_Enable(DMA_Channel_TypeDef* DMAy_Channelx,u16 setsize)   //����DMA����
{
	DMA_Cmd(DMAy_Channelx,DISABLE); // �ر�DMA
	DMA_SetCurrDataCounter(DMAy_Channelx,setsize);
	DMA_Cmd(DMAy_Channelx,ENABLE);
}


