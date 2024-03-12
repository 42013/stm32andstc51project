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
		ADNum1=AD_GetValue(ADC_Channel_0);
		if(ADNum1>3300){
	switch(ADNum1)
		{
		case 4090:serial_Sendbyte(6);Delay_ms(10);serial_Sendbyte(0);break;
		}
	}
		if(ADNum1<3000){
	switch(ADNum1)
		{
		case 10:serial_Sendbyte(8);Delay_ms(10);serial_Sendbyte(0);break;
		}
	}
		ADNum2=AD_GetValue(ADC_Channel_1);
	if(ADNum2>3300){
	switch(ADNum2)
		{
		case 4090: serial_Sendbyte(7);Delay_ms(10);serial_Sendbyte(0);break;
		}
	}
	if(ADNum2<3000){
	switch(ADNum2)
		{
		case 10:serial_Sendbyte(9);Delay_ms(10);serial_Sendbyte(0);break;
		}
	}
		KeyNum=Key_GetNum();
		if(KeyNum==1){
			A++;
			if(A%2==0){
		serial_Sendbyte(7);
			}else{
			serial_Sendbyte(4);
			}
		}
	}
}	
