#include "wakeup.h"

void Enter_Standby_Mode()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE); //����ʱ��
	
	PWR_WakeUpPinCmd(ENABLE); //���û���Դ
	
	PWR_ClearFlag(PWR_FLAG_WU);
	
	PWR_EnterSTANDBYMode();
	
}

