#include "stm32f10x.h"                  // Device header
#include "Delay.h"                      //��ʱ��
#include "voice.h"                      //���������Ŷ���
#include "timer.h"                      //����ʱ��
#include "oled.h"                       //oled��ʾ����

float lenth; //��ʼ����
u32 number;  //�˲���ת����

//               oled��ʾ��˵��: 
//              ----------------------------------------------------------------
//              GND   ��Դ��
//              VCC   3.3v��Դ
//              SCL   PA0�˿�
//              SDA   PA1�˿�
//               ������˵��: 
//              ----------------------------------------------------------------
//              GND   ��Դ��
//              VCC   5v��Դ
//              ECHO  PB8�˿�
//              TRIG  PB9�˿�


int main(void)
{
	OLED_Init();
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
    OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
	Timer_Init();
	voice_Init();
	while(1)
	{	
	lenth=getlength(); //��ȡ��ʼ����
	number=fileter(lenth);//�˲���ת����
		
	/*��ʾ*/	
	OLED_ShowString(10,20,"lenth:",16,1); 	 
	OLED_ShowNum(60,20,number,3,16,1); 
    OLED_ShowString(90,20,"cm",16,1); 		
	OLED_Refresh();//ˢ��	
	}
 }

