#include "reg52.h"
#include <intrins.h>
 
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
sbit xhg=P1^0;
unsigned char pwm_left_val;
unsigned char pwm_right_val;
unsigned char pwm_t;
unsigned char count=0;
unsigned char timer1;
unsigned char receiveDate;
unsigned int control=170;
unsigned int normal;
unsigned int change;


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
}*/
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

 void goForward()
{
		normal=control;
		IN1= 0;  IN2=1;
  		IN3 = 1;	IN4=0;
	pwm_left_val=normal;
	pwm_right_val=normal;
	timer1=12;
}
void godown()
{
	normal=control;
		IN1= 1;  IN2=0;
		IN3 =0;	IN4=1;
	pwm_left_val=normal;
	pwm_right_val=normal;
}
void gostop()
{
		IN1= 0;  IN2=1;
		IN3 = 1;	IN4=0;
		//timer1=13;
}
void go(){
	IN1= 1;  IN2=0;
		IN3 = 0;	IN4=1;
	normal=control;
	pwm_left_val=normal;
	pwm_right_val=normal;
}
void go1(){
	IN1= 1;  IN2=0;
		IN3 = 0;	IN4=1;
	normal=control;
	pwm_left_val=normal;
	pwm_right_val=normal;
	timer1=14;
}
void go2(){
	IN1= 1;  IN2=0;
		IN3 = 0;	IN4=1;
	normal=control;
	pwm_left_val=normal;
	pwm_right_val=normal;
	timer1=9;
}
void goright(){
		IN1= 1;  IN2=0;
		IN3 = 0;	IN4=1;
	change=control+20;
	normal=control;
	pwm_left_val=change;
	pwm_right_val=normal;
	timer1=10;
}
void goleft(){
	change=control+20;
	normal=control;
		IN1= 1;  IN2=0;
		IN3 = 0;	IN4=1;
	pwm_left_val=normal;
	pwm_right_val=change;
	timer1=13;
}
void putleft(){
	change=control+20;
	normal=control;
	IN1= 1;  IN2=0;
		IN3 = 0;	IN4=1;
	pwm_left_val=change+5;
	pwm_right_val=normal-5;
	timer1=14;
}
void putright(){
	change=control+20;
	normal=control;
		IN1= 1;  IN2=0;
		IN3 = 0;	IN4=1;
	pwm_left_val=normal-5;
	pwm_right_val=change+5;
	timer1=9;
}
void moter_add()
	{
			control-=10;
	}
void moter_less()
	{	
			control+=10;
	}
	
	/*void main() 	     //主函数			     
{ 	
	Timer0_Init();
	Com_init();//串口初始化和定时器初始化
	while(1){ 
	  if(RI==1){	 // 判断是否有数据到来
			receive_data = SBUF; //将收/发数据缓存器SBUF中的数据存入变量
		    DateCtrl();			 //调用数据处理函数
		    RI = 0;
		   }       
      } 
		}*/
		void Timer0_Routine() interrupt 1 
{
		TR0=0;
		TH0 = 0xff;   //定时常数 0.1ms 晶振为11.0592MHz
		TL0 = 0xa4;
		pwm_t++; 
		if(pwm_t==255)
				pwm_t=ENA=ENB=0;
		if(pwm_left_val==pwm_t)
				ENA=1;
		if(pwm_right_val==pwm_t)
				ENB=1;
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
/*void receive(unsigned char m)
{
switch(m)
		{
			case(0):	gostop();
				break;
			case (1): go();
				break;	  		
			case (2):	godown(); 
				break;	  		   		
			case (3): goleft();
				break;
			case (4): goright();		  //right 
				break;  
			case (5): moter_add();
			  break;
			case (6): moter_less();
			  break;
			case (7): tracingMode();
			  break;
			case (8): go();	
						left();
						break;
			case (9): go();	
						right();
						break;	
		}
	}*/
	void Uart_Init()
{
	 PCON=0x00;
	 SCON=0x50;
	 TMOD |= 0x20;
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1=0;
	 TR1 = 1;
	 EA = 1;
	 ES = 1;   
}
void Uart_Routine() interrupt 4
{ 
	gostop();
	if(RI)
	{
	SBUF=receiveDate;
	receiveDate=SBUF;	
	RI=0;
	}
	if(TI)
	{
	TI=0;
	}
}
void main()
{	
	Timer0_Init();
	Uart_Init();
	while(1)
	{
	//receive(receiveDate);
	if(receiveDate==0)
	{
		gostop();
	}else if(receiveDate==1)
	{
		go();
	}else if(receiveDate==2)
	{
		godown();
	}else if(receiveDate==3)
	{ 
		timer1=8;
	}else if(receiveDate==4)
	{
		timer1=14;
	}else if(receiveDate==5)
	{
	timer1=11;	
	moter_add();
	}else if(receiveDate==6)
	{
		timer1=11;
		moter_less();
	}else if(receiveDate==7)
	{
	tracingMode();
	}
	}
}