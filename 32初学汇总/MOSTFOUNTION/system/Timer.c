#include "stm32f10x.h"                  // Device header
#include "Delay.h"

uint32_t msCount ;

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 50000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//标志位更新
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
//	TIM_ICInitTypeDef	TIM_ICInitStructure;
//	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
//	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
//  	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //配置输入分配
//	TIM_ICInitStructure.TIM_ICFilter = 0x00;	  //IC2F=0000 配置输入滤波器 0 不滤波
//  	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //IC1映射到TI1
//	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	//TIM_Cmd(TIM2, ENABLE);
	TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update); //清除更新中断，免得一打开中断立即产生中断
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);    //打开定时器更新中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
    TIM_Cmd(TIM2,DISABLE);     
}

void OpenTimer()        //打开定时器
{
        //	/*清除计数器*/
	TIM_SetCounter(TIM2,0);
	msCount = 0;
	TIM_Cmd(TIM2,ENABLE);//使能定时器
}
 
void CloseTimer()        //关闭定时器
{
       //	/*关闭计数器使能*/
	TIM_Cmd(TIM2,DISABLE);
}

uint32_t  GetEchoTimer(void)
{
   uint32_t msCount;
	msCount += TIM_GetCounter(TIM2);//获取计TIM2数寄存器中的计数值，一边计算回响信号时间
	TIM2->CNT = 0;  //将TIM2计数寄存器的计数值清零
	Delay_ms(50);
	return msCount;
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		msCount++;
	}
}
