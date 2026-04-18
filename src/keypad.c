#include "keypad.h"
#include "config.h"
#include <util/delay.h>

void keypad_init(void) {
    ROW_DDR |= (1 << ROW0) | (1 << ROW1) | (1 << ROW2) | (1 << ROW3);
    COL_DDR &= ~((1 << COL0) | (1 << COL1) | (1 << COL2) | (1 << COL3));
    ROW_PORT |= (1 << ROW0) | (1 << ROW1) | (1 << ROW2) | (1 << ROW3);
    COL_PORT |= (1 << COL0) | (1 << COL1) | (1 << COL2) | (1 << COL3);
}

char keypad_scan(void) {
    char keys[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };

    uint8_t rows[4] = { ROW0, ROW1, ROW2, ROW3 };
    uint8_t cols[4] = { COL0, COL1, COL2, COL3 };

    for (uint8_t r = 0; r < 4; r++) {
        ROW_PORT &= ~(1 << rows[r]);
        _delay_us(10);

        for (uint8_t c = 0; c < 4; c++) {
            if (!(COL_PIN & (1 << cols[c]))) {
                _delay_ms(20);
                while(!(COL_PIN & (1 << cols[c])));
                ROW_PORT |= (1 << rows[r]);
                return keys[r][c];
            }
        }

        ROW_PORT |= (1 << rows[r]);
    }

    return 0;
}
