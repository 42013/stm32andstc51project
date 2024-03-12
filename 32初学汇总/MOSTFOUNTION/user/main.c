#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PWM.h"
#include "Motor.h"
#include "AD.h"                  
#include "serial.h"
#include "sterringgear.h"
#include "timer.h"
#include "voice.h"
#include "control.h"

int main(void)
{
//	Motor1_Init(); 
//	Motor2_Init();
//	TIM3_PWM_Init();
//	AD_Init();
//	serial_Init();
//	TIM2_PWM_Init();
//	voice_Init();
	while(1)
	{
		carcontrol();
	}
}
