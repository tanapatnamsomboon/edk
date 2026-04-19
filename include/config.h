#ifndef CONFIG_H
#define CONFIG_H

#include <avr/io.h>

// --- ADC Configuration ---
#define ADC_REF_AVCC      (1 << REFS0)
#define ADC_PRESCALER_128 ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))

// --- I2C & RTC Configuration ---
#define DS1307_ADDR 0xD0
#define I2C_TIMEOUT 10000

//////////////////////////////
//      Macro Helper        //
//////////////////////////////
#define CONCAT(a, b) a ## b
#define PORT_REG(port) CONCAT(PORT, port)
#define DDR_REG(port)  CONCAT(DDR, port)
#define PIN_REG(port)  CONCAT(PIN, port)

#define EXPAND(x) x

#define PIN_OUTPUT_IMPL(port, pin) DDR_REG(port) |= (1 << (pin))
#define PIN_INPUT_IMPL(port, pin)  DDR_REG(port) &= ~(1 << (pin))
#define PIN_HIGH_IMPL(port, pin)   PORT_REG(port) |= (1 << (pin))
#define PIN_LOW_IMPL(port, pin)    PORT_REG(port) &= ~(1 << (pin))
#define PIN_READ_IMPL(port, pin)   (PIN_REG(port) & (1 << (pin)))

#define PIN_OUTPUT(...) EXPAND(PIN_OUTPUT_IMPL(__VA_ARGS__))
#define PIN_INPUT(...)  EXPAND(PIN_INPUT_IMPL(__VA_ARGS__))
#define PIN_HIGH(...)   EXPAND(PIN_HIGH_IMPL(__VA_ARGS__))
#define PIN_LOW(...)    EXPAND(PIN_LOW_IMPL(__VA_ARGS__))
#define PIN_READ(...)   EXPAND(PIN_READ_IMPL(__VA_ARGS__))

//////////////////////////////////
//      LCD Configuration       //
//////////////////////////////////
#define LCD_RS B, 2
#define LCD_EN B, 1

#define LCD_D4 D, 0
#define LCD_D5 D, 1
#define LCD_D6 D, 2
#define LCD_D7 D, 3

#define LCD_CMD_4BIT_MODE  0x28
#define LCD_CMD_DISPLAY_ON 0x0C
#define LCD_CMD_ENTRY_MODE 0x06
#define LCD_CMD_CLEAR      0x01

//////////////////////////////////
//      Keypad Configuration    //
//////////////////////////////////
#define ROW0 C, 0
#define ROW1 C, 1
#define ROW2 C, 2
#define ROW3 C, 3

#define COL0 D, 4
#define COL1 D, 5
#define COL2 D, 6
#define COL3 D, 7

/////////////////////////////////////////
//      Ultrasonic Configuration       //
/////////////////////////////////////////
#define UTRIG C, 0
#define UECHO C, 1

/////////////////////////////////
//      LED Configuration      //
/////////////////////////////////
#define LED1 B, 0
#define LED2 B, 6
#define LED3 B, 7

#endif // CONFIG_H
