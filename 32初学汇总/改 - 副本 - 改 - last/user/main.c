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
	serial_Init();
	Timer_Init();
	voice_Init();

	while(1)
	{	
	if(serial_GetRxFlag()==1) 
	{
		Data=serial_GetRxFlag();
		Data=USART_ReceiveData(USART1);
		serial_Sendbyte(Data);
	}
 }
}
