#include "stm32f10x.h"
#include "sys.h"
#include "PWM.h"



void TIM3_PWM_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE); 
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1; //定义电机引脚 
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP ; //推挽
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5; //定义红外引脚
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7;//定义电机引脚 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	TIM_TimeBaseStructure.TIM_Period =99; //装入自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Prescaler =71; //设置TIM3的时钟预分频系数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseStructure.TIM_ClockDivision=0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	

	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//选择定时器模式：TIM脉冲宽度调制模式
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=0;
	
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);//初始化TIM3_OC1
    TIM_OC2Init(TIM3,&TIM_OCInitStructure);//初始化TIM3_OC2
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);//初始化TIM3_OC3
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);//初始化TIM3_OC4
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);//使能TIM3在oc1上的预装载寄存器
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);//使能TIM3在oc2上的预装载寄存器
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);//使能TIM3在oc3上的预装载寄存器
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);//使能TIM3在oc4上的预装载寄存器
	
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);//使能TIM3的自动重装载寄存器
	

	TIM_Cmd(TIM3,ENABLE);
	
	

}

void Motor1_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5|GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	TIM3_PWM_Init();
}

void Motor2_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12|GPIO_Pin_9| GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	TIM3_PWM_Init();
}

void Forward(void)
{
		TIM_SetCompare1(TIM1,50);	
		TIM_SetCompare2(TIM1,50);	 
	    TIM_SetCompare3(TIM1,50);	
        TIM_SetCompare4(TIM1,50);
		
		IN1 =1;
		IN2 =1;
		IN3 =1;
		IN4 =1;
		
		AIN1 =1;
		AIN2 =0;
		AIN3 =1;
		AIN4 =0;
		BIN1 =1;
		BIN2 =0;
		BIN3 =1;
		BIN4 =0;

}

void Rightward(void)
{
		TIM_SetCompare1(TIM1,50);	
		TIM_SetCompare2(TIM1,50);	 
	    TIM_SetCompare3(TIM1,100);	
	    TIM_SetCompare4(TIM1,100);
		IN1 =1;
		IN2 =0;
		IN3 =0;
		IN4 =1;

}


 
void Leftward(void)
{
      TIM_SetCompare1(TIM1,100);	
	  TIM_SetCompare2(TIM1,100);	 
	  TIM_SetCompare3(TIM1,50);	
	  TIM_SetCompare4(TIM1,50);
	  IN1 =0;
      IN2 =1;    
	  IN3 =1;
	  IN4 =0;

}	


void Stopward(void)
{

		IN1 =0;
		IN2 =0;
		IN3 =0;
		IN4 =0;


}	








