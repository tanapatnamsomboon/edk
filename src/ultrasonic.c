#include "ultrasonic.h"
#include "config.h"
#include <avr/io.h>
#include <util/delay.h>

void ultrasonic_init(void) {
    TCCR1B |= (1 << CS11);
    UTRIG_DDR |= (1 << UTRIG);
    UECHO_DDR &= ~(1 << UECHO);
    UTRIG_PORT &= ~(1 << UTRIG);
}

void ultrasonic_trigger(void) {
    UTRIG_PORT |= (1 << UTRIG);
    _delay_us(10);
    UTRIG_PORT &= ~(1 << UTRIG);
}

uint16_t ultrasonic_measure(void) {
    ultrasonic_trigger();
    while (!(UECHO_PIN & (1 << UECHO)));
    TCNT1 = 0;
    while (UECHO_PIN & (1 << UECHO));
    return TCNT1 / 58;
}
