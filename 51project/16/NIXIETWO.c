#include <REGX52.H>
#include "intrins.h"

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

unsigned char RxdByte;
sbit BT_TX = P3 ^ 1;
sbit BT_RX = P3 ^ 0;
 
void UartInit(void)
{
    TMOD = 0x20;
    TL1 = 0xfd;
    TH1 = 0xfd;
    TR1 = 1;
    SM0 = 0;
    SM1 = 1;
    REN = 1;
    TI = 0;
}

char bluetooth_recv(char ch)
{
    while (!RI); 
    ch = SBUF;
    RI = 0;
	return ch;
}

void main() 
{ 
			UartInit(); 
			LSA=0;
			LSB=0;
			LSC=0;
			while (1) 
			{ 
				char ch = bluetooth_recv();
					switch(ch)
					{
						case '1':LSA = 0;LSB = 0;LSC = 0;P0=0x06;break;
						case '2':LSA = 0;LSB = 0;LSC = 0;P0=0x5B;break;
					}
      } 
}
void UART_ISR() interrupt 4 
{
			if (RI) 
			{ 
						RI = 0; 
						RxdByte=SBUF;
						SBUF=RxdByte;
			} 
			if (TI) 
			{ 
						TI = 0; 
			} 
}