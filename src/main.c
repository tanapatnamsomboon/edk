#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "ultrasonic.h"

int main(void) {
    lcd_init();
    ultrasonic_init();

    char buffer[16];

    while (1) {
        uint16_t dist = ultrasonic_measure();
        lcd_clear();
        itoa(dist, buffer, 10);
        lcd_display(buffer);
        _delay_ms(500);
    }

    return 0;
}
