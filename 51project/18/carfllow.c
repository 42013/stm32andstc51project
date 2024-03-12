#include "reg52.h"
#include <intrins.h>
#include <string.h>
 
sfr AUXR = 0x8E;
 
sbit left_con1A = P1^1;
sbit right_con1A = P1^3;
sbit tracingLeft = P1^5;
sbit tracingRight = P1^6;
 
char leftSpeed;
char rightSpeed;
int cntLeft = 0;
int cntRight = 0;
 
//前进
void goForward()
{
	leftSpeed = 20;
	rightSpeed = 20;
}
 
//停止
void goStop()
{
	leftSpeed = 0;
	rightSpeed = 0;
}
 
void Timer0Init(void)		//1毫秒@11.0592MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	//定时器初值为1ms
	TL0 = 0x66;		
	TH0 = 0xFC;		
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;
	EA  = 1;
}
 
void Timer1Init(void)		//1毫秒@11.0592MHz
{
	AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	//定时器初值为1ms
	TL1 = 0xCD;		
	TH1 = 0xD4;		
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	ET1 = 1;
	EA  = 1;
}
 
void tracingMode()
{	
	if(tracingLeft == 0 && tracingRight == 0){  //
		goForward();
	}
 
	if(tracingLeft == 0 && tracingRight == 1){
		goRight();
	}
 
	if(tracingLeft == 1 && tracingRight == 0){
		goLeft();
	}
 
	if(tracingLeft == 1 && tracingRight == 1){
		goStop();
	}
}
 
void main()
{
	Timer0Init();
	while(1){
		tracingMode();
	}
}
 
//定时器0的中断函数
void Time0Handler() interrupt 1
{
	cntLeft++;
	TL0 = 0x66;		
	TH0 = 0xFC;
	if(cntLeft < leftSpeed)
	{
		goLeftForward();
	}else{
		goLeftStop();
	}
	if(cntLeft == 20){
		cntLeft = 0;
	}
}
