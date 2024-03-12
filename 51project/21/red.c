//
 
#include <reg52.h>
#define uint  unsigned int
#define uchar unsigned char
	
 
sbit IR = P3^2;
unsigned char Time_width;
unsigned char Ir_Value[4];
//
void DelayMs(unsigned int x) //延迟大约0.1ms 或 100us
{
	unsigned char y;
	while(x--)
	{
		for (y=0;y<8;y++);
	}
}
//
void main()
{
	EA = 1;
	IT0 = 1;
	EX0 = 1;
//	IR = 1;
	while(1)
	{
		P2 = Ir_Value[3 ];
	}
}
void Read_Ir() interrupt 0   //外部中断0
{
	unsigned char i,j,count;
	Time_width = 0;
	EX0 = 0;   //关闭中断防止干扰
	if(IR==0) //判断是否是正确的信号，排除干扰
	{
		count=95; //90 * 0.1ms = 9ms,超过说明接收到错误的信号
		while((IR==0)&&(count>0)) //等待9ms的低电平过去 
		{
			DelayMs(1);
			count--;
		}
		if(IR==1) //9ms低电平已过去
		{
			count=50;  // 45 * 0.1ms = 4.5ms
			while((IR==1)&&(count>0)) //等待4.5ms的高电平过去
			{
				DelayMs(1);
				count--;
			}
			for(i=0;i<4;i++) //共有4组数据
			{
				for(j=0;j<8;j++) //接收一组数据
				{
					count=6;   //6*0.1ms=0.6ms=600us
					while((IR==0)&&(count>0))//等待560us低电平过去
					{
						DelayMs(1);
						count--;
					}
					count=55;    //50*0.1ms=5ms
					while((IR==1)&&(count>0)) //计算高电平的时间宽度
					{
						DelayMs(1);   //2.24ms/0.1ms=23
						Time_width++; //最长计算到23  55-23=32
						count--;
						if(Time_width>35)   //20*0.1=2.8ms>2.24ms
						{                   //说明已经超出信号范围
							EX0=1;  //打开外部中断
							return; //错误则直接结束中断
						}
					}
					Ir_Value[i]>>=1; //i表示第几组数据
					if(Time_width>=8) //如果高电平大于1.12ms，
					{                 //那么是1，否则默认为0，直接移位
					  Ir_Value[i]|=0x80;
					}
					Time_width=0; //用完要清零
				}
			}
		}
		if(Ir_Value[2] != ~Ir_Value[3]){return;}  //错误则重新开始，退出中断
	}
	EX0 = 1;  //接收完毕，打开中断
}
 
//