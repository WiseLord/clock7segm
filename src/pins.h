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
#define READ(x)             (PIN(x) & x ## _LINE)

#define SERIN               D
#define SERIN_LINE          (1<<7)
#define CLOCK               D
#define CLOCK_LINE          (1<<6)
#define LATCH               D
#define LATCH_LINE          (1<<5)

#define BUTTON_1            C
#define BUTTON_1_LINE       (1<<3)
#define BUTTON_2            C
#define BUTTON_2_LINE       (1<<2)
#define BUTTON_3            C
#define BUTTON_3_LINE       (1<<1)

#define I2C_SCL             C
#define I2C_SCL_LINE        (1<<5)
#define I2C_SDA             C
#define I2C_SDA_LINE        (1<<4)

#endif // PINS_H
