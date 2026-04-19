#include "led.h"
#include "config.h"

void led_init(uint8_t count) {
    if (count >= 1) { PIN_OUTPUT(LED1); PIN_LOW(LED1); }
    if (count >= 2) { PIN_OUTPUT(LED2); PIN_LOW(LED2); }
    if (count >= 3) { PIN_OUTPUT(LED3); PIN_LOW(LED3); }
}

void led_on(uint8_t index) {
    switch (index) {
        case 1: PIN_HIGH(LED1); break;
        case 2: PIN_HIGH(LED2); break;
        case 3: PIN_HIGH(LED3); break;
    }
}

void led_off(uint8_t index) {
    switch (index) {
        case 1: PIN_LOW(LED1); break;
        case 2: PIN_LOW(LED2); break;
        case 3: PIN_LOW(LED3); break;
    }
}

void led_toggle(uint8_t index) {
    switch (index) {
        case 1: if (PIN_READ(LED1)) PIN_LOW(LED1); else PIN_HIGH(LED1); break;
        case 2: if (PIN_READ(LED2)) PIN_LOW(LED2); else PIN_HIGH(LED2); break;
        case 3: if (PIN_READ(LED3)) PIN_LOW(LED3); else PIN_HIGH(LED3); break;
    }
}
