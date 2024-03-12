#include <REGX52.H>
#include <intrins.h>
	sfr AUXR = 0x8E;
	sbit LSA=P2^2;
	sbit LSB=P2^3;
	sbit LSC=P2^4;
	typedef unsigned u16;
	unsigned char RxdByte;
	sbit BT_TX = P3 ^ 1;
  sbit BT_RX = P3 ^ 0;

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
		EA=1;
	}
/*void sendByte(char data_msg)
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
}*/
 
/*void delay(unsigned int t)
{
		while(t--);
}*/

	
	
void main()
{
		LSA=1;
		LSB=1;
		LSC=1;
	  ConfigUART(9600);
		while(1)
		{
			char ch = bluetooth_recv();
		switch(ch){
		case '1':LSC=1;LSB=1;LSA=1;P0=0x3F; break;
		case '2':LSC=1;LSB=1;LSA=1;P0=0x06; break;
		case '3':LSC=1;LSB=1;LSA=1;P0=0x5B; break;
		case '4':LSC=1;LSB=1;LSA=1;P0=0x4F; break;
		case '5':LSC=1;LSB=1;LSA=1;P0=0x66; break;
		case '6':LSC=1;LSB=1;LSA=1;P0=0x6D; break;
		case '7':LSC=1;LSB=1;LSA=1;P0=0x7D; break;
		case '8':LSC=1;LSB=1;LSA=1;P0=0x07; break;
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