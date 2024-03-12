#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "xunji.h"
#include "serial.h"
#include "voice.h"
#include "timer.h"
#include "sterringgear.h"

uint8_t Data;


int main(void)
{
	//one();
	//two();
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
	if(serial_GetRxFlag()==1) 
	{
		Data=serial_GetRxFlag();
		Data=USART_ReceiveData(USART1);
	}
//	switch(Data)
//	{
//		case 1:tracingMode();break;
//		case 2:run();break;
//		case 3:back();break;
//		case 4: MOVER();break;
//		case 5:MOVEL();break;
//		case 6:stop();break;
//		case 7:lengthdown();break;
//		case 8:one();break;
//		case 9:two();break;
//	}
	if(Data==1)
		{
		tracingMode0();
	}else if(Data==2)
		{
		run();
	}else if(Data==3)
		{
		back();
	}else if(Data==4)
		{
		 Rightward();	
	}else if(Data==5)
		{
		 Leftward();	
	}else if(Data==6)
		{
		 stop();	
	}else if(Data==7)
		{
		 lengthdown();	
	}else if(Data==8)
		{uint16_t x;
			if(500<x<2500){
			x++;
			 //Delay_ms(500);	
			}
			if(x>2500)
			{
			x=700;
			}
		PWM_SetCompare2(x);
		 //Rightward();	
	}else if(Data==9)
		{ 
			uint16_t y;
			if(500<y<2500){
			y++;
			}
			if(y>2500)
			{
			y=700;
			}
		PWM_SetCompare1(y); 
		 //Leftward();		
	}	
	}
}
