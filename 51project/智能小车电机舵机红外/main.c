#include <REGX52.H>
#include <intrins.h>
sbit IN1=P1^1;
sbit IN2=P1^2;
sbit IN3=P1^3;
sbit IN4=P1^4;

sbit EN1A=P2^1;
sbit EN2A=P2^2;
sbit left_light=P1^5;
sbit middle_light=P1^7;
sbit right_light=P1^6;
sbit PWM = P2^0;

unsigned char counter=0;
unsigned char compareA,compareB;
unsigned char count=0;
unsigned char PWM_count=15;

/*void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void delay_ms(unsigned int n)
{
    unsigned int i,y;
    for(i=n;i>0;i--)
        for(y=114;y>0;y--);
}*/
void Timer0Init()
{
	TMOD |= 0x01;
	TL0 = 0xA4;	
	TH0 = 0xFF;	
	TF0 = 0;
	EA=1;
	ET0=1;
	TR0 = 1;
}
void carlm_go()		  			//左电机直行
{
	IN1=0;
	IN2=1;
}
void carrm_go()		  			//右电机直行
{
	IN3=1;
	IN4=0;
}
void carlm_back()					//左电机后退
{
	IN1=0;
	IN2=1;
}
void carrm_back()		       //右电机后退
{
	IN3=1;
	IN4=0;
}
void carlm_stop()		       //左电机停止
{
	IN1=0;
	IN2=0;
}
void carrm_stop()		       //右电机停止
{
	IN3=0;
	IN4=0;
}
void car_go()				       //小车前进
{
PWM_count=14;
compareB=80;
compareA=80;
carlm_go();
carrm_go();
}
void car_stop()			       //小车停止
{
PWM_count=15;
compareB=80;
compareA=80;
carlm_stop();
carrm_stop();
}
void car_back()		         //小车后退
{
PWM_count=12;
compareB=80;
compareA=70;
carlm_back();
carrm_back();
}
void car_goright()	       //小车前右
{
PWM_count=10;
compareB=70;
compareA=80;
carlm_go();
carrm_go();
}
void car_goleft()	         //小车前左
{
PWM_count=18;
compareB=80;
compareA=70;
carlm_go();
carrm_go();}
void car_inplaceleft()     //小车原地左
{
PWM_count=19;
compareB=80;
compareA=50;
carlm_go();
carrm_go();
}
void car_inplaceright()    //小车原地右
{
PWM_count=11;
compareB=50;
compareA=80;
carlm_go();
carrm_go();
}
void Infrared_tracking()    //红外循迹模块
{	
	if(left_light==1&&middle_light==1&&right_light==1)//全黑
	{
		car_go();
	}
	if(left_light==0&&middle_light==1&&right_light==0)//直线
	{
		car_go();
	}
	if(left_light==1&&middle_light==0&&right_light==0)//大右转
	{
		car_inplaceright();
			if(left_light==0&&middle_light==1&&right_light==0)
			{
			car_go();
			}
	}

	if(left_light==0&&middle_light==0&&right_light==1)//大左转
	{	
		car_inplaceleft();
			if(left_light==0&&middle_light==1&&right_light==0)
			{
			car_go();
			}
	}
	if(left_light==1&&middle_light==1&&right_light==0)//左
	{
		car_goleft();
		if(left_light==0&&middle_light==1&&right_light==0)
		{
			car_go();
		}

	}
	if(left_light==0&&middle_light==1&&right_light==1)//右
	{
		car_goright();
		if(left_light==0&&middle_light==0&&right_light==0)
		{
			car_go();
		}

	}

}

void main()
{	
	Timer0Init();
	
	while(1)
	{
		Infrared_tracking();
	}
}
void Timer0_Routine() interrupt 1
{
	TL0=0xA4;
	TH0=0xFF;
	compareA=90;
	compareB=90;
	counter++;
	if(counter>=100)
	{
	 counter=0;
	}
	if(counter<compareA)
	{
	  EN1A=1;

	}
	else
	{
		EN1A=0;

	}
	if(counter<compareB)
	{
	  EN2A=1;

	}
	else
	{
		EN2A=0;

	}
	count++;
	count%=200;
	if(count <PWM_count) 
	{ 
		PWM = 1; 
	}
	else 
	{ 
		PWM = 0; 
	}
}
