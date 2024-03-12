#include "stm32f10x.h"                  // Device header
#include "lightfell.h"
#include "serial.h"

void Delay_us(uint32_t xus)
{
	SysTick->LOAD = 72 * xus;				//设置定时器重装值
	SysTick->VAL = 0x00;					//清空当前计数值
	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器
	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
	SysTick->CTRL = 0x00000004;				//关闭定时器
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
} 


int main(void)
{
	serial_Init();
	//serial_Sendbyte(0x67);
	while(1)
	{
		Serial_Printf("1");
		Delay_ms(200);
	}
}





//uint8_t RxData;
//char *str;
//uint8_t i=0;
//char re[100];
//serial_Sendstring("BBURUDBFUFFFRRFUUFLULUFUDLRRDBBDBDBLUDDFLLRRBRLLLBRDDF");
//		if(serial_GetRxFlag()==1)
//	{
//		RxData=serial_GetRxFlag();
//		RxData=USART_ReceiveData(USART1);           
//		serial_Sendbyte(RxData);
//	}
//	if(serial_GetRxFlag()==1)
//	{
//		RxData=serial_GetRxFlag();
//		RxData=USART_ReceiveData(USART1); 
//		serial_Sendbyte(RxData);
////		serial_Sendbyte(RxData);
////        re[i]= RxData;		
////		serial_Sendbyte(re[i]);
////		i++;
	//} 
