#include "stm32f10x.h"
#include "xunji.h"  
#include "sys.h"
#include "Delay.h"

//电机驱动
void motor1_gpio()
{
//B10、B11、B12、B13
  GPIO_InitTypeDef  GPIO_InitStructure;
	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13; 		
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	  //推挽输出 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
  GPIO_Init(GPIOB, &GPIO_InitStructure);     
  GPIO_ResetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13);
}

void motor2_gpio()
{
//A2 A3 A4 A5
  GPIO_InitTypeDef  GPIO_InitStructure;
	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5; 		
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	  //推挽输出 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
  GPIO_Init(GPIOA, &GPIO_InitStructure);      
  GPIO_ResetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);
}
//红外传感器
void xunji_gpio()
{
//C11、C12、C13、C14
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2; //定义红外引脚
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);


}

//电机调速
void pwm()
{
	//B0、B1   TIM3
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	  //使能定时器3时钟 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //使能GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能GPIOA时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用输出 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用输出 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	  
	TIM_TimeBaseStructure.TIM_Period =199;    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =35;     //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //TIM向上计数模式 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);    
	//控制电机
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    //输出极性:TIM输出比较极性高
 	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);   //使能TIM3在CCR1上的预装载寄存器
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);   //使能TIM3在CCR2上的预装载寄存器
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);   //使能TIM3在CCR3上的预装载寄存器
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);   //使能TIM3在CCR4上的预装载寄存器

	
	TIM_Cmd(TIM3, ENABLE);   //使能TIM3
}
void run()
{
		TIM_SetCompare1(TIM3,145);
   		TIM_SetCompare2(TIM3,140);
		TIM_SetCompare3(TIM3,140);
   		TIM_SetCompare4(TIM3,145);
		AIN1 =1;
		AIN2 =0; 
		AIN3 =1;
		AIN4 =0;
		BIN1 =1;
		BIN2 =0;
		BIN3 =1;
		BIN4 =0;
}
void back()
{		
		TIM_SetCompare1(TIM3,145);
   		TIM_SetCompare2(TIM3,140);
		TIM_SetCompare3(TIM3,140);
   		TIM_SetCompare4(TIM3,145);
		AIN1 =0;
		AIN2 =1;
		AIN3 =0;
		AIN4 =1;
		BIN1 =0;
		BIN2 =1;
		BIN3 =0;
		BIN4 =1;
}

void Rightward(void)
{
	
		TIM_SetCompare1(TIM3,135);	
		TIM_SetCompare2(TIM3,130);	 
	    TIM_SetCompare3(TIM3,130);	
	    TIM_SetCompare4(TIM3,135);
		 
		 AIN1 =0;
		AIN2 =1;    
		AIN3 =1;
		AIN4 =0;
		BIN1 =0;
		BIN2 =1;    
		BIN3 =1;
		BIN4 =0;

}
void Leftward(void)
{		
      TIM_SetCompare1(TIM3,135);	
	  TIM_SetCompare2(TIM3,130);	 
	  TIM_SetCompare3(TIM3,130);	
	  TIM_SetCompare4(TIM3,135);
	
		AIN1 =1;
		AIN2 =0;
		AIN3 =0;
		AIN4 =1;
		BIN1 =1;
		BIN2 =0;
		BIN3 =0;
		BIN4 =1;
}

void MOVER(void)
{		
      TIM_SetCompare1(TIM3,155);	
	  TIM_SetCompare2(TIM3,150);	 
	  TIM_SetCompare3(TIM3,150);	
	  TIM_SetCompare4(TIM3,155);
	  AIN1 =0;
      AIN2 =1;    
	  AIN3 =1;
	  AIN4 =0;
	  BIN1 =1;
      BIN2 =0;    
	  BIN3 =0;
	  BIN4 =1;
}

void MOVEL(void)
{		
      TIM_SetCompare1(TIM3,155);	
	  TIM_SetCompare2(TIM3,150);	 
	  TIM_SetCompare3(TIM3,150);	
	  TIM_SetCompare4(TIM3,155);
	  AIN1 =1;
      AIN2 =0;    
	  AIN3 =0;
	  AIN4 =1;
	  BIN1 =0;
      BIN2 =1;    
	  BIN3 =1;
	  BIN4 =0;
}	

void stop()
{
		AIN1 =0;
		AIN2 =0;
		AIN3 =0;
		AIN4 =0;
		BIN1 =0;
		BIN2 =0;
		BIN3 =0;
		BIN4 =0;
}

void voicerun()
{
		TIM_SetCompare1(TIM3,125);
   		TIM_SetCompare2(TIM3,120);
		TIM_SetCompare3(TIM3,120);
   		TIM_SetCompare4(TIM3,125);
		AIN1 =1;
		AIN2 =0; 
		AIN3 =1;
		AIN4 =0;
		BIN1 =1;
		BIN2 =0;
		BIN3 =1;
		BIN4 =0;
}

void tracingMode(void)
{
	//注：实际L与R反jie

	if(L==0&&R==0){	
     run();
	}
	 if(L==1&&R==0){
//		 if(a==0){
//		 MOVEL(); 
//		Delay_ms(1500);	 
//		 }else
		 {
		//run();
		//Delay_ms(20);		
		 Leftward();
	 //Delay_ms(45);
		 }
	 }
	 if(L==0&&R==1){
		//run();
		//Delay_ms(20);	 
	 Rightward();
		//Delay_ms(45); 
	 }
	 if(L==1&&R==1){
	 run();	 
	 }
 } 

 void tracingMode0()    
{	
	if(L==1&&M==1&&R==1)//ȫۚ
	{
		run();
	}
	if(L==0&&M==1&&R==0)//ֱП
	{      
		run();
	}
	if(L==1&&M==0&&R==0)//ճԒת
	{
		Leftward();
			if(L==0&&M==1&&R==0)
			{
			run();
			}
	}
	if(L==0&&M==0&&R==1)//ճسת
	{
			Rightward();
			if(L==0&&M==1&&R==0)
			{
				run();
			}
	} 
	if(L==1&&M==1&&R==0)
	{
			Leftward();
		if(L==0&&M==1&&R==0)
		{
		run();
		}
	}
	if(L==0&&M==1&&R==1)
	{
		Rightward(); 

		if(L==0&&M==0&&R==0)
		{
			run();
		}
	}
}
