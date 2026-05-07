#ifndef DHT11_H
#define DHT11_H

#include <stdint.h>

// Returns 1 if successful, 0 if error/timeout
uint8_t dht11_read(uint8_t *humidity, uint8_t *temperature);

#endif // DHT11_H