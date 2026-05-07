#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "i2c.h"
#include "sh1106.h"

int main(void) {
    sei(); // Enable global interrupts

    // 1. Initialize interfaces
    i2c_init();

    // 2. Wait for OLED to stabilize on power-up
    timer_wait_ms(100);

    // 3. Initialize and clear the display
    sh1106_init();
    sh1106_clear();

    // 4. Print text
    sh1106_set_cursor(0, 2);
    sh1106_print_string("Hello, World!");
    
    sh1106_set_cursor(0, 4);
    sh1106_print_string("SH1106 is ready.");

    sh1106_set_cursor(0, 6);
    sh1106_print_string("It's really works on my board.");

    while (1) {
        // Main loop
    }

    return 0;
}