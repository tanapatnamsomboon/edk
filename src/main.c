#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "led.h"
#include "keypad.h"
#include "timer.h"
#include "ultrasonic.h"

int main(void) {
    sei();
    keypad_init();
    ultrasonic_init();
    lcd_init();
    led_init(3);

    char buffer[16];
    uint16_t distance;

    lcd_clear();
    lcd_gotoxy(0, 0);
    lcd_display("Ultrasonic Test");
    timer_wait_ms(1000);
    lcd_clear();
    while (1) {
        cli();
        distance = ultrasonic_measure();
        sei();
        sprintf(buffer, "Dist: %3u cm", distance);

        lcd_gotoxy(0, 0);
        lcd_display(buffer);

        lcd_gotoxy(0, 1);
        if (distance < 10) {
            lcd_display("Stat: TOO CLOSE");
        } else if (distance > 100) {
            lcd_display("Stat: TOO FAR  ");
        } else {
            lcd_display("Stat: NORMAL   ");
        }

        timer_wait_ms(200);
    }

    return 0;
}
