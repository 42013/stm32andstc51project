#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Serial.h"
#include "Key.h"

uint8_t KeyNum;

int main(void)
{
	Key_Init();
	Serial_Init();
	
//	Serial_TxPacket[0] = 0x01;
//	Serial_TxPacket[1] = 0x02;
//	Serial_TxPacket[2] = 0x03;
//	Serial_TxPacket[3] = 0x04;
	
	while (1)
	{
		//Serial_SendPacket();
		
		if (Serial_GetRxFlag() == 1)
		{
			Serial_SendByte(0x05);
		}
	}
}
