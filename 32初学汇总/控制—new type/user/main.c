#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "serial.h"
#include "PWM.h"
#include "AD.h"
#include "Key.h"


uint32_t ADNum1;
uint32_t ADNum2;
uint8_t KeyNum;
uint8_t A;

int main(void)
{
	serial_Init();
	AD_Init();
	Key_Init();
	while(1)
	{
	serial_Sendbyte(6);
	Delay_ms(500);
	serial_Sendbyte(0);
	Delay_ms(500);
	}
}
