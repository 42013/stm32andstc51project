#include "reg52.h"
#include <intrins.h>
sbit PWM = P3^7;  //设定PWM输出的I/O端口
unsigned int count = 0;
unsigned int timer1 ;
/*void Timer0_Init()		//100微秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xAE;		//设置定时初值
	TH0 = 0xFB;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}*/

void Timer0_Init()		//100微秒@12.000MHz
{
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TR0 = 1;		//定时器0开始计时
	EA=1;
	ES=1;
}


/*void delay(unsigned int xms)		//@12.000MHz
{	
	unsigned char i;
	while(xms--)
	{
	_nop_();
	i = 2;
	while (--i);
	}
}*/
void Time0_Init() interrupt 1 
{
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	if(count <= timer1) //5==0° 15==90°
	{ 
		PWM = 1; 
	}
	else 
	{ 
		PWM = 0; 
	}
	count++;
	if (count > 200) //T = 20ms清零
	{ 
		count = 0; 
	}
}
void main()
{
	Timer0_Init();
	while(1)
	{
		timer1 =18;//舵机旋转135°
		
		//timer1 =5;//舵机恢复到0°的位置
		//count=0;//让定时器重新计数
		//delay(1000);
	}
}
