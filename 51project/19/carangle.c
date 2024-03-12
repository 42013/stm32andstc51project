#include "reg52.h"
#include <intrins.h> 

sbit left_con1A = P1^1;
sbit right_con1A = P1^3;
sfr AUXR=0x80;
sbit PWM = P3^7;  //设定PWM输出的I/O端口

unsigned char count = 0;
unsigned char timer1 ;
char leftSpeed;
char rightSpeed;
int cntLeft = 0;
int cntRight = 0;

/*
对于180°舵机
t = 0.5ms——————-舵机会转动 0 ° 
t = 1.0ms——————-舵机会转动 45°
t = 1.5ms——————-舵机会转动 90°
t = 2.0ms——————-舵机会转动 135°
t = 2.5ms——————-舵机会转动180
*/

void Timer0_Init()		//100微秒@12.000MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x50;		//设置定时初值
	TH0 = 0xFB;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}
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

 void Timer1Init()		//100微秒@12.000MHz
{
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0x50;		//设置定时初值
	TH1 = 0xFB;		//设置定时初值
	TF1 = 0;		 //清除TF1标志
	TR1 = 1;		//定时器1开始计时
}

/*延时程序*/
void delay1s(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}
/* void delay(unsigned int xms)		//@12.000MHz
{	
	unsigned char i;
	while(xms--)
	{
	_nop_();
	i = 2;
	while (--i);
	}
}*/

/*定时器T0初始化*/
/*void Timer0_Init()           
{
    TMOD &= 0x00;
    TMOD |= 0x01; //定时器T0设置成方式1
 
    TH0 = 0xff;   //定时常数 0.1ms 晶振为11.0592MHz
    TL0 = 0xa4;
 
    ET0 = 1;      
    TR0 = 1; 
	EA=1; 
	}*/
void goForward()
{
	left_con1A = 1;
	right_con1A = 1;
}

void gostop()
{
	left_con1A = 0;
	right_con1A = 0;
}

 void goForwardup()
{
	leftSpeed = 20;
	rightSpeed = 20;
}

void main()
{
	Timer0_Init();
	Timer1Init();
	while(1){
		goForwardup();
		delay1s();
		timer1 =10;//舵机旋转45°
		count=0;
		goForwardup();
		delay1s();
		timer1 =20;//舵机旋转135°
		count=0;//让定时器重新计数
		goForwardup();
		delay1s();
		timer1 =5;//舵机恢复到0°的位置
		count=0;//让定时器重新计数
		gostop();
		delay1s();
	}
}

void Time1Handler() interrupt 1
{
	cntLeft++;
	cntRight++;
	TL1 = 0x50;		//设置定时初值
	TH1 = 0xFB;		//设置定时初值
	if(cntLeft < leftSpeed&&cntRight < rightSpeed)
	{
		goForward();
	}else{
		gostop();
	}
	if(cntLeft == 20&&cntRight == 20){
		cntLeft = 0;
		cntRight = 0;
	}
}
 