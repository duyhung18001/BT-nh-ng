#ifndef __APP_IWDG_H
#define __APP_IWDG_H
#include "Mid_IWDG.h"

void App_IWDG_InitBKP(void);
void App_IWDG_SaveTestID(uint16_t id);
uint16_t App_IWDG_ReadTestID(void);
void App_IWDG_CheckRecovery(void);
void App_IWDG_Execute(uint16_t id);

#endif