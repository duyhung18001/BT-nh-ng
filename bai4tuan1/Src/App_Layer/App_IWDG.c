#include "App_IWDG.h"
#include "App_UART.h"
#include "IP_SysTick.h"
#include "LCD.h"

void App_IWDG_InitBKP(void) {
    RCC->APB1ENR |= (1 << 28) | (1 << 27); 
    PWR->CR |= (1 << 8);                   
}
void App_IWDG_SaveTestID(uint16_t id) { BKP->DR1 = id; }
uint16_t App_IWDG_ReadTestID(void)    { return BKP->DR1; }

void App_IWDG_CheckRecovery(void) {
    if (Mid_IWDG_CheckReset()) {
        Mid_IWDG_ClearFlags();
        App_UART_Print("[REPORT] >>> WATCHDOG RESET SUCCESSFUL! <<<");
        App_UART_Print("[REPORT] System recovered from Test 3 hanging state.");
        lcd_clear();
        lcd_set_cursor(0, 0); lcd_send_string("IWDG RESET OK!  ");
        lcd_set_cursor(1, 0); lcd_send_string("BACK TO TEST 1  ");
        App_IWDG_SaveTestID(1); 
        Delay_ms(3000); 
    }
}

void App_IWDG_Execute(uint16_t id) {
    uint8_t count;
    lcd_clear(); 
    if (id == 1) {
        App_UART_Print("TEST 1:");
        lcd_set_cursor(0, 0); 
        lcd_send_string("T1: normal");
        Mid_IWDG_Init(2000); 
        for(count = 1; count <= 5; count++) {
            lcd_set_cursor(1, 0); 
            lcd_send_string("count: ");
            lcd_send_data(count + '0');
            Mid_IWDG_Kick(); 
            Delay_ms(1000);
        }
        App_IWDG_SaveTestID(2);
        App_UART_Print("[DONE] Test 1 OK. Moving to Test 2...");
		App_UART_WaitAndReset();
        NVIC_SystemReset();
    } 
    else if (id == 2) {
        App_UART_Print("[START] TEST 2: Boundary (Input 50s).");
        lcd_set_cursor(0, 0); 
        lcd_send_string("T2: ");
        Mid_IWDG_Init(50000); 
        for(count = 1; count <= 36; count++) {
            lcd_set_cursor(1, 0);
			lcd_send_string("count: ");
            lcd_send_data(count + '0');
            Mid_IWDG_Kick(); 
            Delay_ms(1000);
        }
        App_IWDG_SaveTestID(3);
        App_UART_Print("Test 2 OK. Moving to Test 3...");
		App_UART_WaitAndReset();
        NVIC_SystemReset();
    }
    else if (id == 3) {
        App_UART_Print("[START] TEST 3: Hanging (No Feed).");
        lcd_set_cursor(0, 0); 
		lcd_send_string("T3: ");
        Mid_IWDG_Init(3000); 
        for(count = 1; count <= 10; count++) {
            lcd_set_cursor(1, 0); 
            lcd_send_string("count: ");
            lcd_send_data(count + '0');
            Delay_ms(1000);
        }
        lcd_set_cursor(1, 0); 
        lcd_send_string(" SYSTEM HALTED! ");
        App_UART_Print("[CRASH] Software stopped feeding. Waiting for Hardware Reset...");
    }
}