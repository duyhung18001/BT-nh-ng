#include "IP_IWDG.h"

void IP_IWDG_WriteConfig(uint8_t pr, uint16_t rlr) {
    IWDG->KR = 0x5555; 
    while ((IWDG->SR & 0x01) != 0); 
    IWDG->PR = pr;
    
    while ((IWDG->SR & 0x02) != 0); 
    IWDG->RLR = rlr;
}
void IP_IWDG_Refresh(void) { IWDG->KR = 0xAAAA; }
void IP_IWDG_Start(void)   { IWDG->KR = 0xCCCC; }

uint8_t IP_IWDG_GetResetStatus(void) { return (RCC->CSR & (1 << 29)) ? 1 : 0; }
void IP_IWDG_ClearResetFlag(void)    { RCC->CSR |= (1 << 24); }