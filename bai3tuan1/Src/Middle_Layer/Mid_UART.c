#include "Mid_UART.h"
extern uint32_t SystemCoreClock; 

void Mid_UART_Init(uint32_t baudrate) {
    uint32_t brr_val = SystemCoreClock / baudrate;

    IP_UART_ClockEnable();
    IP_UART_GPIOConfig();
    IP_UART_SetBaudRate(brr_val);
    IP_UART_Enable();
}

void Mid_UART_SendString(const char* str) {
    while (*str) {
        IP_UART_WriteChar(*str++);
    }
}