#include "keypad.h"
#include "config.h"
#include <util/delay.h>

void keypad_init(void) {
    PIN_OUTPUT(ROW0); PIN_OUTPUT(ROW1); PIN_OUTPUT(ROW2); PIN_OUTPUT(ROW3);
    PIN_INPUT(COL0);  PIN_INPUT(COL1);  PIN_INPUT(COL2);  PIN_INPUT(COL3);

    PIN_HIGH(ROW0); PIN_HIGH(ROW1); PIN_HIGH(ROW2); PIN_HIGH(ROW3);
    PIN_HIGH(COL0); PIN_HIGH(COL1); PIN_HIGH(COL2); PIN_HIGH(COL3);
}

#define CHECK_COL(col_macro, r, c)                                      \
    if (!PIN_READ(col_macro)) {                                         \
        _delay_ms(20);                                                  \
        while (!PIN_READ(col_macro));                                   \
        PIN_HIGH(ROW0); PIN_HIGH(ROW1); PIN_HIGH(ROW2); PIN_HIGH(ROW3); \
        return keys[r][c];                                              \
    }

char keypad_scan(void) {
    char keys[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };

    PIN_LOW(ROW0); _delay_us(10);
    CHECK_COL(COL0, 0, 0); CHECK_COL(COL1, 0, 1); CHECK_COL(COL2, 0, 2); CHECK_COL(COL3, 0, 3);
    PIN_HIGH(ROW0);

    PIN_LOW(ROW1); _delay_us(10);
    CHECK_COL(COL0, 1, 0); CHECK_COL(COL1, 1, 1); CHECK_COL(COL2, 1, 2); CHECK_COL(COL3, 1, 3);
    PIN_HIGH(ROW1);

    PIN_LOW(ROW2); _delay_us(10);
    CHECK_COL(COL0, 2, 0); CHECK_COL(COL1, 2, 1); CHECK_COL(COL2, 2, 2); CHECK_COL(COL3, 2, 3);
    PIN_HIGH(ROW2);

    PIN_LOW(ROW3); _delay_us(10);
    CHECK_COL(COL0, 3, 0); CHECK_COL(COL1, 3, 1); CHECK_COL(COL2, 3, 2); CHECK_COL(COL3, 3, 3);
    PIN_HIGH(ROW3);

    return '\0';
}
