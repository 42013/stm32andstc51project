#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Motor.h"
#include "sterringgear.h"
#include "serial.h"
#include "AD.h"
#include "voice.h"
#include "timer.h"
#include "Delay.h"

int32_t gear1;
int32_t gear2;
uint16_t data;
uint8_t order;
void carcontrol(void)
{
	serial_Init();
	Motor1_Init(); 
	Motor2_Init();
	TIM3_PWM_Init();
	AD_Init();
	TIM2_PWM_Init();
	voice_Init();
if(serial_GetRxFlag()==1)
	{
		data=serial_GetRxFlag();
	}
		if(data<=7)
		{
		switch(data)
		{
		case 2:Forward();
		case 3:Down();
		case 4:MOVE1();
		case 5:MOVE2();
		case 6:Rightward();
		case 7:lengthdown();	
		}
		if(data==8)
			{
		gear2=AD_GetValue(ADC_Channel_0);
		if(gear2<=180){
		gear2++;
		getangle2(gear2);
		}
		}
		if(data==9)
			{
		gear2=AD_GetValue(ADC_Channel_0);
		if(gear2>=0){
		gear2--;
		getangle2(gear2);
		}
		}
		}
}

