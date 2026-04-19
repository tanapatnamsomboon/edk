#include "lcd.h"
#include "config.h"
#include <util/delay.h>

void lcd_init(void) {
    PIN_OUTPUT(LCD_RS);
    PIN_OUTPUT(LCD_EN);
    PIN_OUTPUT(LCD_D4);
    PIN_OUTPUT(LCD_D5);
    PIN_OUTPUT(LCD_D6);
    PIN_OUTPUT(LCD_D7);

    _delay_ms(50);

    lcd_send_nibble(0x03); _delay_ms(5);
    lcd_send_nibble(0x03); _delay_ms(5);
    lcd_send_nibble(0x03); _delay_ms(5);
    lcd_send_nibble(0x02); _delay_ms(5);


    lcd_command(LCD_CMD_4BIT_MODE);
    lcd_command(LCD_CMD_DISPLAY_ON);
    lcd_command(LCD_CMD_ENTRY_MODE);
    lcd_clear();
}

void lcd_send_nibble(uint8_t nibble) {
    if (nibble & 0x01) PIN_HIGH(LCD_D4); else PIN_LOW(LCD_D4);
    if (nibble & 0x02) PIN_HIGH(LCD_D5); else PIN_LOW(LCD_D5);
    if (nibble & 0x04) PIN_HIGH(LCD_D6); else PIN_LOW(LCD_D6);
    if (nibble & 0x08) PIN_HIGH(LCD_D7); else PIN_LOW(LCD_D7);
    lcd_commit();
}

void lcd_command(uint8_t cmd) {
    PIN_LOW(LCD_RS);
    lcd_send_nibble(cmd >> 4);
    lcd_send_nibble(cmd);
    _delay_ms(2);
}

void lcd_data(uint8_t data) {
    PIN_HIGH(LCD_RS);
    lcd_send_nibble(data >> 4);
    lcd_send_nibble(data);
    _delay_us(50);
}

void lcd_commit() {
    PIN_HIGH(LCD_EN);
    _delay_us(50);

    PIN_LOW(LCD_EN);
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
