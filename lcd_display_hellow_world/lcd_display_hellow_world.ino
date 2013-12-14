// lcd_display_hellow_world.ino
// test a 16x4 lcd display

#include <LiquidCrystal.h>

const int numRows   = 4;
const int numCols   = 16;

// specify lcd interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.setCursor(0, 0);
  lcd.begin(numCols, numRows);
  lcd.print("hello, world!");
  lcd.setCursor(-4, 2);
  lcd.print("row 3");
  lcd.setCursor(-4, 3);
  lcd.print("row 4");
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print("uptime: ");
  lcd.setCursor(7, 1);
  lcd.print(millis()/1000);
}



