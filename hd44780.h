#ifndef _HD44780_H_
#define _HD44780_H_
#include <stdint.h>
    /*
     * P0: RS
     * P1: WR
     * P2: CS
     * P3: P3
     * P4: DB4
     * P5: DB5
     * P6: DB6
     * P7: DB7
     * Nibble order, send upper first and lower second.
     */
typedef struct {
	uint8_t RS:1;
	uint8_t RW:1;
	uint8_t CS:1;
	uint8_t Backlight:1;
	uint8_t nibble:4;
}HD447680_BYTE;

typedef union {
	HD447680_BYTE type;
	uint8_t byte;
};

typedef void (*i2c_transfer_t)(uint8_t adr, uint8_t data);
typedef void (*millisecond_delay_t)(uint32_t milliseconds);

void setI2CFun(i2c_transfer_t* fun);
void setMilliSecondDelay(millisecond_delay_t* msDelayTime);

void init_lcd(void);
void writeLine(uint8_t* data);

#endif
