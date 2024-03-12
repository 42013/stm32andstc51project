#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "xunji.h"
#include "serial.h"
#include "voice.h"
#include "timer.h"
#include "sterringgear.h"

uint16_t Data;

int main(void)
{
	motor1_gpio();
	motor2_gpio();
	pwm();
	serial_Init();
	Timer_Init();
	voice_Init();
	xunji_gpio();
	TIM2_PWM_Init();
	while(1)
	{	
//		uint16_t m;
	if(serial_GetRxFlag()==1) 
	{
		Data=serial_GetRxFlag();
		Data=USART_ReceiveData(USART1);
	}
//	if(m!=1){
//	t=getlength();
//	if(t>50){
//	tracingMode0();
//	}else{
//	lengthdown();
//	}
//	if(t<35){
//	m=1;
//	break;	
//	}
//}
	if(Data==0)
		{
		stop();
	}else if(Data==4)
		{
	tracingMode0();	
	}else if(Data==3)
		{
		lengthdown();
	}else if(Data==6)
		{
			uint16_t x;
			if(500<x<2500){
			x++;	
			}
			if(x>2500)
			{
			x=510;
			}
		PWM_SetCompare2(x);
	}else if(Data==7)
		{
			uint16_t y;
			if(500<y<2500){
			y++;	
			}
			if(y>2500)
			{
			y=510;
			}
		PWM_SetCompare1(y);
	}else if(Data==8)
		{
			uint16_t x;
			if(500<x<2500) {
			x--;
			}
			if(x<500)
			{
			x=2490;
			}
		PWM_SetCompare2(x);
	}else if(Data==9)
		{
			uint16_t y;
			if(500<y<2500){
			y--;	
			}
			if(y<500) 
			{
			y=2490;
			}
		PWM_SetCompare1(y);
		}
	}
}
