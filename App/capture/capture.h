#ifndef _capture_H
#define _capture_H

#include "system.h"

extern u8   TIM5_CH1_CAPTURE_STA;
extern u16  TIM5_CH1_CAPTURE_VAL;


void TIM5_CH1_CAPTURE_Init(u16 pre,u16 psc);

#endif

