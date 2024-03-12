#include <REGX52.H>
#include <intrins.h>
	sbit k1=P2^1;
	sbit k2=P2^2;
	sbit k3=P2^3;
	sbit k4=P2^4;
	sbit k5=P2^5;
	sbit k6=P2^6;
	sbit k7=P2^7;
	unsigned char RxdByte;
	unsigned char receiveData;

/*void Uart_Init(void)		//9600bps@12.000MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	//AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
	//AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设定定时器1为16位自动重装方式
	TL1 = 0xE6;		//设定定时初值
	TH1 = 0xFF;		//设定定时初值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}*/

	void Uart_Init()
{
	 PCON=0x00;
	 SCON=0x50;
	 TMOD |= 0x20;
	 TL1 = 0xFD;
	 TH1 = 0xFD;
	//TL1 = 0xD9;		//设定定时初值
	//TH1 = 0xD9;		//设定定时器重装值
		ET1=0;
	 TR1 = 1;
	 EA = 1;
	 ES = 1;   
}

void sendByte(char data_msg)
	{
			SBUF = data_msg;
			while(!TI);
			TI = 0; 
	}
 
/*void sendString(char* str)
{
	while( *str != '\0')
		{
			sendByte(*str);
			str++;
		}
}*/
 
void delay(unsigned int t)
{
		while(t--);
}
	/*void Delay100ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 144;
	k = 71;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}*/
/*void delay1s()   //误差 0us
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}*/
void main()
{
	while(1){
		Uart_Init();	
		while(1)  
		{	
			if(k1==0)
			{
						while(k1 ==0);
						delay(50);
						//sendString("7");
						sendByte(1);
			}
			if(k2==0)
			{
						while(k2==0);
						delay(50);
	//					sendString("2");
				sendByte(2);
			}
			if(k3==0)
			{
						while(k3==0);
						delay(50);
						//sendString("3");
				sendByte(3);
			}
			if(k4==0)
			{
						while(k4==0);
						delay(50);
						//sendString("4");
						sendByte(4);
			}
			if(k5==0)
			{
						while(k5==0);
						delay(100);
						//sendString("5");
							sendByte(5);
			}
			if(k6==0)
			{
						while(k6==0);
						delay(100);
						//sendString("6");
						sendByte(6);
			}
			if(k7==0)
			{
						while(k7==0)
						delay(50);
						//sendString("7");
						sendByte(7);
			}
			
		/*if(k1==0)
			while(k1==0)
			Delay100ms();
			{			
				if(k4==0&&k3==1)
							{
								while(k4==0&&k3==1)
								Delay100ms();	
						//sendString("9");
								sendByte(9);
							}else if(k4==1&&k3==0){
							while(k4==1&&k3==0)	
							Delay100ms();	
						//sendString("8");
								sendByte(8);
						}else if(k4==1&&k3==1){
							while(k4==1&&k3==1)
							Delay100ms();	
						//sendString("1");
							sendByte(1);
				}	
			}*/
			
		}				
					}
				}