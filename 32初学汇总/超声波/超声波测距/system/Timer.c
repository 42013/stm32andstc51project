#include "stm32f10x.h"                  // Device header
#include "Delay.h"

uint32_t msCount;
//定时器配置，获取时间，72MHZ/（TIM_Period+1）/（TIM_Prescaler+1）=20HZ 相当于50ms进一次中断
void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_InternalClockConfig(TIM4);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 50000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//标志位更新
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	TIM_ClearITPendingBit(TIM4, TIM_FLAG_Update); //清除更新中断，免得一打开中断立即产生中断
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);    //打开定时器更新中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
    TIM_Cmd(TIM4,DISABLE);     
}

void OpenTimer()        //打开定时器
{
        // /*清除计数器*/
	TIM_SetCounter(TIM4,0);
	msCount = 0;
	TIM_Cmd(TIM4,ENABLE);//使能定时器
}
 
void CloseTimer()        //关闭定时器
{
       // /*关闭计数器使能*/
	TIM_Cmd(TIM4,DISABLE);
}

uint32_t  GetEchoTimer(void)
{
	msCount += TIM_GetCounter(TIM4);//获取计TIM2数寄存器中的计数值，一边计算回响信号时间
	TIM4->CNT = 0;  //将TIM2计数寄存器的计数值清零
	Delay_ms(50);
	return msCount;
}

void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		msCount++;
	}
}
