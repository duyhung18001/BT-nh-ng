#include "IP_UART.h"

void IP_UART_ClockEnable(void) {
    RCC->APB2ENR |= (1 << 0) | (1 << 2) | (1 << 14);
}

void IP_UART_GPIOConfig(void) {
    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |= (0xB << 4);
}

void IP_UART_SetBaudRate(uint32_t brr_val) {
    USART1->BRR = brr_val;
}

void IP_UART_Enable(void) {
    USART1->CR1 = 0;
    USART1->CR2 = 0;
    USART1->CR3 = 0;
    USART1->CR1 |= (1 << 13) | (1 << 3);
}

void IP_UART_WriteChar(char c) {
    while ((USART1->SR & (1 << 7)) == 0); 
    USART1->DR = (c & 0xFF);
}