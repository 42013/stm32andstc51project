#include <REGX52.H>
#include <intrins.h>
sbit BEEP = P2^5;
 
unsigned char expected[] = {0x55, 0x00, 0x03, 0x11, 0x00, 0xec};
//unsigned char a;
 unsigned int  flag;
unsigned int ms=1000,i;
void Delay(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
while(xms--){
	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}
}

/*void UartInit(void)		//4800bps@11.0592MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xF4;		//设定定时初值
	TH1 = 0xF4;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}*/
void Buzzer_Delay()  //@12.000MHz
{
 unsigned char i;
  _nop_  ();
 i = 80;
 while (--i);
}
	void UART_Init()	//9600bps@12.000MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA=1;
	ES=1;
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
	Delay(800);
	P0=0x00;
}
/*void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}*/

void main()
{
	char data_msg = 'a';
	UART_Init();
	while(1)
	{
		Delay(1000);
		SBUF = data_msg;
	}
}
/*void UART_Routine() interrupt 4
{
	if(RI==1)
		{
			if(P3_0==0){
				SBUF=0xF0;
			P2=~SBUF;
		for(i=0;i<ms*0.5;i++)
   {
   BEEP=!BEEP;
   Buzzer_Delay();
		 Delay(1000);
		 Nixie(1,2);
   } 
 }
}
}*/
