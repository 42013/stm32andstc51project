#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "serial.h"
#include "AD.h"



int main(void)
{
	u8 adcx;
	float shuiwei=0;
	serial_Init();
    AD_Init();
      while(1) 
   {
		adcx=AD_GetValue(ADC_Channel_0);
		shuiwei=ShuiWeiSensor_Get_Val();
		shuiwei=shuiwei*2;
		Serial_Printf("ADC: %d \r\n",adcx);
		Serial_Printf("Distance: %f cm\r\n",shuiwei);  
		//serial_Sendnumber(rad,6);
	   //IR_Read();
   }
}
