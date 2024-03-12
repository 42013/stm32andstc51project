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
	run();
	}
}
