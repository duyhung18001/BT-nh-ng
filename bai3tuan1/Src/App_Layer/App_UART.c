#include "App_UART.h"
#include "IP_SysTick.h"
void App_UART_Config(uint32_t baudrate) {
    Mid_UART_Init(baudrate);
}

void App_UART_Print(const char* str) {
    Mid_UART_SendString(str);
}
void App_UART_WaitAndReset(void) {
    while (!(USART1->SR & (1 << 6))); 
    Delay_ms(10); 
    NVIC_SystemReset();
}