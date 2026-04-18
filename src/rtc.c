#include "rtc.h"
#include "i2c.h"
#include "config.h"

uint8_t bcd_to_dec(uint8_t val) {
    return ((val / 16 * 10) + (val % 16));
}

uint8_t dec_to_bcd(uint8_t val) {
    return ((val / 10 * 16) + (val % 10));
}

void rtc_get_time(uint8_t* sec, uint8_t* min, uint8_t* hour, uint8_t* date, uint8_t* month, uint8_t* year) {
    i2c_start();
    i2c_write(DS1307_ADDR);
    i2c_write(0x00);

    i2c_start();
    i2c_write(DS1307_ADDR | 1);

    *sec   = bcd_to_dec(i2c_read_ack() & 0x7F);
    *min   = bcd_to_dec(i2c_read_ack());
    *hour  = bcd_to_dec(i2c_read_ack() & 0x3F);
    i2c_read_ack();
    *date  = bcd_to_dec(i2c_read_ack());
    *month = bcd_to_dec(i2c_read_ack());
    *year  = bcd_to_dec(i2c_read_nack());

    i2c_stop();
}

void rtc_set_time(uint8_t sec, uint8_t min, uint8_t hour, uint8_t date, uint8_t month, uint8_t year) {
    i2c_start();
    i2c_write(DS1307_ADDR);
    i2c_write(0x00);

    i2c_write(dec_to_bcd(sec) & 0x7F);
    i2c_write(dec_to_bcd(min));
    i2c_write(dec_to_bcd(hour) & 0x3F);
    i2c_write(0x01);
    i2c_write(dec_to_bcd(date));
    i2c_write(dec_to_bcd(month));
    i2c_write(dec_to_bcd(year));

    i2c_stop();
}
