#include <reg52.h>
#include <intrins.h>
sbit PWM = P2^0;  //设定PWM输出的I/O端口
unsigned char count = 0;
unsigned char timer1 ;
/*
对于180°舵机
t = 0.5ms——————-舵机会转动 0 ° 
t = 1.0ms——————-舵机会转动 45°
t = 1.5ms——————-舵机会转动 90°
t = 2.0ms——————-舵机会转动 135°
t = 2.5ms——————-舵机会转动180
*/

 
 
/*延时程序*/
void delay1s(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}
 
/*定时器T0初始化*/
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
	
/*T0中断初始化*/
void Time0_Init() interrupt 1 
{
	TR0 = 0; 
	//TL0 = 0x50;		//设置定时初值
	//TH0 = 0xFB;		//设置定时初值
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
void main()
{
	Timer0_Init();
	while(1)
	{
		timer1 =5;//舵机恢复到0°的位置
		count=0;//让定时器重新计数
		delay1s();
		timer1 =8;//舵机旋转
		count=0;
		delay1s();
	}
}
