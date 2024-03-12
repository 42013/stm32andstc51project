#include "stm32f10x.h"                  // Device header
#include "timer.h"
#include "Delay.h"
#include "PWM.h"
#include "Motor.h"

void voice_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出 ,高低电平均有驱动能力，Out_OD开luo输出，高电平无驱动能力 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;//TRIG输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);//信号口制低电平
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;	//ECHO输入
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//下拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);

}

//uint32_t  GetEchoTimer(void)
//{
//   uint32_t msCount;
//	msCount += TIM_GetCounter(TIM2);//获取计TIM2数寄存器中的计数值，一边计算回响信号时间
//	TIM2->CNT = 0;  //将TIM2计数寄存器的计数值清零
//	Delay_ms(50);
//	return msCount;
//}

float getlength(void)
{
	uint32_t t=0;
	float length=0;
		GPIO_SetBits(GPIOB,GPIO_Pin_8);//trig拉高信号，发出高电平
		Delay_us(10);//持续时间超过10us
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);
		/*Echo发出信号 等待回响信号*/
		/*输入方波后，模块会自动发射8个40KHz的声波，与此同时回波引脚（echo）端的电平会由0变为1；
		（此时应该启动定时器计时）；当超声波返回被模块接收到时，回波引 脚端的电平会由1变为0；
		（此时应该停止定时器计数），定时器记下的这个时间即为
			超声波由发射到返回的总时长；*/
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) == 0);//echo等待回响
		/*开启定时器*/
		OpenTimer();
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) == 1);
		/*关闭定时器*/
		CloseTimer();
		t=GetEchoTimer();
		if(t==0){
		length=0;
		}else
		{
		length = t/58;
		}
		return length;
}

void lengthdown(void)
	{
	float len;
		len=getlength();
		if(len<25)
		{
		Stopward();
		}else{
		Forward();
		}
	}
