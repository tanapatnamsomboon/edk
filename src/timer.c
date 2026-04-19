#include "timer.h"

volatile uint8_t  ms_timer_done  = 0;
volatile uint16_t overflow_count = 0;
volatile uint16_t target_overflows = 0;

ISR(TIMER1_OVF_vect) {
    overflow_count++;
    if (overflow_count >= target_overflows) {
        TCCR1B = 0;
        ms_timer_done = 1;
    }
}

void timer_delay_ms(uint16_t milliseconds) {
    ms_timer_done  = 0;
    overflow_count = 0;

    target_overflows = (milliseconds / 50) + 1;

    TCCR1A = 0;
    TCNT1  = 65536 - (milliseconds * 1000 / target_overflows);

    TIMSK1 |= (1 << TOIE1);
    TCCR1B |= (1 << CS11);
}

void timer_delay_us(uint16_t microseconds) {
    TCCR1B = 0;
    TCCR1A = 0;
    TCNT1  = 65536 - microseconds;

    TIFR1  |= (1 << TOV1);
    TIMSK1 |= (1 << TOIE1);
    TCCR1B |= (1 << CS11);
}

void timer_wait_ms(uint16_t milliseconds) {
    timer_delay_ms(milliseconds);
    while (!ms_timer_done);
    ms_timer_done = 0;
}

void timer_wait_us(uint16_t microseconds) {
    TCCR1B = 0;
    TCCR1A = 0;
    TCNT1  = 65536 - microseconds;

    TIFR1  |= (1 << TOV1);
    TCCR1B |= (1 << CS11);

    while (!(TIFR1 & (1 << TOV1)));
    TCCR1B = 0;
}
