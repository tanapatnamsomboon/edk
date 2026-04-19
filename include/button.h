#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

extern volatile uint8_t button_flag1;
extern volatile uint8_t button_flag2;

void    button_init(uint8_t count);
uint8_t button_pressed(uint8_t button);
uint8_t button_released(uint8_t button);

#endif
