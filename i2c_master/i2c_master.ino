/* * I2C_Master * Echo Serial data to an I2C slave */
#include <Wire.h>

const int address = 4;

// the address to be used by the communicating devices

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  writeMessage();
}

void writeMessage() {
  char message = 'A';
  Serial.print("writeMessage: ");Serial.println(message);
  Wire.beginTransmission(address);
  Serial.println("beginTransmission");
  Wire.write(message);
  Wire.endTransmission();
  Serial.println("message sent");
}
