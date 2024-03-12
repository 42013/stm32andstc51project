#include "stm32f10x.h"                  // Device header
#include "switch.h"
#include "Delay.h"
#include "xunji.h"
#include "Key.h"
#include "serial.h"

uint16_t Data;
uint16_t b=0;

void relay_init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 输出高

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 端口配置, 推挽输出
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 输出高 
}


int main(void)
{
		relay_init();
		//serial_Init();
	while(1)
	{	
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		Delay_ms(500);
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		Delay_ms(500);
		//relay1_on();
		//relay2_on();
		//Delay_ms(2000);
		//relay2_off();
		//relay1_on();
		//relay1_off();
		//floorrun();
		//relay1_on();
//		if(serial_GetRxFlag()==1) 
//	{
//		Data=serial_GetRxFlag();
//		Data=USART_ReceiveData(USART1);
//		b=1;
//	}
//	if(Data==0)
//		{
//		stop();
//	}else if(Data==1)
//		{
//	run();
//	}else if(Data==2)
//		{
//	back();
//	}else if(Data==3)
//		{
//		Rightward();	
//	}else if(Data==4)
//		{
//		Leftward();	
//	}else if(Data==5)
//		{
//		floorrun();
//	}else if(Data==6)
//		{
//		 relay1_on();
//	}else if(Data==7)
//		{
//		 relay1_off();
//		}
	}
}
