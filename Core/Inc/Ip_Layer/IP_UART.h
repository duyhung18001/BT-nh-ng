#ifndef __IP_UART__H
#define __IP_UART__H

#include "stm32f10x.h"

void IP_UART_ClockEnable(void);
void IP_UART_GPIOConfig(void);
void IP_UART_SetBaudRate(uint32_t brr_val);
void IP_UART_Enable(void);
void IP_UART_WriteChar(char c);

#endif