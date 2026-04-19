#include "ultrasonic.h"
#include "config.h"
#include "timer.h"
#include <avr/io.h>

void ultrasonic_init(void) {
    PIN_OUTPUT(UTRIG);
    PIN_INPUT(UECHO);
    PIN_LOW(UTRIG);
}

uint16_t ultrasonic_measure(void) {
    PIN_LOW(UTRIG);
    timer_wait_us(2);
    PIN_HIGH(UTRIG);
    timer_wait_us(10);
    PIN_LOW(UTRIG);

    uint32_t timeout = 0;
    while (!PIN_READ(UECHO)) {
        timer_wait_us(1);
        timeout++;
        if (timeout > 30000) return 0;
    }

    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
    TCNT1 = 0;
    TCCR1B = (1 << CS11);

    timeout = 0;
    while (PIN_READ(UECHO)) {
        timeout++;
        if (timeout > 50000) return 0;
        if (TCNT1 > 40000) break;
    }

    TCCR1B = 0;
    return TCNT1 / 58;
}
