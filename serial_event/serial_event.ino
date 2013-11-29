// serial_event.ino
// illustrate the use of the serialEvent callback to set led blink rate using serial input

const int ledPin      = 13;
int blinkRate         = 0;

void setup() {
  Serial.begin( 9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  blink(blinkRate);
}

void serialEvent() {
  while(Serial.available()) {
    char ch = Serial.read();
    Serial.print("Read: ");Serial.println(ch);
    if(isDigit(ch)) {
      blinkRate = 100*(ch - '0');
      Serial.print("blinkRate: "); Serial.println(blinkRate);
    }
  }
}

void blink(int rate) {
  digitalWrite(ledPin, HIGH);
  delay(rate);
  digitalWrite(ledPin, LOW);
  delay(rate);
}
