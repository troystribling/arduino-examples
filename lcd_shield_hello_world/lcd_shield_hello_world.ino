// lcd_shield_hello_world.ino
// test the LCDShield library

#include <LiquidCrystal.h>
#include <LCDShield.h>

LCDShield lcd;

void setup() {
  lcd.begin();
  lcd.print("Hello, World!");
}

void loop() {
  lcd.setCursor(0,1);
  lcd.print(millis()/1000);
  delay(1000);
}

