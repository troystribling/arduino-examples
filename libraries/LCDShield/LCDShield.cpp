#include "LCDShield.h"

const static int numRows = 2;
const static int numCols = 16;

const static int rsPin      = 12; // data input
const static int enablePin  = 8;  // enable signal
const static int d0Pin      = 7;  // data bus 1
const static int d1Pin      = 6;  // data bus 2
const static int d2Pin		= 5;  // data bus 3
const static int d3Pin      = 4;  // data bus 4

LCDShield::LCDShield(): LiquidCrystal(rsPin, enablePin, d0Pin, d1Pin, d2Pin, d3Pin) {
}

void LCDShield::begin(uint8_t charsize) {
	LiquidCrystal::begin(numCols, numRows, charsize);
}