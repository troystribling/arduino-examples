// pin_serial_ouput.ino
// write values of analog and digtal pins to serial port

void setup() {
  Serial.begin(9600);
  // turn on all digital pins
  for (int i = 2; i <= 13; i++) {
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }
}

void loop() {
  int values = 0;
  for(int i = 2; i <= 13; i++) {
    bitWrite(values, i - 2, digitalRead(i));
  }
  Serial.println(values, BIN);
  for(int i = 0; i < 6; i++) {
    Serial.println(analogRead(i), DEC);
  }
  delay(1000);
}
