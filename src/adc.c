#include "adc.h"
#include "config.h"

void adc_init(void) {
    ADMUX = ADC_REF_AVCC;
    ADCSRA = (1 << ADEN) | ADC_PRESCALER_128;
}

uint16_t adc_read(uint8_t channel) {
    channel &= 0b00000111;

    ADMUX = (ADMUX & 0xF8) | channel;

    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC));

    return (ADC);
}
