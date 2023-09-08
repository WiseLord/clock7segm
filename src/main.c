#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "ds18x20.h"
#include "mtimer.h"
#include "segm.h"
#include "rtc.h"

void hwInit(void)
{
    _delay_ms(250);

    ds18x20SearchDevices();
    mTimerInit();
    segmInit();

    sei();
}

int main(void)
{
    uint8_t cmd;

    hwInit();
    segmTime();

    ds18x20Process();

    while(1) {
        // Update sensors with SENSOR_POLL_INTERVAL period
        if (!sensTimer) {
            sensTimer = SENSOR_POLL_INTERVAL;
            ds18x20Process();
        }

        rtcReadTime();

        cmd = getBtnCmd();

        switch (cmd) {
        case BTN_0:
            dispTimer = DISPLAY_TIME;
            rtc.etm = RTC_HOUR;
            rtcChangeTime(+1);
            break;
        case BTN_1:
            dispTimer = DISPLAY_TIME;
            rtc.etm = RTC_MIN;
            rtcChangeTime(+1);
            rtc.etm = RTC_SEC;
            rtcChangeTime(0);
            break;
        }

        rtc.etm = RTC_ETM;

        if (dispTimer <= DISPLAY_TEMP) {
            segmTemp(0);
        } else {
            segmTime();
        }

        segmShow();
        _delay_ms(100);
    }

    return 0;
}
