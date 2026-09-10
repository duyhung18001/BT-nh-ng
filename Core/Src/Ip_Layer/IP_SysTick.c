#include "IP_SysTick.h"
static uint32_t ticks_per_ms = 8000; 

void IP_SysTick_Init(uint32_t system_clock_hz) {
    ticks_per_ms = system_clock_hz / 1000;
}

void Delay_ms(uint32_t ms) {
    uint32_t i; 
    
    SysTick->LOAD = ticks_per_ms - 1; 
    SysTick->VAL = 0;          
    SysTick->CTRL = 5;        
    
    for (i = 0; i < ms; i++) {
        while ((SysTick->CTRL & (1 << 16)) == 0); 
    }
    
    SysTick->CTRL = 0;         
}
