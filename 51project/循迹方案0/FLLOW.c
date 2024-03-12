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
sbit right_light= P1^6;
sbit middle_light=P1^7;
sbit PWM = P3^7;  //设定PWM输出的I/O端口

unsigned char pwm_left=210;
unsigned char pwm_right=210;
unsigned char pwm_t;
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
t = 2.5ms——————-舵机会转动 180°
*/
void Timer0_Init()           
{
    TMOD &= 0x00;
    TMOD |= 0x01; //定时器T0设置成方式1
 
    //TL0 = 0x50;		//设置定时初值
//	TH0 = 0xFB;		//设置定时初值
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

 void Timer1Init()		//100微秒@12.000MHz
{
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0x50;		//设置定时初值
	TH1 = 0xFB;		//设置定时初值
	TF1 = 0;		 //清除TF1标志
	TR1 = 1;		//定时器1开始计时
	EA	=	1;
	ES	=	1;
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
	
/*void godown()
{
		IN1= 1;  IN2=0;
		IN3 = 0;	IN4=1;
}*/
void goForward()
{
		IN1= 0;  IN2=1;
		IN3 = 1;	IN4=0;
		timer1=12;
}

void goright(){
	IN1= 0;  IN2=1;
		IN3 = 1;	IN4=0;
	timer1=10;
}
void goleft(){
		IN1= 0;  IN2=1;
		IN3 = 1;	IN4=0;
	timer1=14;
}
void putleft(){
	IN1= 0;  IN2=1;
		IN3 = 1;	IN4=0;
	timer1=15;
}
void putright(){
	IN1= 0;  IN2=1;
		IN3 = 1;	IN4=0;
	timer1=9;
}
void goForwardup()
{
	leftSpeed = 16;
	rightSpeed = 24;
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
	if(left_light==1&&middle_light==1&&right_light==0)//س
	{
		goleft();
		if(left_light==0&&middle_light==1&&right_light==0)
		{
			goForward();
		}

	}
	if(left_light==0&&middle_light==1&&right_light==1)//Ԓ
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
	Timer1Init();
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
		/*cntLeft++;
	cntRight++;
	if(cntLeft < leftSpeed&&cntRight < rightSpeed)
	{
		goForward();
	}else{
		gostop();
	}
	if(cntLeft == 20&&cntRight == 20){
		cntLeft = 0;
		cntRight = 0;
	}*/
}
