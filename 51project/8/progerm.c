#include <REGX52.H>
#include <intrins.h>
typedef unsigned int uint  ;
typedef unsigned char uchar	;
sbit BEEP = P3^0 ;
sbit Trig=P1^1;
sbit Echo=P1^0;
sbit k1=P3^7;
unsigned int distance,number1,number2,number3;
float time;
void Time0Init()
{
	TMOD |= 0x01;		
	TL0 = 0x00;		
	TH0 = 0x00;	
	TR0 = 0;	
}

//void delay(uint i){
//	 while(i--){
//	 }
//}

void ultrasonicwave_init(void)
{
	Trig=0;
	Echo=1;
	Time0Init();
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
    Trig=1; 
		delay(2);
		Trig=0;  
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
    time = (TH0 * 256 + TL0)*1.085;
    distance = time * 0.017;
    number1=distance/100%10;
		number2=distance/10%10;
		number3=distance/1%10;
	if(distance<=100){
    uint ms=1000,i;
		for(i=0;i<ms*0.3;i++)
   {
   BEEP=!BEEP;
   Buzzer_Delay(); 
   }
 }else{
			 BEEP=1;
			 delay(100);
			 BEEP=0;
			 delay(100);
	}
 }
unsigned char Nixietable[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void Nixie(unsigned char location,unsigned char number){
	switch(location){
		case 1:P2_0=1;P2_1=1;P2_2=1; break;
		case 2:P2_0=1;P2_1=1;P2_2=0; break;
		case 3:P2_0=1;P2_1=0;P2_2=1; break;
		case 4:P2_0=1;P2_1=0;P2_2=0; break;
		case 5:P2_0=0;P2_1=1;P2_2=1; break;
		case 6:P2_0=0;P2_1=1;P2_2=0; break;
		case 7:P2_0=0;P2_1=0;P2_2=1; break;
		case 8:P2_0=0;P2_1=0;P2_2=0; break;
	}
	P0=Nixietable[number];
	delay(1);
	P0=0x00;
}


void main(){
	  ultrasonicwave_init();//启动并计时
while(1)
	   {
		 zong();
		 Nixie(2, number1);
		 delay(1);
		 Nixie(3, number2);
		 delay(1);
		 Nixie(4, number3);
		 delay(1);
			Nixie(1, 0);
		 delay(1);
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
		while(!k1);//dm
		while(1)
	   {
		zong();
			 Nixie(1, 0);
		 delay(1);
			 Nixie(2, 0);
		 delay(1);
		Nixie(3, number1);
		delay(1);
		Nixie(4, number2);
		delay(1);
		}
	}
    }
}