#include "Mid_IWDG.h"
#include "App_UART.h"

void Mid_IWDG_Init(uint32_t timeout_ms) {
    uint16_t reload;
	if (timeout_ms > 26208) {
        timeout_ms = 26208;
        App_UART_Print("\r\n[MID WARN] Timeout 50s is too large! Clamped to 26.2s.");
    }
    if (timeout_ms < 10) {
        timeout_ms = 10;
        App_UART_Print("\r\n[MID WARN] Timeout < 10ms. Ep ve 10ms.");
    }
    if (timeout_ms > 26208) {
        timeout_ms = 26208; 
        App_UART_Print("\r\n[MID WARN] Timeout vuot nguong HW. Ep ve 26.2s.");
    }
    reload = (uint16_t)((timeout_ms * 156) / 1000);
    if(reload > 0xFFF) reload = 0xFFF;
    IP_IWDG_WriteConfig(6, reload);
    IP_IWDG_Refresh();
    IP_IWDG_Start();
}

void Mid_IWDG_Kick(void) { IP_IWDG_Refresh(); }
uint8_t Mid_IWDG_CheckReset(void) { return IP_IWDG_GetResetStatus(); }
void Mid_IWDG_ClearFlags(void) { IP_IWDG_ClearResetFlag(); }