#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "sys.h"
#include "Motor.h"

void Motor1_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5|GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//GPIO_ResetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_2|GPIO_Pin_3);
	TIM3_PWM_Init();
}

void Motor2_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12|GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//GPIO_ResetBits(GPIOA,GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_9|GPIO_Pin_10);
	TIM3_PWM_Init();
}

void motorgo(void)
{
	IN1=1;
	IN2=1;
	IN3=1;
	IN4=1;
}

void Forward(void)
{
		motorgo();
		AIN1 =1;
		AIN2 =0;
		AIN3 =1;
		AIN4 =0;
		BIN1 =1;
		BIN2 =0;
		BIN3 =1;
		BIN4 =0;
}


void Down(void)
{
		motorgo();
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
		//motorgo();
		TIM_SetCompare1(TIM1,500);	
		TIM_SetCompare2(TIM1,500);	 
	    TIM_SetCompare3(TIM1,2000);	
	    TIM_SetCompare4(TIM1,2000);
		AIN1 =1;
		AIN2 =0;
		AIN3 =0;
		AIN4 =1;
		BIN1 =1;
		BIN2 =0;
		BIN3 =0;
		BIN4 =1;

}


 
void Leftward(void)
{		//motorgo();
      TIM_SetCompare1(TIM1,100);	
	  TIM_SetCompare2(TIM1,100);	 
	  TIM_SetCompare3(TIM1,50);	
	  TIM_SetCompare4(TIM1,50);
	  AIN1 =0;
      AIN2 =1;    
	  AIN3 =1;
	  AIN4 =0;
	  BIN1 =0;
      BIN2 =1;    
	  BIN3 =1;
	  BIN4 =0;
}	

void MOVE1(void)
{		//motorgo();
      TIM_SetCompare1(TIM1,100);	
	  TIM_SetCompare2(TIM1,100);	 
	  TIM_SetCompare3(TIM1,50);	
	  TIM_SetCompare4(TIM1,50);
	  AIN1 =0;
      AIN2 =1;    
	  AIN3 =1;
	  AIN4 =0;
	  BIN1 =1;
      BIN2 =0;    
	  BIN3 =0;
	  BIN4 =1;
}

void MOVE2(void)
{		//motorgo();
      TIM_SetCompare1(TIM1,100);	
	  TIM_SetCompare2(TIM1,100);	 
	  TIM_SetCompare3(TIM1,50);	
	  TIM_SetCompare4(TIM1,50);
	  AIN1 =1;
      AIN2 =0;    
	  AIN3 =0;
	  AIN4 =1;
	  BIN1 =0;
      BIN2 =1;    
	  BIN3 =1;
	  BIN4 =0;
}	
void Stopward(void)
{
		//motorgo();
		AIN1 =0;
		AIN2 =0;
		AIN3 =0;
		AIN4 =0;
		BIN1 =0;
		BIN2 =0;
		BIN3 =0;
		BIN4 =0;
}
void tracingMode(void)
{
	if(L==0&&R==0)	
     Forward();
	
	 if(L==1&&R==0)
	 Leftward();
	 
	 if(L==0&&R==1)
	 Rightward();
	 
	 if(L==1&&M==1&&R==1)
	 Forward();	 
	 }
