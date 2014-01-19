// eeprom.ino
#include <EEPROM.h>

#define MAX_COUNT 10

int addr = 0;

void writeEEPROM() {
  Serial.println("Start write");
  for (int i = 0; i < MAX_COUNT; i++) {
    EEPROM.write(addr + i, i);
  }
  Serial.println("End write");
}

void readEEPROM() {
  Serial.println("Start read");
  int value;
  for (int i = 0; i < MAX_COUNT; i++) {
    value = EEPROM.read(addr + i);
    Serial.print(addr + i);
    Serial.print("\t");
    Serial.print(value, DEC);
    Serial.println();
  }
  Serial.println("End read");
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  writeEEPROM();
  readEEPROM();
  addr++;
  if (addr + MAX_COUNT > 512) {
    addr = 0;
  }
  delay(1000);
}
