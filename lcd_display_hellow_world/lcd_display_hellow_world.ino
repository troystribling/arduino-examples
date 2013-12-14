// lcd_display_hellow_world.ino
// test an lcd display

#include <LiquidCrystal.h>

const int numRows   = 4;
const int numCols   = 16;

// specify lcd interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(numCols, numRows);
  lcd.print("hello, world!");
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
}



