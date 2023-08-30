#include <avr/io.h>
#include <util/delay.h>

#include "segm.h"
#include "pins.h"

int main(void)
{
    segmInit();
    
    OUT(LED);
    
    while(1) {
        for (int16_t i = 9999; i >= 0; i--) {
            segmNum(i, 0);
            segmShow();
            
            if (i % 2 == 0) {
                SET(LED);
            } else {
                CLR(LED);
            }
            _delay_ms(100);
        }
    }

    return 0;
}
