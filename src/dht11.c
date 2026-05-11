#include "dht11.h"
#include "config.h"
#include <util/delay.h>

uint8_t dht11_read(uint8_t *humidity, uint8_t *temperature) {
    uint8_t bits[5] = {0};
    uint16_t timeout;
    
    // 1. Send start signal to DHT11
    PIN_OUTPUT(DHT_PIN);
    PIN_LOW(DHT_PIN);
    _delay_ms(20);     // MCU pulls low for >18ms
    PIN_HIGH(DHT_PIN);
    _delay_us(30);     // MCU pulls high for 20-40us
    
    PIN_INPUT(DHT_PIN); // Set pin to input to listen to DHT11
    
    // 2. Wait for DHT11 response (80us low, then 80us high)
    timeout = 0;
    while(PIN_READ(DHT_PIN))  { if (++timeout > 100) return 0; _delay_us(1); } 
    timeout = 0;
    while(!PIN_READ(DHT_PIN)) { if (++timeout > 100) return 0; _delay_us(1); } 
    timeout = 0;
    while(PIN_READ(DHT_PIN))  { if (++timeout > 100) return 0; _delay_us(1); } 
    
    // 3. Read the 40 data bits (5 bytes)
    for (uint8_t i = 0; i < 5; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            timeout = 0;
            // Wait for 50us low preamble
            while(!PIN_READ(DHT_PIN)) { if (++timeout > 100) return 0; _delay_us(1); } 
            
            // Wait 30us to check if the high pulse is a '0' (26-28us) or '1' (70us)
            _delay_us(30); 
            if (PIN_READ(DHT_PIN)) {
                bits[i] |= (1 << (7 - j)); // It's a '1'
                timeout = 0;
                // Wait for the rest of the high pulse to finish
                while(PIN_READ(DHT_PIN)) { if (++timeout > 100) return 0; _delay_us(1); } 
            }
        }
    }
    
    // 4. Verify checksum
    if ((uint8_t)(bits[0] + bits[1] + bits[2] + bits[3]) == bits[4]) {
        *humidity = bits[0];     // Integer part of humidity
        *temperature = bits[2];  // Integer part of temperature
        return 1;
    }
    
    return 0; // Checksum mismatch
}