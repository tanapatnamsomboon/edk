#ifndef LED_H
#define LED_H

#include <stdint.h>

void led_init(uint8_t count);

void led_on(uint8_t index);
void led_off(uint8_t index);
void led_toggle(uint8_t index);

#endif // LED_H
