#ifndef _dma_H
#define _dma_H

#include "system.h"

void DMAp_Init(DMA_Channel_TypeDef* DMAy_Channelx,u32 pe_ad,u32 me_ad,u16 buffsize);
void DMAp_Enable(DMA_Channel_TypeDef* DMAy_Channelx,u16 setsize);

#endif

