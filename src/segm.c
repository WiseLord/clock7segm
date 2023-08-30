#include "segm.h"

#include <util/delay.h>

#include "pins.h"

static volatile uint8_t ind[DIGITS];
static const uint8_t num[] = {CH_0, CH_1, CH_2, CH_3, CH_4, CH_5, CH_6, CH_7, CH_8, CH_9};

void segmInit(void)
{
    OUT(SERIN);
    OUT(CLOCK);
    OUT(LATCH);

    CLR(SERIN);
    CLR(CLOCK);
    CLR(LATCH);
}

void segmNum(int16_t number, uint8_t dot)
{
    uint8_t i;
    uint8_t neg = 0;

    // Indicator data buffer;
    uint8_t buf[DIGITS];
    
    for (i = 0; i < DIGITS; i++) {
        buf[i] = 0;
    }

    if (number < 0) {
        neg = 1;
        number = -number;
    }

    for (i = 0; i < DIGITS; i++) {
        if (number == 0 && i > dot)
            break;
        buf[i] = num[number % 10];
        number /= 10;
    }

    if (neg)
        buf[i] |= BIT_G;

    ind[0] = buf[0];
    ind[1] = buf[1];
    ind[2] = buf[2];
    ind[3] = buf[3];
}

void segmShow(void)
{
    int8_t i, j;
    for (i = DIGITS - 1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            if (ind[i] & (1 << j)) {
                SET(SERIN);
            } else {
                CLR(SERIN);
            }
            _delay_us(2);
            SET(CLOCK);
            _delay_us(2);
            CLR(CLOCK);
        }
    }

    _delay_us(2);
    SET(LATCH);
    _delay_us(2);
    CLR(LATCH);
}
