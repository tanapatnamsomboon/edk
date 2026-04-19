#include "timer.h"

volatile uint8_t  timer_done  = 0;
volatile uint16_t overflow_count = 0;
volatile uint16_t target_overflows = 0;

ISR(TIMER0_OVF_vect) {
    overflow_count++;
    if (overflow_count >= target_overflows) {
        TCCR0B = 0;
        timer_done = 1;
    }
}

void timer_delay_ms(uint16_t milliseconds) {
    timer_done  = 0;
    overflow_count = 0;

    target_overflows = ((uint32_t)milliseconds * 1000UL / 256) + 1;

    TCCR0A = 0;
    TCNT0  = 0;
    TIMSK0 |= (1 << TOIE0);
    TCCR0B = (1 << CS01);
}

void timer_delay_us(uint16_t microseconds) {
    timer_done     = 0;
    overflow_count = 0;

    target_overflows = (microseconds / 256) + 1;

    TCCR0A = 0;
    TCNT0  = 256 - (microseconds % 256);
    TIMSK0 |= (1 << TOIE0);
    TCCR0B = (1 << CS01);
}

void timer_wait_ms(uint16_t milliseconds) {
    timer_delay_ms(milliseconds);
    while (!timer_done);
    timer_done = 0;
}

void timer_wait_us(uint16_t microseconds) {
    TCCR0B = 0;
    TCCR0A = 0;
    TCNT0  = 256 - (microseconds & 0xFF);

    TIFR0  |= (1 << TOV0);
    TCCR0B  = (1 << CS01);

    while (!(TIFR0 & (1 << TOV0)));
    TCCR0B = 0;
}
