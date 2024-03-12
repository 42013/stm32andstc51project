#include "reg52.h"
#include <intrins.h>

sfr AUXR=0x80;
sbit IN1 = P1^1;
sbit IN2 = P1^2;
sbit IN3 = P1^3;
sbit IN4 = P1^4;
sbit ENA	=P2^1;
sbit ENB	=P2^2;
sbit tracingLeft = P1^5;
sbit tracingRight = P1^6;
sbit tracingModile=P1^7;
sbit PWM = P2^0;  //设定PWM输出的I/O端口(舵机)

unsigned char pwm_left=210;
unsigned char pwm_right=210;
unsigned char pwm_t;
unsigned char count = 0;
unsigned char timer1;
unsigned char timer2; 
char leftSpeed;
char rightSpeed;
int cntLeft = 0;
int cntRight = 0;
int cnt = 0;

/*
对于180°舵机
t = 0.5ms——————-舵机会转动 0 ° 
t = 1.0ms——————-舵机会转动 45°
t = 1.5ms——————-舵机会转动 90°
t = 2.0ms——————-舵机会转动 135°
t = 2.5ms——————-舵机会转动 180°
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
void Timer1_Init(void)		//100微秒@11.0592MHz
{
	AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xAE;		//设置定时初值
	TH1 = 0xFB;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
}

 /*void Timer1_Init()		//100微秒@12.000MHz
{
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0x50;		//设置定时初值
	TH1 = 0xFB;		//设置定时初值
	TF1 = 0;		 //清除TF1标志
	TR1 = 1;		//定时器1开始计时
}*/

/*延时程序*/
void delay1s()   //误差 0us
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
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

/*定时器T0初始化*/

void sg90Left()
{
	timer1= 18;  
	if(timer2 != timer1){  
		cnt = 0;
	}
	timer2 = timer1;
	delay1s();
} 
 
void sg90Middle()
{
	timer1=5;
	if(timer2 != timer1){  
		cnt = 0;
	}
	timer2 = timer1;
	delay1s();
} 
 
void sg90Right()
{
	timer1=8;
	if(timer2 != timer1){  
		cnt = 0;
	}
	timer2 = timer1;
	delay1s();
} 

void goForward()
{
		IN1= 0;  IN2=1;
		IN3 = 1;	IN4=0;
}

void gostop()
{
	IN1= 0;  IN2=0;
		IN3 = 1;	IN4=1;
}

 void goForwardup()
{
	leftSpeed = 16;
	rightSpeed = 24;
}
void tracingMode()
{	
	if(tracingLeft == 0 && tracingRight == 0){  //
		goForward();
		goForwardup();
		sg90Middle();//舵机恢复到0°的位置
		count=0;//让定时器重新计数
	}
 
	if(tracingLeft == 0 && tracingRight == 1){
		goForward();
		goForwardup();;
		if(tracingModile==0){
		sg90Right();
		count=0;
		}else{
			goForwardup();
		goForward();
		sg90Middle();//舵机恢复到0°的位置
		count=0;//让定时器重新计数
		}
	}
 
	if(tracingLeft == 1 && tracingRight == 0){
		goForward();
		goForwardup();
		if(tracingModile==0){
		sg90Left();
			count=0;
		}else{
		goForward();
		goForwardup();
		sg90Middle();
		count=0;//让定时器重新计数
		}
	}
 
	if(tracingLeft == 1 && tracingRight == 1){
		if(tracingModile==0){
		gostop();
		timer1 =5;//舵机恢复到0°的位置
		count=0;//让定时器重新计数
		}else{
		goForward();
		goForwardup();
		timer1 =5;//舵机恢复到0°的位置
		count=0;//让定时器重新计数
		}
	}
}
void main()
{
	Timer0_Init();
	Timer1_Init();
	while(1){
		goForward();
		tracingMode();
		goForwardup();
	}
}
void Time1Handler() interrupt 3
{
	TL1 = 0x50;		//设置定时初值
	TH1 = 0xFB;		//设置定时初值
		pwm_t++;
		if(pwm_t==255)
				pwm_t=ENA=ENB=0;
		if(pwm_left==pwm_t)
		{
				ENA=1;
		}else{
			ENA=0;
		}
		if(pwm_right==pwm_t){
				ENB=1;
		}else{
		ENB=0;
		}
	}
 //可将循迹函数改为两部分，调试正常后再修改