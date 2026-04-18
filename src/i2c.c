#include "i2c.h"
#include "config.h"

void i2c_init(void) {
    TWSR &= ~(1 << TWPS0) & ~(1 << TWPS1);
    TWBR = 0x48;
    TWCR |= (1 << TWEN);
}

uint8_t i2c_start(void) {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    uint16_t timeout = I2C_TIMEOUT;
    while (!(TWCR & (1 << TWINT))) {
        if (--timeout == 0) return 0;
    }
    return 1;
}

void i2c_stop(void) {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

uint8_t i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    uint16_t timeout = I2C_TIMEOUT;
    while (!(TWCR & (1 << TWINT))) {
        if (--timeout == 0) return 0;
    }
    return 1;
}

uint8_t i2c_read_ack(void) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    uint16_t timeout = I2C_TIMEOUT;
    while (!(TWCR & (1 << TWINT))) {
        if (--timeout == 0) return 0;
    }
    return TWDR;
}

uint8_t i2c_read_nack(void) {
    TWCR = (1 << TWINT) | (1 << TWEN);
    uint16_t timeout = I2C_TIMEOUT;
    while (!(TWCR & (1 << TWINT))) {
        if (--timeout == 0) return 0;
    }
    return TWDR;
}
