#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile uint8_t  timer_done;
extern volatile uint16_t overflow_count;
extern volatile uint16_t target_overflows;

// --- Non-blocking (Interrupt) ---
void timer_delay_ms(uint16_t milliseconds);
void timer_delay_us(uint16_t microseconds);

// --- Blocking (Polling) ---
void timer_wait_ms(uint16_t milliseconds);
void timer_wait_us(uint16_t microseconds);

#endif // TIMER_H
