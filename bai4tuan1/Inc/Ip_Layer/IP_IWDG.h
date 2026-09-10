#ifndef __IP_IWDG_H
#define __IP_IWDG_H
#include "stm32f10x.h"

void IP_IWDG_WriteConfig(uint8_t pr, uint16_t rlr);
void IP_IWDG_Refresh(void);
void IP_IWDG_Start(void);
uint8_t IP_IWDG_GetResetStatus(void);
void IP_IWDG_ClearResetFlag(void);

#endif