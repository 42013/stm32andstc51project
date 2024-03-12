#include "reg52.h"
#include <intrins.h>

sbit IN1 = P1^1;
sbit IN2 = P1^2;
sbit IN3 = P1^3;
sbit IN4 = P1^4;
sbit ENA=P2^1;
sbit ENB=P2^2;
sbit left_light = P1^5;
sbit right_light = P1^6;
sbit middle_light=P1^7;
sbit PWM = P2^0;  //设定PWM输出的I/O端口(舵机)
sbit xhg	=P1^0;

unsigned char pwm_left_val;
unsigned char pwm_right_val;
unsigned char pwm_t;
unsigned char count = 0;
unsigned char timer1; 
float distance;
void delay1s()   //误差 0us
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}
void Timer0_Init()		//100微秒@12.000MHz
{
	TMOD &= 0x00;
    TMOD |= 0x01; //定时器T0设置成方式1
 
    TH0 = 0xff;   //定时常数 0.1ms 晶振为11.0592MHz
    TL0 = 0xa4;
 
    ET0 = 1;      
    TR0 = 1; 
	EA=1; 
}
void Time0Init() interrupt 1 
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
			TMOD|=0x02;//八位重装模块
			TH1=256;
			TL1=256;//11.0592M晶振下最大比值是256，输出100HZ
			TR1=1;//启动定时器1
			ET1=1;//允许定时器1中断
			EA=1;//总中断允许
}
void goForward()
{
		IN1= 1;  IN2=0;
		IN3 = 0;	IN4=1;
	pwm_left_val=160;
	pwm_right_val=160;
		timer1=12;
}
void goright(){
		IN1= 1;  IN2=0;
		IN3 = 0;	IN4=1;
	pwm_left_val=180;
	pwm_right_val=160;
	timer1=10;
}
void goleft(){
		IN1= 1;  IN2=0;
		IN3 = 0;	IN4=1;
	pwm_left_val=160;
	pwm_right_val=180;
	timer1=13;
}
void putleft(){
	IN1= 1;  IN2=0;
		IN3 = 0;	IN4=1;
	pwm_left_val=205;
	pwm_right_val=175;
	timer1=14;
}
void putright(){
		IN1= 1;  IN2=0;
		IN3 = 0;	IN4=1;
	pwm_left_val=175;
	pwm_right_val=205;
	timer1=9;
}
void tracingMode()    
{	
	if(xhg==1)     //确定是不是真检测到了
			{
			putleft();
			delay1s();
			putright();
			delay1s();
			goForward();
			}
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
		putright();
			if(left_light==0&&middle_light==1&&right_light==0)
			{
			goForward();
			}
	}

	if(left_light==0&&middle_light==0&&right_light==1)//ճسת
	{	
			putleft();
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
void main()
{
	 Timer0_Init();           
		Timer1_Init();	
	while(1){
		tracingMode();
		}
	}


void Time1_Init() interrupt 3
{
	TR1=1;//启动定时器1
			TH1=236;
			TL1=236;//11.0592M晶振下最大比值是256，输出100HZ
		pwm_t++; 
		if(pwm_t==255)
				pwm_t=ENA=ENB=0;
		if(pwm_left_val==pwm_t)
				ENA=1;
		if(pwm_right_val==pwm_t)
				ENB=1;
}