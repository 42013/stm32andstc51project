#include "stm32f10x.h"                  // Device header
#include "ADC.h"



void IR_GPIO_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef  GPIO_InitStructure;
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void IR_ADC_Init(void)
{
	ADC_InitTypeDef   ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);

	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET);

}

uint16_t IR_Read(void)
{
    uint16_t ADCVal;

    TIM_SetCounter(TIM2, 0);
    while (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
    TIM_Cmd(TIM2, ENABLE);

    while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));

    TIM_Cmd(TIM2, DISABLE);

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));

    ADCVal = ADC_GetConversionValue(ADC1);

    return (uint16_t) (ADCVal * 3.3/4095 * 100); // ????(????)
}
