#ifndef __IP_SYSTICK_H
#define __IP_SYSTICK_H

#include "stm32f10x.h"

void IP_SysTick_Init(uint32_t system_clock_hz);
void Delay_ms(uint32_t ms);

#endif