#include "PWM.h"
#include "stm32f10x.h"
#include "sys.h"


 int main()
 {
  
   TIM3_PWM_Init();
	Motor1_Init();
	Motor2_Init(); 
	 while(1)
	 {
		
	 //if(L==0&&R==0)
     Forward();
	 
//	 if(L==1&&R==0)
//	 Leftward();
//	 
//	 if(L==0&&R==1)
//	 Rightward();
//	 
//	 if(L==1&&M==1&&R==1)
//	 Stopward();	 
	 
	 }
	 
	
 }


 


