#include "stm32f10x.h"
#include "sys.h"
#include "PWM.h"

void TIM3_PWM_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	TIM_TimeBaseStructure.TIM_Period =1999; //装入自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Prescaler =71; //设置TIM3的时钟预分频系数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5; //定义红外引脚
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1; //定义电机引脚 
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP ; //推挽
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7;//定义电机引脚 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//选择定时器模式：TIM脉冲宽度调制模式
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=50;
	
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
