#ifndef __MID_UART__H
#define __MID_UART__H

#include "IP_UART.h"
#include <stdint.h>

void Mid_UART_Init(uint32_t baudrate);
void Mid_UART_SendString(const char* str);

#endif