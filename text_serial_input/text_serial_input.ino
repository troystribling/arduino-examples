// text_serial_input.ino

const int ledPin      = 13;  // pin the LED is connected to
int blinkRate         = 0;
const int maxChars    = 5;
int index             = 0;

char strValue[maxChars + 1];

void setup() {
	Serial.begin( 9600); 		// Initialize serial port to send and receive at 9600 baud
	pinMode(ledPin, OUTPUT); 	// set this pin as output
}

void loop() {
	if (Serial.available()) {
		char ch = Serial.read();
    Serial.print("Read: ");Serial.println(ch);
    if(index < maxChars && isDigit(ch)) {
      strValue[index++] = ch;
      Serial.print("adding ch: ");Serial.print(ch);Serial.print(" at index: ");Serial.println(index);
    } else {
      strValue[index] = 0;
      Serial.print("strValue: "); Serial.println(strValue);
      blinkRate = atoi(strValue);
      index = 0;
      Serial.print("blinkRate: "); Serial.println(blinkRate);
    }
  }
  blink(blinkRate);
}

void blink(int rate) {
	digitalWrite(ledPin, HIGH);
	delay(rate);
	digitalWrite(ledPin, LOW);
	delay(rate);
}
