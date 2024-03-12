#include "stm32f10x.h"                  // Device header
#include "lightfell.h"
void lightfell_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输出；推挽输出 ,高低电平均有驱动能力，Out_OD开luo输出，高电平无驱动能力 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//GPIO_SetBits(GPIOA,GPIO_Pin_0);//信号口制高电平
	// GPIO_ResetBits(GPIOC,GPIO_Pin_13);//信号口制低电平
	//GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);//写入参数控制行为
}

uint8_t lightfell_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
}
