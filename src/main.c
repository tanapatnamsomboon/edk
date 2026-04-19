#include <avr/io.h>
#include <stdio.h>
#include "timer.h"
#include "lcd.h"
#include "adc.h"
#include <math.h>

int main(void) {
    sei();
    adc_init();
    lcd_init();

    char buffer[16];

    uint16_t ldr_raw = 0;
    const float rfixed = 4700.0f;
    float vlux = 0.0f;
    float rldr = 0.0f;
    float luxf = 0.0f;
    uint16_t lux = 0;


    uint16_t tmp_raw = 0;
    float voltage = 0;
    uint16_t celsius = 0;

    lcd_clear();

    while (1) {
        ldr_raw = adc_read(0);
        vlux =  (float)ldr_raw * 5000.0f / 1024.0f;
        rldr = rfixed * (5000.0f -vlux) / vlux;
        luxf = powf(75150.0f / rldr, 1.0f / 0.7f);
        lux = (uint16_t)(luxf + 0.5f);

        lcd_gotoxy(0, 0);
        sprintf(buffer, "LDR: %5uLux", lux);
        lcd_display(buffer);

        tmp_raw = adc_read(1);
        voltage = (tmp_raw * 5000.0f) / 1024.0f;
        celsius = voltage / 10.0f;

        lcd_gotoxy(0, 1);
        sprintf(buffer, "TMP: %5uC", celsius);
        lcd_display(buffer);

        timer_wait_ms(500);
    }

    return 0;
}
