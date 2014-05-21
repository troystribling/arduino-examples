/* * I2C_Slave * monitors I2C requests and echoes these to the serial port */

#include <Wire.h>
const int address = 4;

// the address to be used by the communicating devices

void setup() {
  Serial.begin(9600);
  Serial.println("Slave Starting");
  Wire.begin(address);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {
}

void receiveEvent(int howMany) {
  Serial.println("receiveEvent");
  while(Wire.available() > 0) {
    char c = Wire.read();
    Serial.write(c);
  }
  Serial.println("");Serial.println("finished");
}

void requestEvent() {
  Serial.println("Master Request Received");
  Wire.write("good bye");
  Serial.println("finished");
}