/* * I2C_Master * Echo Serial data to an I2C slave */
#include <Wire.h>

const int address = 4;
const char* message = "Hello-";

// the address to be used by the communicating devices

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  writeMessage();
  readResponse(8);
}

void writeMessage() {
  Serial.print("writeMessage: ");Serial.println(message);
  Wire.beginTransmission(address);
  for (int i = 0; i < strlen(message); i++) {
    Wire.write(message[i]);
  }
  Wire.endTransmission();
  Serial.println("message sent");
}

void readResponse(int8_t message_size) {
  Serial.println("readResponse");
  Wire.requestFrom(address, message_size);
  while(Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println("");Serial.println("finished");
}
