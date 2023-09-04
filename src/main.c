#include <avr/io.h>
#include <util/delay.h>

#include "segm.h"
#include "pins.h"
#include "rtc.h"

int main(void)
{
    segmInit();

    while(1) {
        rtcReadTime();
        segmTime();

        segmShow();
        _delay_ms(100);
    }

    return 0;
}
