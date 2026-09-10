#ifndef __MID_IWDG_H
#define __MID_IWDG_H
#include "IP_IWDG.h"

void Mid_IWDG_Init(uint32_t timeout_ms);
void Mid_IWDG_Kick(void);
uint8_t Mid_IWDG_CheckReset(void);
void Mid_IWDG_ClearFlags(void);

#endif