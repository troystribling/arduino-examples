// pull_down_button_led.ino
// a pushbutton is used to send a pull down signal through a digital pin to an led.
// a pull down switch sets the output to HIGH when the INPUT is HIGH and the output to LOW when the input is LOW.

const int ledPin    = 13;
const int inputPin  = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
}

void loop() {
  int val = digitalRead(inputPin);
  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

