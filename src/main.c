#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "keypad.h"
#include "timer.h"
// #include "ultrasonic.h"

int main(void) {
    sei();
    keypad_init();
    lcd_init();

    char prev = '\0';
    int count = 0;
    char buffer[20];
    while (1) {
        // char key = keypad_scan();
        // if (key != prev) {
        //     prev = key;
        //     if (key != '\0') {
        //         lcd_clear();
        //         lcd_data(key);
        //     }
        // }

        lcd_clear();
        sprintf(buffer, "%d", count);
        lcd_display(buffer);
        count++;

        timer_wait_ms(500);

        // lcd_clear();
        // lcd_display("Hello, World!");
        // _delay_ms(500);
    }

    return 0;
}
