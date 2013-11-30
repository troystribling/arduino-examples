// pull_up_button_led_internal_resistor.ino
// a pushbutton is used to send a pull up signal through a digital pin to an led. in this example
// the arduino interval pull up resistor is used instead of an extenal pull up resistor as used in the other example.

const int ledPin    = 13;
const int inputPin  = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
  // turn on internal pull-up resistor
  digitalWrite(inputPin, HIGH);
}

void loop() {
  int val = digitalRead(inputPin);
  if (val == HIGH) {
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
  }
}

