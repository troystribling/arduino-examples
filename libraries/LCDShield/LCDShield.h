#ifndef LCDShield_h
#define LCDShield_h

#include <LiquidCrystal.h>

class LCDShield : public LiquidCrystal {
public:
	LCDShield();
	void begin(uint8_t charsize = LCD_5x8DOTS);
};

#endif