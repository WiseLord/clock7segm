#ifndef PINS_H
#define PINS_H

#include <avr/io.h>

#define CONCAT(x,y)         x ## y

#define DDR(x)              CONCAT(DDR,x)
#define PORT(x)             CONCAT(PORT,x)
#define PIN(x)              CONCAT(PIN,x)

#define OUT(x)              DDR(x) |= x ## _LINE
#define IN(x)               DDR(x) &= ~x ## _LINE
#define SET(x)              PORT(x) |= x ## _LINE
#define CLR(x)              PORT(x) &= ~x ## _LINE

#define SERIN               D
#define SERIN_LINE          (1<<7)
#define CLOCK               D
#define CLOCK_LINE          (1<<6)
#define LATCH               D
#define LATCH_LINE          (1<<5)

#endif // PINS_H
