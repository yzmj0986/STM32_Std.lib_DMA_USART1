#include "wakeup.h"

void Enter_Standby_Mode()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE); //开启时钟
	
	PWR_WakeUpPinCmd(ENABLE); //设置唤醒源
	
	PWR_ClearFlag(PWR_FLAG_WU);
	
	PWR_EnterSTANDBYMode();
	
}

