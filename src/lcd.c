#include "lcd.h"
#include "config.h"
#include <util/delay.h>

void lcd_init(void) {
    LCD_DATA_DDR |= 0x0F;
    LCD_RS_DDR |= (1 << LCD_RS);
    LCD_EN_DDR |= (1 << LCD_EN);

    _delay_ms(50);

    lcd_send_nibble(0x03);
    _delay_ms(5);
    lcd_send_nibble(0x03);
    _delay_us(150);
    lcd_send_nibble(0x03);
    lcd_send_nibble(0x02);

    lcd_command(LCD_CMD_4BIT_MODE);
    lcd_command(LCD_CMD_DISPLAY_ON);
    lcd_command(LCD_CMD_ENTRY_MODE);
    lcd_clear();
}

void lcd_send_nibble(uint8_t nibble) {
    LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (nibble & 0x0F);
    lcd_commit();
}

void lcd_command(uint8_t cmd) {
    LCD_RS_PORT &= ~(1 << LCD_RS);
    lcd_send_nibble(cmd >> 4);
    lcd_send_nibble(cmd);
    _delay_ms(2);
}

void lcd_data(uint8_t data) {
    LCD_RS_PORT |= 1 << LCD_RS;
    lcd_send_nibble(data >> 4);
    lcd_send_nibble(data);
    _delay_us(50);
}

void lcd_commit() {
    LCD_EN_PORT |= (1 << LCD_EN);
    _delay_us(50);

    LCD_EN_PORT &= ~(1 << LCD_EN);
    _delay_us(50);
}

void lcd_clear() {
    lcd_command(LCD_CMD_CLEAR);
    _delay_ms(20);
}

void lcd_display(char* str) {
    while (*str != '\0') {
        lcd_data(*str);
        str++;
    }
}

void lcd_gotoxy(uint8_t x, uint8_t y) {
    uint8_t addr = (y == 0) ? 0x80 : 0xC0;
    lcd_command(addr + x);
}
