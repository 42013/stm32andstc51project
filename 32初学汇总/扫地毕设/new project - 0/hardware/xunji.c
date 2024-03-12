#include "stm32f10x.h"
#include "xunji.h"  
#include "sys.h"
#include "Delay.h"
#include "switch.h"


 uint32_t a;
//电机驱动
void motor_gpio()
{
	//B10、B11、B12、B13
GPIO_InitTypeDef  GPIO_InitStructure;
	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13; 		
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	  //推挽输出 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
  GPIO_Init(GPIOB, &GPIO_InitStructure);     
  GPIO_ResetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13);
}

//红外传感器
void xunji_gpio()
{
//C0、C1、C2andc6(定点)
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11| GPIO_Pin_12; //定义红外引脚
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

//电机调速
void pwm()
{
	//B0、B1   TIM3
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	  //使能定时器3时钟 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //使能GPIOB时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用输出 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	  
	TIM_TimeBaseStructure.TIM_Period =199;    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =35;     //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //TIM向上计数模式 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);    
	//控制电机
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    //输出极性:TIM输出比较极性高
 	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	
	
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);   //使能TIM3在CCR1上的预装载寄存器
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);   //使能TIM3在CCR2上的预装载寄存器
	
	
	TIM_Cmd(TIM3, ENABLE);   //使能TIM3
}

void run()
{
		TIM_SetCompare3(TIM3,160);//right
   		TIM_SetCompare4(TIM3,165);//left
		
		AIN1 =1;
		AIN2 =0; 
		AIN3 =1;
		AIN4 =0;	
}

void back()
{		
		TIM_SetCompare3(TIM3,160);
   		TIM_SetCompare4(TIM3,165);
		
		AIN1 =0;
		AIN2 =1;
		AIN3 =0;
		AIN4 =1;	
}

void Rightward(void)
{
		TIM_SetCompare3(TIM3,160);	
		TIM_SetCompare4(TIM3,165);	 
	    	 
		AIN1 =0;
		AIN2 =1;    
		AIN3 =1;
		AIN4 =0;
}

void Leftward(void)
{		
      TIM_SetCompare3(TIM3,160);	
	  TIM_SetCompare4(TIM3,165);	 
	  
		AIN1 =1;
		AIN2 =0;
		AIN3 =0;
		AIN4 =1;	
}

void stop()
{
		AIN1 =0;
		AIN2 =0;
		AIN3 =0;
		AIN4 =0;	
}

void tryi()
{
	Leftward();
	Delay_ms(500);	
}

void floorrun()
{
	relay1_on();
	relay2_on();
	while(R==1&&M==1&&L==1)
{
		run();
}
	if(R==0&&M==0&&L==1)
{	
	Rightward();
	Delay_ms(700);
}

	if(R==0&&M==1&&L==1)
	{
	Rightward();
	Delay_ms(700);	
	}
	

	if(R==1&&M==0&&L==0)
{
	Leftward();
	Delay_ms(700);
}

	if(R==1&&M==1&&L==0)
	{
	Leftward();
	Delay_ms(700);	
	}
	
	if(R==1&&M==0&&L==1)
	{
	Rightward();
	Delay_ms(700);
	run();
	}
	
//	if(R==1&&M==0&&L==1&&a%2!=0)
//	{
//	Leftward();		
//	a++;	
//}

	while(R==0&&M==0&&L==0)
	{
		stop(); 
	}
	while(R==0&&M==1&&L==0)
	{
		run();
	}
}
