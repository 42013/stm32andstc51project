#include "reg52.h"
#include <intrins.h>
sfr AUXR=0x80;
sbit PWM = P3^7;  //设定PWM输出的I/O端口
unsigned char count = 0;
unsigned char timer1 ;

void Timer0_Init()		//100微秒@12.000MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x50;		//设置定时初值
	TH0 = 0xFB;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}

 
/*T0中断初始化*/
void Time0Init() interrupt 1 
{
	TR0 = 0; 
	TL0 = 0x50;		//设置定时初值
	TH0 = 0xFB;		//设置定时初值
	if(count <= timer1) //5==0° 15==90°
	{ 
		PWM = 1; 
	}
	else 
	{ 
		PWM = 0; 
	}
	count++;
	if (count >= 200) //T = 20ms清零
	{ 
		count = 0; 
	}
	TR0 = 1; //开启T0
}