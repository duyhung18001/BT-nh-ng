#include "LCD.h"
#include "i2c.h"

static void delay_ms(uint32_t ms) {
    uint32_t i; 

	for (i = 0; i < ms * 8000; i++) {
        __NOP();
    }
}

static void lcd_write_i2c(uint8_t data) {
    i2c_start(1);
    i2c_add(1, LCD_ADDR, 0); 
    i2c_data(1, data);       
    i2c_stop(1);
}

static void lcd_send_4bit(uint8_t val, uint8_t rs) {
    uint8_t high_nib = (val & 0xF0) | rs | BL_BIT;
    uint8_t low_nib  = ((val << 4) & 0xF0) | rs | BL_BIT;

    lcd_write_i2c(high_nib | EN_BIT); 
    delay_ms(1);
    lcd_write_i2c(high_nib);          
    
    lcd_write_i2c(low_nib | EN_BIT);  
    delay_ms(1);
    lcd_write_i2c(low_nib);           
}

void lcd_send_cmd(char cmd) {
    lcd_send_4bit(cmd, 0);
}

void lcd_send_data(char data) {
    lcd_send_4bit(data, RS_BIT);
}

void lcd_init(void) {
    delay_ms(50);
    lcd_write_i2c(0x30 | EN_BIT | BL_BIT);
    lcd_write_i2c(0x30 | BL_BIT);
    delay_ms(5);
    lcd_write_i2c(0x30 | EN_BIT | BL_BIT);
    lcd_write_i2c(0x30 | BL_BIT);
    delay_ms(1);
    lcd_write_i2c(0x20 | EN_BIT | BL_BIT);
    lcd_write_i2c(0x20 | BL_BIT);
    lcd_send_cmd(0x28); 
    lcd_send_cmd(0x0C); 
    lcd_send_cmd(0x06); 
    lcd_send_cmd(0x01); 
    delay_ms(2);
}

void lcd_send_string(char *str) {
    while (*str) lcd_send_data(*str++);
}

void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_send_cmd(addr);
}

void lcd_clear(void) {
    lcd_send_cmd(0x01); 
    delay_ms(2);
}
