#include "stm32f10x.h"                  // Device header
#include "Delay.h"                      //延时库
#include "voice.h"                      //超声波引脚定义
#include "timer.h"                      //捕获时间
#include "oled.h"                       //oled显示屏库

float lenth; //初始距离
u32 number;  //滤波后并转整形

//               oled显示屏说明: 
//              ----------------------------------------------------------------
//              GND   电源地
//              VCC   3.3v电源
//              SCL   PA0端口
//              SDA   PA1端口
//               超声波说明: 
//              ----------------------------------------------------------------
//              GND   电源地
//              VCC   5v电源
//              ECHO  PB8端口
//              TRIG  PB9端口


int main(void)
{
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
    OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	Timer_Init();
	voice_Init();
	while(1)
	{	
	lenth=getlength(); //获取初始距离
	number=fileter(lenth);//滤波后并转整形
		
	/*显示*/	
	OLED_ShowString(10,20,"lenth:",16,1); 	 
	OLED_ShowNum(60,20,number,3,16,1); 
    OLED_ShowString(90,20,"cm",16,1); 		
	OLED_Refresh();//刷新	
	}
 }

