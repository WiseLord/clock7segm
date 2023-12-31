#ifndef MTIMER_H
#define MTIMER_H

#include <inttypes.h>

#define TEMP_MEASURE_TIME       2
#define SENSOR_POLL_INTERVAL    8

#define DISPLAY_TIME            12
#define DISPLAY_TEMP            2

#define BTN_STATE_0             0x00
#define BTN_0                   (1<<0)
#define BTN_1                   (1<<1)
#define BTN_2                   (1<<2)
#define BTN_0_LONG              (BTN_0<<4)
#define BTN_1_LONG              (BTN_1<<4)
#define BTN_2_LONG              (BTN_2<<4)

// Handling long press actions
#define SHORT_PRESS             25
#define LONG_PRESS              125

#define BEEP_SHORT              20
#define BEEP_LONG               40

#define TIME_SEC                250

#define TIME_DISP                250

extern volatile uint8_t sensTimer;
extern volatile uint8_t dispTimer;

void mTimerInit(void);

uint8_t getBtnCmd(void);

#endif // MTIMER_H
