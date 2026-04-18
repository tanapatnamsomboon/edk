#ifndef CONFIG_H
#define CONFIG_H

#include <avr/io.h>

// --- LCD Configuration ---
#define LCD_RS         PB2
#define LCD_RS_PORT    PORTB
#define LCD_RS_DDR     DDRB
#define LCD_EN         PB1
#define LCD_EN_PORT    PORTB
#define LCD_EN_DDR     DDRB

#define LCD_DATA_PORT  PORTD
#define LCD_DATA_DDR   DDRD
#define LCD_DATA_START 0

#define LCD_CMD_4BIT_MODE  0x28
#define LCD_CMD_DISPLAY_ON 0x0C
#define LCD_CMD_ENTRY_MODE 0x06
#define LCD_CMD_CLEAR      0x01


// --- ADC Configuration ---
#define ADC_REF_AVCC      (1 << REFS0)
#define ADC_PRESCALER_128 ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))


// --- I2C & RTC Configuration ---
#define DS1307_ADDR 0xD0
#define I2C_TIMEOUT 10000


// --- Keypad Configuration ---
#define ROW_PORT PORTC
#define ROW_DDR  DDRC
#define ROW0 PC0
#define ROW1 PC1
#define ROW2 PC2
#define ROW3 PC3

#define COL_PORT PORTD
#define COL_DDR  DDRD
#define COL_PIN  PIND
#define COL0 PD4
#define COL1 PD5
#define COL2 PD6
#define COL3 PD7

// --- Ultrasonic Configuration ---
#define UTRIG      PC0
#define UTRIG_PORT PORTC
#define UTRIG_PIN  PINC
#define UTRIG_DDR  DDRC
#define UECHO      PC1
#define UECHO_PORT PORTC
#define UECHO_PIN  PINC
#define UECHO_DDR  DDRC

#endif // CONFIG_H
