#ifndef __APP_UART__H
#define __APP_UART__H

#include "Mid_UART.h"

void App_UART_Config(uint32_t baudrate);
void App_UART_Print(const char* str);
void App_UART_WaitAndReset(void);
#endif