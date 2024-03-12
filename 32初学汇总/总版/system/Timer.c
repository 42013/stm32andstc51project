#include "stm32f10x.h"                  // Device header
#include "Delay.h"

uint32_t msCount;
uint32_t TIM4_CH1_CAPTURE_VAL;
uint32_t TIM4_CH1_CAPTURE_VAL1;
uint32_t TIM4_CH1_CAPTURE_VAL2;
uint8_t nn;

void Timer_Init(u16 arr,u16 psc)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_InternalClockConfig(TIM4);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//标志位更新
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	TIM_ClearITPendingBit(TIM4, TIM_FLAG_Update); //清除更新中断，免得一打开中断立即产生中断
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);    //打开定时器更新中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;				
	TIM_ICInitStruct.TIM_ICFilter = 0x00;							
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;	
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;				
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM4, &TIM_ICInitStruct);
	
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
        //	/*清除计数器*/
	TIM_SetCounter(TIM4,0);
	msCount = 0;
	TIM_Cmd(TIM4,ENABLE);//使能定时器
}
 
void CloseTimer()        //关闭定时器
{
       //	/*关闭计数器使能*/
	TIM_Cmd(TIM4,DISABLE);
}

uint32_t  GetEchoTimer(void)
{
   uint32_t msCount;
	msCount += TIM_GetCounter(TIM4);//获取计TIM2数寄存器中的计数值，一边计算回响信号时间
	TIM4->CNT = 0;  //将TIM2计数寄存器的计数值清零
	Delay_ms(50);
	return msCount;
}

//void TIM4_IRQHandler(void)
//{
////	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
////	{
////		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
////		msCount++;
////	}

//}

void echocapture(void)
{	
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) == 0)//echo等待回响
		{/*开启定时器*/
		OpenTimer();
		nn=0;
		}
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) == 1);
		/*关闭定时器*/
}


void TIM4_IRQHandler(void)
{	
	if(TIM_GetITStatus(TIM4,TIM_IT_CC1)!=RESET)//发生捕获中断
	TIM_ClearITPendingBit(TIM4,TIM_IT_CC1);//先清除中断标志位
	if(nn==0) //第一次捕获上升沿
{ 
	TIM4_CH1_CAPTURE_VAL1=TIM_GetCapture1(TIM4);//记录下此时上升沿的CNT值
	nn=1;//第二次捕捉上升沿标志位
}
	else if(nn==1)//第二次捕获上升沿
{ 	
	TIM4_CH1_CAPTURE_VAL2=TIM4->CCR1;//记录下此时上升沿的CNT值
	 if(TIM4_CH1_CAPTURE_VAL1>TIM4_CH1_CAPTURE_VAL2)
	{		
	TIM4_CH1_CAPTURE_VAL=65535-TIM4_CH1_CAPTURE_VAL1+TIM4_CH1_CAPTURE_VAL;
	}
	else if(TIM4_CH1_CAPTURE_VAL1<TIM4_CH1_CAPTURE_VAL2)
	{
	TIM4_CH1_CAPTURE_VAL=TIM4_CH1_CAPTURE_VAL2-TIM4_CH1_CAPTURE_VAL1;
	}
	else{
		TIM4_CH1_CAPTURE_VAL=0;
	}
nn=0;//让nn等于0，准备新的捕获
}
}
