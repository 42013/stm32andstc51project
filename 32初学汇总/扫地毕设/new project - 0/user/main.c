#include "stm32f10x.h"                  // Device header
#include "switch.h"
#include "Delay.h"
#include "xunji.h"
#include "Key.h"

float i;
uint8_t KeyNum;

int main(void)
{
		motor_gpio();
		xunji_gpio();
		pwm();
		Key_Init();
		relay_init();
	while(1)
	{	
//	KeyNum=Key_GetNum();
//		if(KeyNum==1){
//		relay1_on();
//		}
//		KeyNum=Key_GetNum();
//		if(KeyNum==2){
//		relay2_on();
//		}
		floorrun();
		//tryi();
	}
}
