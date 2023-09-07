#include "mtimer.h"

#include <avr/interrupt.h>
#include "pins.h"

// Command buffer
static volatile uint8_t cmdBuf;

void mTimerInit(void)
{
    TIMSK |= (1 << TOIE0);                              // Enable Timer0 overflow interrupt
    TCCR0 = (1 << CS02) | (0 << CS01) | (0 << CS00);    // Set timer prescaller to 256 (43200Hz)

    // Setup buttons as inputs with pull-up resistors
    IN(BUTTON_1);
    IN(BUTTON_2);
    IN(BUTTON_3);
    SET(BUTTON_1);
    SET(BUTTON_2);
    SET(BUTTON_3);

    cmdBuf = BTN_1;

}

ISR (TIMER0_OVF_vect)                                   // 43200 / (256 - 83) = 250 polls/sec
{
    TCNT0 = 83;

    static int16_t btnCnt = 0;                          // Buttons press duration value
    static uint8_t btnPrev = 0;                         // Previous buttons state

    uint8_t btnNow = BTN_STATE_0;

    if (!READ(BUTTON_1))
        btnNow |= BTN_0;
    if (!READ(BUTTON_2))
        btnNow |= BTN_1;
    if (!READ(BUTTON_3))
        btnNow |= BTN_2;

    // If button event has happened, place it to command buffer
    if (btnNow) {
        if (btnNow == btnPrev) {
            btnCnt++;
            if (btnCnt == LONG_PRESS)
                cmdBuf = (btnPrev << 4);
        } else {
            btnPrev = btnNow;
        }
    } else {
        if ((btnCnt > SHORT_PRESS) && (btnCnt < LONG_PRESS))
            cmdBuf = btnPrev;
        btnCnt = 0;
    }
}

uint8_t getBtnCmd(void)
{
    uint8_t ret = cmdBuf;
    cmdBuf = BTN_STATE_0;

    return ret;
}
