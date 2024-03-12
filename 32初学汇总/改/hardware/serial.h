#ifndef __SERIAL_H
#define __SERIAL_H

#include "stdio.h"

void serial_Init(void);
void serial_Sendbyte(uint8_t Byte);
void serial_Sendarray(uint8_t *array,uint16_t lengh);
void serial_Sendstring(char *string);
void serial_Sendnumber(uint32_t number,uint16_t lengh);
void Serial_Printf(char *format, ...);
uint8_t serial_GetRxFlag(void);
uint8_t serial_GetRxData(void);

#endif
