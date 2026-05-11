#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h> 

#include "timer.h"
#include "i2c.h"
#include "sh1106.h"
#include "rtc.h"
#include "dht11.h"

int main(void) {
    sei(); 

    i2c_init();
    timer_wait_ms(100);
    sh1106_init();
    sh1106_clear();

    uint8_t sec, min, hour, date, month, year;
    uint8_t humidity = 0, temperature = 0;
    char buffer[25]; 
    uint8_t ticks = 0;

    rtc_set_time(0, 03, 19, 7, 5, 26); // Sets time to 18:57:00 on 07/05/2026

    sh1106_set_cursor(0, 0);
    sh1106_print_string("Environment Monitor");

    while (1) {
        // --- 1. Update RTC ---
        rtc_get_time(&sec, &min, &hour, &date, &month, &year);
        
        sh1106_set_cursor(0, 2);
        sprintf(buffer, "Date: %02d/%02d/20%02d", date, month, year);
        sh1106_print_string(buffer);
        
        sh1106_set_cursor(0, 4);
        sprintf(buffer, "Time: %02d:%02d:%02d", hour, min, sec);
        sh1106_print_string(buffer);

        // --- 2. Update DHT11 (Every 2 seconds) ---
        if (ticks % 2 == 0) {
            if (dht11_read(&humidity, &temperature)) {
                // Clear the line by overwriting it with spaces just in case
                sprintf(buffer, "Hum:%02d%% Temp:%02dC  ", humidity, temperature);
            } else {
                sprintf(buffer, "DHT11 Read Error   ");
            }
            sh1106_set_cursor(0, 6);
            sh1106_print_string(buffer);
        }

        ticks++;
        timer_wait_ms(1000); // Main loop runs once per second
    }

    return 0;
}