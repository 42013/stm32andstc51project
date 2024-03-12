#include <REGX52.H>
#include <intrins.h>
sbit left_con1A = P1^0;//س
sbit left_con2A = P1^1;
sbit right_con1A = P1^2;//Ԓ
sbit right_con2A = P1^3;
sbit driect=P2^3;//צܺ      
sbit IO=P1^4;//С܆ڜ
sbit LeftSersor = P3^6;
sbit Le = P3^4;
sbit MiddleSersor=P3^3;
sbit Ri = P3^2;
sbit RightSersor = P3^5;
unsigned int counter,compare,num;
unsigned int counter1,compare1;
//unsigned int counter2,compare2;
int receive_data ,Work_Mode,flag;
sbit Buzzer=P2^5;
//unsigned char flag=1
void Uart0_Init()
{

    RCAP2L=0xD9;//9600波特率对应 FFD9，低位为D9

    RCAP2H=0xFF;//高位为FF

    T2CON=0x34;//RCLK、TCLK、TR2置1

    SCON=0x50;//串口工作模式1，接收使能

    ES=1;//打开接收中断

    EA=1;//打开总中断

}

void Timer0Init(void)		//50΢ī@12.000MHz
{
	TMOD &= 0xF0;
	TMOD |=0x01;
	TL0 = 0xF8;				//设置定时初始值
	TH0 = 0xFF;
	TF0 = 0;
    TR0 = 1;
    ET0 = 1;
    EA  = 1;
   	PT0=0;
}
void Delay1000us()		//@12.000MHz
{
	unsigned char i, j;
	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

void Buzzer_Delay500us()		//@12.000MHz
{
	unsigned char j;

	_nop_();
	j= 247;
	while (--j);
}
void Buzzer_Time(unsigned int ms )
{
	unsigned int i;
	for(i=0;i<ms*2;i++)
	{
		Buzzer=~Buzzer;
		Buzzer_Delay500us();
		
	}
}

void driection()
{ 
	  compare1=0;
		left_con1A = 1; 
		left_con2A = 0;
		right_con1A = 1;
		right_con2A = 0;
		if(LeftSersor==0&&Le==0&&MiddleSersor==1&&Ri==0&&RightSersor==0)
		{
			num=30;

		}
		if(LeftSersor==0&&Le==1&&MiddleSersor==0&&Ri==0&&RightSersor==0)
		{
			num=27;	
		}	
		if(LeftSersor==0&&Le==0&&MiddleSersor==0&&Ri==1&&RightSersor==0)
		{
			num=33;
		}
		if(LeftSersor==1&&Le==1&&MiddleSersor==0&&Ri==0&&RightSersor==0)
		{
			num--;
		}
		if(LeftSersor==0&&Le==0&&MiddleSersor==0&&Ri==1&&RightSersor==1)
		{
			num++;
		}
		if(LeftSersor==1&&Le==0&&MiddleSersor==0&&Ri==0&&RightSersor==0)
		{
			num=25;
		}
		if(LeftSersor==0&&Le==0&&MiddleSersor==0&&Ri==0&&RightSersor==1)
		{
			num=35;
		}
//		if(LeftSersor==0&&Le==0&&MiddleSersor==0&&Ri==0&&RightSersor==0)
//		{
//			num=30;
//			compare1=95;
//		}
//		if(LeftSersor==1&&Le==1&&MiddleSersor==1&&Ri==1&&RightSersor==1)
//		{
//			num=30;
//			compare1=95;
//		}
		if(num>=35)
		{
			num=35;
		}
			if(num<=25)
		{
			num=25;
		}
		compare=num;
			 
}
void go()
{
	 flag=1;
	compare1=50;
//	left_con1A = 1; 
//		left_con2A = 0;
//		right_con1A = 1;
//		right_con2A = 0;
 if(counter1<=compare1&&flag==1)
	{
		left_con1A = 1; 
		left_con2A = 0;
		right_con1A = 1;
		right_con2A = 0;
	}
	else		{
		left_con1A = 0; 
		left_con2A = 0;
		right_con1A = 0;
		right_con2A = 0;
	}
}
void stop()
{
	//flag=3;
   compare1=0;
	left_con1A = 0; 
		left_con2A = 0;
		right_con1A = 0;
	right_con2A = 0;
}
void back()
{
	flag=0;
	compare1=50;
//	left_con1A = 0; 
//		left_con2A = 1;
//		right_con1A = 0;
//		right_con2A = 1;
	if(counter1<=compare1&&flag==0)
	{
		left_con1A = 0; 
		left_con2A = 1;
		right_con1A = 0;
		right_con2A = 1;
	}
	else		{
		left_con1A = 0; 
		left_con2A = 0;
		right_con1A = 0;
		right_con2A = 0;
	}
}
void main()
{
  Timer0Init();
	counter=0;
	counter1=0;
	driect = 1;
	//if(flag)
	//{
	Uart0_Init();
	
	//counter2=0;
	
	while(1)//发送端有while，要按一下才能让死循环无效
	{
				if(Work_Mode)
				{
				 driection();
				}
				else
				{
				Buzzer_Time(100);
				}
	 }
}
void Timer0_Rountine() interrupt 1
{
	TR0 = 0;
	TL0 = 0xF8;				//设置定时初始值
	TH0 = 0xFF;
	counter++;
	counter1++;
	//counter2++;
    if (counter ==2500)
	{
        counter = 0;
    }
    if (counter<compare)
	{
        driect = 1;
    }
	else
	{
		driect = 0;
    }
	if (counter1 >= 100)
	{
        counter1 = 0;
    }
	


	
//	if (counter2 == 100)
//	{
//        counter2 = 0;
//    }
	//已被删除，或者将其放主函数里也可
	TR0 = 1; 
}
void Com_Int(void) interrupt 4
{
//int cm=27;
	  if(RI)
		{
			//flag=1;
			receive_data=SBUF;
			 //SBUF=receive_data;
     //  compare=27;
					switch(receive_data) 
        { 
           case (2):  //前进 
						
		  //compare=cm; 
            go();
					 	
					 //flag=1;
					 Work_Mode=0; 
					 
            break;  
        case (1): //停止
					//compare1=0;
				//compare2=0;
				//compare=27;   
        stop();
				//flag=1;
				 Work_Mode=0; 
				 
            break;  
				case (6): //
					 //compare2++;  
	//compare=cm;
      back();
	   
//			//compare1=70;
			//	flag=1;
				 Work_Mode=0; 
            break;  


        case (4):  
		// compare=27;
				compare--;
				//cm=compare;
//	flag=1;
				 Work_Mode=0; 

            break;//
				
        case (5): //
				//compare=27;
				compare++;
				//cm=compare;//只能是定值？
//	flag=1;
				 Work_Mode=0; 
            break; 
        case (8): //jiansu 
            compare1++; 
				//compare2--;
				//flag=1;
				 Work_Mode=0; 
            break;  
	      case (0):
					//flag=1;
			Work_Mode=1; 
		 // compare1=95;
			driection();
				break;  //转变为循迹功
				default:  
         break;  
	        }
	//	cm=compare;//bushan
				SBUF=receive_data;
					 RI = 0;
//					flag=0;
				}
		while(!TI);	
		TI=0;
	
}