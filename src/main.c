#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "mtimer.h"
#include "segm.h"
#include "rtc.h"

int main(void)
{
    uint8_t cmd;

    mTimerInit();
    segmInit();

    sei();

    while(1) {
        rtcReadTime();

        cmd = getBtnCmd();

        switch (cmd) {
        case BTN_0:
            rtc.etm = RTC_HOUR;
            rtcChangeTime(+1);
            break;
        case BTN_1:
            rtc.etm = RTC_MIN;
            rtcChangeTime(+1);
            rtc.etm = RTC_SEC;
            rtcChangeTime(0);
            break;
        }

        rtc.etm = RTC_ETM;

        segmTime();

        segmShow();
        _delay_ms(100);
    }

    return 0;
}
