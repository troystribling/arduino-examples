// pull_up_button_led.ino
// a pushbutton is used to send a pull up signal through a digital pin to an led.
// a pull up switch sets the output to HIGH when the input is LOW and the out to LOW when the input is HIGH.

const int ledPin    = 13;
const int inputPin  = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
}

void loop() {
  int val = digitalRead(inputPin);
  if (val == HIGH) {
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
  }
}


