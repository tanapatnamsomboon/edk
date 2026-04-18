#ifndef LCD_H
#define LCD_H

#include <stdint.h>

void lcd_init(void);
void lcd_send_nibble(uint8_t nibble);
void lcd_command(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_commit(void);
void lcd_clear(void);
void lcd_display(char* str);
void lcd_gotoxy(uint8_t x, uint8_t y);

#endif // LCD_H
