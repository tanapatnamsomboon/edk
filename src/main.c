#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "lcd.h"
#include "rtc.h"
#include "i2c.h"

int main(void) {
    lcd_init();
    i2c_init();

    uint8_t sec, min, hour, date, month, year;
    char date_buffer[20];
    char time_buffer[20];

    rtc_set_time(0, 10, 15, 18, 4, 26);

    while (1) {
        rtc_get_time(&sec, &min, &hour, &date, &month, &year);

        sprintf(date_buffer, "Date: %02d/%02d/20%02d", date, month, year);
        sprintf(time_buffer, "Time: %02d:%02d:%02d", hour, min, sec);

        lcd_clear();
        lcd_gotoxy(0, 0);
        lcd_display(date_buffer);
        lcd_gotoxy(0, 1);
        lcd_display(time_buffer);

        // lcd_clear();
        // lcd_display("Hello, World!");
        _delay_ms(500);
    }

    return 0;
}
