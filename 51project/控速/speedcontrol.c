#include "reg52.h"
#include <intrins.h>
sbit IN1 = P1^1;
sbit IN2 = P1^2;
sbit IN3 = P1^3;
sbit IN4 = P1^4;
sbit k1=P3^1;//速度增加
sbit k2=P3^0;//速度减小
char leftspeed;
char rightspeed;
int cntLeft = 0;
int cntRight = 0;

void goForward()
{
		IN1= 1;  IN2=0;
		IN3 = 1;	IN4=0;
}

void gostop()
{
	IN1= 0;  IN2=0;
		IN3 = 1;	IN4=1;
}
void Timer1Init()		//100微秒@12.000MHz
{
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0x50;		//设置定时初值
	TH1 = 0xFB;		//设置定时初值
	TF1 = 0;		 //清除TF1标志
	TR1 = 1;		//定时器1开始计时
}
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
void keyscan()
{	
	if(k1==0)
	{	
		if(k1==0)
			delay(100);
		{
			leftspeed+=5;
			rightspeed+=5;
		}
		while(!k1);	
	}
	if(k2==0)
	{	
		if(k2==0)
			delay(100);
		{
			leftspeed-=5;
			rightspeed-=5;
		}
		while(!k2);	
	}
}
void main()
{
	Timer1Init();
	while(1){
		keyscan();
	}
}

void Time1Handler() interrupt 1
{
	cntLeft++;
	cntRight++;
	TL1 = 0x50;		//设置定时初值
	TH1 = 0xFB;		//设置定时初值
	if(cntLeft < leftspeed&&cntRight < rightspeed)
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