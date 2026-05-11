#ifndef SH1106_H
#define SH1106_H

#include <stdint.h>

// I2C Address for SH1106 (0x3C shifted left by 1)
#define SH1106_I2C_ADDR 0x78

// SH1106 panels are physically 128px wide but have 132px of RAM. 
// We offset by 2 columns to center the image on the screen.
#define SH1106_OFFSET 2

void sh1106_init(void);
void sh1106_command(uint8_t cmd);
void sh1106_data(uint8_t data);
void sh1106_clear(void);
void sh1106_set_cursor(uint8_t x, uint8_t page);
void sh1106_print_char(char c);
void sh1106_print_string(const char *str);

#endif // SH1106_H