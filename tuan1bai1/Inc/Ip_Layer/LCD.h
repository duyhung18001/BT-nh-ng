#ifndef __LCD_H   
#define __LCD_H   
#include "stm32f10x.h" 

#define LCD_ADDR 0x4E  
#define RS_BIT   0x01  
#define EN_BIT   0x04  
#define BL_BIT   0x08  
#define LCD_CLEAR 0x01 

void lcd_init(void);
void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_send_string(char *str);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_clear(void);

#endif 