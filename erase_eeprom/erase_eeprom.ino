// erase_eeprom.ino
#include <EEPROM.h>

#define NUMBER_BYTES 1024

int addr = 0;

void eraseEEPROM() {
  Serial.println("Start erase");
  for (int i = 0; i < NUMBER_BYTES; i++) {
    EEPROM.write(addr + i, 0x00);
  }
  Serial.println("End erase");
}

void setup() {
  Serial.begin(9600);
  eraseEEPROM();
}

void loop() {
  delay(1000);
}
