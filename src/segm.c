#include "segm.h"

#include <util/delay.h>

#include "pins.h"
#include "rtc.h"
#include "mtimer.h"

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

    for (i = 0; i < DIGITS; i++) {
        ind[i] = 0;
    }

    if (number < 0) {
        neg = 1;
        number = -number;
    }

    for (i = 0; i < DIGITS; i++) {
        if (number == 0 && i > dot)
            break;
        ind[i] = num[number % 10];
        number /= 10;
    }

    if (neg)
        ind[i] |= BIT_G;
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

void segmTime()
{

    // Data for left and right halfs of display
    uint8_t tmL = rtc.hour;
    uint8_t tmR = rtc.min;

    // Prepare indicators data
    ind[0] = num[tmR % 10];
    ind[1] = num[tmR / 10];

    ind[2] = num[tmL % 10];
    ind[3] = num[tmL / 10];

    // Show dot
    if (rtc.sec % 2) {
        ind[2] |= BIT_P;
    }
}
