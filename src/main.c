#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "led.h"
#include "keypad.h"
#include "timer.h"
// #include "ultrasonic.h"

int main(void) {
    sei();
    keypad_init();
    lcd_init();
    led_init(3);

    int index = 0;
    int wait = 1000;
    char key = '\0';
    timer_delay_ms(wait);
    while (1) {
        key = keypad_scan();
        if (key == '1') {
            wait = 1000;
        } else if (key == '2') {
            wait = 500;
        } else if (key == '3') {
            wait = 100;
        }

        if (timer_done) {
            led_off(1);
            led_off(2);
            led_off(3);

            led_on(index);

            index++;
            if (index > 3) {
                index = 1;
            }

            timer_done = 0;
            timer_delay_ms(wait);
        }
    }

    return 0;
}
