#include <avr/io.h>
#include <util/delay.h>

#include "pins.h"

int main(void)
{
    OUT(SERIN);
    OUT(CLOCK);
    OUT(LATCH);

    CLR(SERIN);
    CLR(CLOCK);
    CLR(LATCH);

    while (1) {
        uint32_t data = 0b10101010010101011100110000110011;

        for (uint8_t i = 0; i < 32; i++) {

            if (data & (1UL << i)) {
                SET(SERIN);
            } else {
                CLR(SERIN);
            }

            _delay_us(2);
            SET(CLOCK);
            _delay_us(2);
            CLR(CLOCK);
        }

        _delay_us(2);
        SET(LATCH);
        _delay_us(2);
        CLR(LATCH);
     }

    return 0;
}
