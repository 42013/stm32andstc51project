#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "lightfell.h"
#include "serial.h"
#include "PWM.h"
#include "Key.h"

float i;
uint8_t KeyNum;
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出 ,高低电平均有驱动能力，Out_OD开luo输出，高电平无驱动能力 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//GPIO_SetBits(GPIOA,GPIO_Pin_0);//信号口制高电平
	// GPIO_ResetBits(GPIOC,GPIO_Pin_13);//信号口制低电平
	//GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);//写入参数控制行为
}
int main(void)
{
	PWM_Init();
	Key_Init();
	LED_Init();
	while(1)
	{	
		PWM_SetCompare2(2000);
//		for(i=0;i<1500;i++){
//		//Delay_ms(200);	
//		PWM_SetCompare2(100+i);
//		}
	}
}
