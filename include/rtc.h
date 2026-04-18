#ifndef RTC_H
#define RTC_H

#include <stdint.h>

uint8_t bcd_to_dec(uint8_t val);
uint8_t dec_to_bcd(uint8_t val);

void rtc_set_time(uint8_t sec, uint8_t min, uint8_t hour, uint8_t date, uint8_t month, uint8_t year);
void rtc_get_time(uint8_t* sec, uint8_t* min, uint8_t* hour, uint8_t* date, uint8_t* month, uint8_t* year);

#endif // RTC_H
