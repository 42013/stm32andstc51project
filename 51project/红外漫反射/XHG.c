#include "reg52.h"
#include <intrins.h>

sfr AUXR=0x80;
sbit IN1 = P1^1;
sbit IN2 = P1^2;
sbit IN3 = P1^3;
sbit IN4 = P1^4;
sbit ENA	=P2^1;
sbit ENB	=P2^2;
sbit left_light = P1^5;
sbit right_light = P1^6;
sbit middle_light=P1^7;
sbit PWM = P2^0;  //设定PWM输出的I/O端口
sbit xhg	=P1^0;

unsigned char pwm_left_val=210;
unsigned char pwm_right_val=210;
unsigned char pwm_t;
unsigned char counter=0;
unsigned char count = 0;
unsigned char timer1 ;

/*
对于180°舵机
t = 0.5ms——————-舵机会转动 0 ° 
t = 1.0ms——————-舵机会转动 45°
t = 1.5ms——————-舵机会转动 90°
t = 2.0ms——————-舵机会转动 135°
t = 2.5ms——————-舵机会转动 180°
*/

void Timer0_Init()           
{
    TMOD &= 0x00;
    TMOD |= 0x01; //定时器T0设置成方式1
 
    TH0 = 0xff;   //定时常数 0.1ms 晶振为11.0592MHz
    TL0 = 0xa4;
 
    ET0 = 1;      
    TR0 = 1; 
	EA=1; 
	}
void Time0_Init() interrupt 1 
{
	TR0 = 0; 
	TH0 = 0xff;   //定时常数 0.1ms 晶振为11.0592MHz
    TL0 = 0xa4;
 
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

 void Timer1_Init()		//100微秒@12.000MHz
{
	//TMOD &= 0x0F;		//设置定时器模式
	//TL1 = 0x50;		//设置定时初值
	//TH1 = 0xFB;		//设置定时初值
	//TF1 = 0;		 //清除TF1标志
	//TR1 = 1;		//定时器1开始计时
	//EA	=	1;
	//ES	=	1;
			TMOD|=0x02;//八位重装模块
			TH1=256;
			TL1=256;//11.0592M晶振下最大比值是256，输出100HZ
			TR1=1;//启动定时器1
			ET1=1;//允许定时器1中断
			EA=1;//总中断允许
}

/*延时程序*/
/*void delay1s()   //误差 0us
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}*/
 void delay(unsigned int xms)		//@12.000MHz
{	
	unsigned char i;
	while(xms--)
	{
	_nop_();
	i = 2;
	while (--i);
	}
}

/*定时器T0初始化*/

void goForward()
{
		IN1= 0;  IN2=1;
		IN3 = 1;	IN4=0;
	pwm_left_val=130;
	pwm_right_val=130;
		timer1=12;
}
/*void godown1()
{
		IN1= 1;  IN2=0;
		IN3 =0;	IN4=1;
	pwm_left_val=110;
	pwm_right_val=110;
		timer1=10;
}*/
/*void godown2()
{
		IN1= 1;  IN2=0;
		IN3 =0;	IN4=1;
	pwm_left_val=110;
	pwm_right_val=110;
		timer1=14;
}*/
void gostop()
{
		IN1= 0;  IN2=0;
		IN3 = 1;	IN4=1;
		timer1=12;
}
void goright(){
	IN1= 0;  IN2=1;
		IN3 = 1;	IN4=0;
	pwm_left_val=140;
	pwm_right_val=120;
	timer1=11;
}
void goleft(){
		IN1= 0;  IN2=1;
		IN3 = 1;	IN4=0;
	pwm_left_val=120;
	pwm_right_val=140;
	timer1=13;
}
void putleft(){
	IN1= 0;  IN2=1;
		IN3 = 1;	IN4=0;
	pwm_left_val=145;
	pwm_right_val=115;
	timer1=14;
}
void putright(){
		IN1= 0;  IN2=1;
		IN3 = 1;	IN4=0;
	pwm_left_val=115;
	pwm_right_val=145;
	timer1=9;
}
void tracingMode()    
{	
	if(left_light==1&&middle_light==1&&right_light==1)//ȫۚ 
	{
		goForward();
	}
	if(left_light==0&&middle_light==1&&right_light==0)//ֱП
	{      
		goForward();
	}
	if(left_light==1&&middle_light==0&&right_light==0)//ճԒת
	{
		putleft();
			if(left_light==0&&middle_light==1&&right_light==0)
			{
			goForward();
			}
	}

	if(left_light==0&&middle_light==0&&right_light==1)//ճسת
	{	
			putright();
			if(left_light==0&&middle_light==1&&right_light==0)
			{
				goForward();
			}
	} 
	if(left_light==1&&middle_light==1&&right_light==0)
	{
			goleft();
		if(left_light==0&&middle_light==1&&right_light==0)
		{
		goForward();
		}
	}
	if(left_light==0&&middle_light==1&&right_light==1)
	{
		goright();

		if(left_light==0&&middle_light==0&&right_light==0)
		{
			goForward();
		}
	}
}
void avoid(){
	if(xhg==1)     //确定是不是真检测到了
			{
			gostop();
			delay(50);
			putleft();
			delay(2000);
			goForward();
		}
}
void main()
{
	 Timer0_Init();           
		Timer1_Init();
			while(1){
			tracingMode();
			avoid();	
	}
}

void Time1_Init() interrupt 3
{
			TR1=1;//启动定时器0
			TH1=236;
			TL1=236;//11.0592M晶振下最大比值是256，输出100HZ
		pwm_t++;
		if(pwm_t==225)
				pwm_t=ENA=ENB=0;
		if(pwm_left_val==pwm_t)
				ENA=1;
		if(pwm_right_val==pwm_t)
				ENB=1;
}