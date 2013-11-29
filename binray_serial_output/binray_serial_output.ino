// binray_serial_output.ino

int intValue;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.write('H');
  intValue = random(pow(2,16));
  Serial.write(lowByte(intValue));
  Serial.write(highByte(intValue));
  delay(1000);
}

