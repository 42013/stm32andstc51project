#ifndef __AD_H
#define __AD_H

#define Adc3IN11SHUIWEI_READ_TIMES	10


void AD_Init(void);
uint16_t AD_GetValue(uint8_t ADC_Channel);	
float ShuiWeiSensor_Get_Val(void);

#endif
