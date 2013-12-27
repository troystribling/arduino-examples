// lcd_16x2_hello_world.ino
// test a 16x2 lcd dispaly

#include <LiquidCrystal.h>

const int numRows = 2;
const int numCols = 16;

LiquidCrystal lcd(12, 8, 7, 6, 5, 4);

void setup() {
  lcd.begin(numCols, numRows);
  lcd.print("Hello, World!");
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
  delay(1000);
}

