#include <REGX52.H>
#include <intrins.h>
	sfr AUXR = 0x8E;
	sbit beep=P2^5;
	sbit k1=P3^1;
	sbit k2=P3^0;
	sbit k3=P3^2;
	sbit LSA=P2^2;
	sbit LSB=P2^3;
	sbit LSC=P2^4;
	typedef unsigned u16;
	unsigned char RxdByte;
	unsigned char receiveData;


void ConfigUART(u16 baud)
	{
		SCON=0x50;
		TMOD&=0x0F;
		TMOD|=0x20;
		TH1=256 -(11059200/12/32)/baud; 
		TL1=TH1;
		ET1=0;
		ES=1;
		TR1=1;
	}
	

void sendByte(char data_msg)
	{
			SBUF = data_msg;
			while(!TI);
			TI = 0; 
	}
 
void sendString(char* str)
{
	while( *str != '\0')
		{
			sendByte(*str);
			str++;
		}
}
 
void delay(unsigned int t)
{
		while(t--);
}

void Buzzer_Delay()  //@12.000MHz
{
 unsigned char i;
  _nop_  ();
 i = 80;
 while (--i);
}


void main()
{
	while(1){
		delay(1000);
		EA = 1;
	  ConfigUART(9600);
		while(1)
		{
					}
				}
			}
void InterruptUART() interrupt 4
	{
			if(RI)
					{
								RI=0;
								RxdByte=SBUF;
								SBUF=RxdByte;
					}
			if(TI)
					{
						    TI=0;
					}
	}
	/*if(k1==1){
			delay(10);
			RxdByte='c';
			beepchoice();
		}else if(k1==0){
			delay(10);
			RxdByte='a';
			beepchoice();
		}else if(k2==1){
			delay(10);
			RxdByte='d';
			beepchoice();
		}else if(k2==0){
			delay(10);
			RxdByte='b';
			beepchoice();
		}*/
	/*switch(RxdByte)
					{
						case 'a':beep_one();break;
						case 'b':beep_two();break;
					}*/