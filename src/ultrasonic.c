#include "ultrasonic.h"
#include "config.h"
#include <avr/io.h>
#include <util/delay.h>

void ultrasonic_init(void) {
    PIN_OUTPUT(UTRIG);
    PIN_INPUT(UECHO);

    PIN_LOW(UTRIG);

    TCCR1B |= (1 << CS11);
}

uint16_t ultrasonic_measure(void) {
    PIN_LOW(UTRIG);
    _delay_us(2);
    PIN_HIGH(UTRIG);
    _delay_us(10);
    PIN_LOW(UTRIG);

    uint32_t counter = 0;
    while (!PIN_READ(UECHO)) {
        counter++;
        if (counter > 50000) return 0;
    }

    TCNT1 = 0;

    counter = 0;
    while (PIN_READ(UECHO)) {
        counter++;
        if (counter > 50000) return 0;
        if (TCNT1 > 40000) break;
    }

    return TCNT1 / 116;
}
