#include "hd44780.h"

static HD447680_BYTE outputByte;
static i2c_transfer_t* i2cFun;
millisecond_delay_t* msDelay;

static void setReadWrite(uint8_t value);

void setI2CFun(i2c_transfer_t* fun) {
	i2cFun = fun;
}

void setMilliSecondDelay(millisecond_delay_t* msDelayTime) {
	msDelay = msDelayTime;
}

void init_lcd(void) {

}

void writeLine(uint8_t* data) {

}

static void setReadWrite(uint8_t value){
	outputByte.RW = value;

}
