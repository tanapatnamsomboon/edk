#include <avr/io.h>
#include "led.h"
#include "button.h"
#include "timer.h"
#include <stdio.h>

int main(void) {
    sei();
    led_init(2);
    button_init(2);

    while (1) {
        if (button_flag1) {
            button_flag1 = 0;
            led_toggle(1);
        }
        if (button_flag2) {
            button_flag2 = 0;
            led_toggle(2);
        }
    }

    return 0;
}
