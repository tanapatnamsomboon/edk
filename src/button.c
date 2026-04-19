#include "button.h"
#include "config.h"
#include "timer.h"
#include <avr/interrupt.h>

volatile uint8_t button_flag1 = 0;
volatile uint8_t button_flag2 = 0;

void button_init(uint8_t count) {
    if (count >= 1) {
        PIN_INPUT(BTN1);
        PIN_HIGH(BTN1);

        EICRA |= (1 << ISC01);
        EIMSK |= (1 << INT0);
    }

    if (count >= 2) {
        PIN_INPUT(BTN2);
        PIN_HIGH(BTN2);

        EICRA |= (1 << ISC11);
        EIMSK |= (1 << INT1);
    }
}

uint8_t button_pressed(uint8_t button) {
    switch (button) {
        case 1:
            return !PIN_READ(BTN1);
        case 2:
            return !PIN_READ(BTN2);
        default:
            return 0;
    }

}

uint8_t button_released(uint8_t button) {
    switch (button) {
        case 1:
            return PIN_READ(BTN1);
        case 2:
            return PIN_READ(BTN2);
        default:
            return 1;
    }
}

ISR(INT0_vect) {
    button_flag1 = 1;
}

ISR(INT1_vect) {
    button_flag2 = 1;
}
