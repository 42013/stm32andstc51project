#include <REGX52.H>
#include <intrins.h>
typedef unsigned int uint  ;
typedef unsigned char uchar	;
sbit BEEP = P2^5;
sbit Trig=P2^1;
sbit Echo=P2^0; 
sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
unsigned int number1,number2,number3,c;
float time,distance;
void Time0Init()
{
	TMOD |= 0x01;		
	TL0 = 0x00;		
	TH0 = 0x00;	
	TR0 = 0;	
}

//0x06|0x80
void ultrasonicwave_init(void)
{
	Trig=0;
	Echo=1;
	Time0Init();
}	
int dot = 5;
void mioo() interrupt 0
{
	dot--;
	if(dot )
		dot = 6;
	while(!P3_2);
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

void startHC()
{
    Trig=1; //set
		delay(2);
		Trig=0; //reset 
}
void Buzzer_Delay()  //@12.000MHz
{
 unsigned char i;
  _nop_  ();
 i = 80;
 while (--i);
}
void zong()
{
	   Time0Init();
	   startHC();
	while(Echo == 0);
        TR0 = 1;
     while(Echo == 1);
        TR0 = 0;
    time = (TH0 * 256 + TL0)*1.085;
    distance = time * 0.017;
	distance=distance*10;
	c=(int)distance;
    number1=c/1000%10;
		number2=c/100%10;
		number3=c/10%10;
	if(distance<=1000){
    uint ms=1000,i;
		for(i=0;i<ms*0.1;i++)
   {
   BEEP=!BEEP;
   Buzzer_Delay();
   }
 }else{
			 BEEP=1;
			 delay(50);
			 BEEP=0;
			 delay(50);
	}
 }
unsigned char Nixietable[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void Nixie(unsigned char location,unsigned char number){
	switch(location){
		case 1:P2_4=1;P2_3=1;P2_2=1; break;
		case 2:P2_4=1;P2_3=1;P2_2=0; break;
		case 3:P2_4=1;P2_3=0;P2_2=1; break;
		case 4:P2_4=1;P2_3=0;P2_2=0; break;
		case 5:P2_4=0;P2_3=1;P2_2=1; break;
		case 6:P2_4=0;P2_3=1;P2_2=0; break;
		case 7:P2_4=0;P2_3=0;P2_2=1; break;
		case 8:P2_4=0;P2_3=0;P2_2=0; break;
	}
	P0=Nixietable[number];
	delay(800);
	P0=0x00;
}


void main(){
	  ultrasonicwave_init();//启动并计时
while(1)
	   {
		 zong();
			Nixie(8, 0);
		 delay(10);
		 Nixie(7, number1);
		 delay(10);
		 Nixie(6, number2);
		 delay(10);
		 Nixie(5, number3);
		 delay(10);
 if(k1==0)
	 {
	   delay(1);
	   if(k1==0)
	   {
			delay(1);
			if(k1==1)
			{
				delay(1);
			}
		}
		while(!k1);//cm
		while(1)
	   {
		zong();
			 Nixie(8, 0);
		 delay(10);
			 Nixie(7, number1);
		 delay(10);
		Nixie(6, number2);
		delay(10);
		Nixie(5, number3);
		delay(10);
			if(k2==0||k3==0)
	       {
			delay(1);
			if(k2==0||k3==0)
			{
				delay(1);
				break;
			}
		   }
		}
	}

 if(k2==0)
	 {
	  delay(1);
	  if(k2==0)
	  {
			if(k2==1)
			{
				delay(1);
			}
	  }
	   	 while(!k2);//DM
	  while(1)
	  {
		  zong();
			Nixie(8,0);
		 delay(10);
		 Nixie(7, 0);
		 delay(10);
		 Nixie(6, number1);
		 delay(10);
		 Nixie(5, number2);
		 delay(10);
		  if(k1==0||k3==0)
			{
				if(k1==0||k3==0)
			{
				delay(1);
				break;
			}
			}
	  }
	  }
	 
 if(k3==0)
	 {
	  delay(1);
	  if(k3==0)
	  {
      if(k3==1)
			{
				break;
			}
		}
		while(!k3);
		while(1)//M
		{
		 zong();
		 Nixie(8, 0);
		 delay(10);
		 Nixie(7, 0);
		 delay(10);
		 Nixie(6, 0);
		 delay(10);
			Nixie(5, number1);
		 delay(10);
			if(k1==0||k2==0)
			{
			if(k1==0||k2==0)
			{
				delay(1);
				break;
			}
			}
		}
	  }
    }
}