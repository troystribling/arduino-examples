// pull_up_button_led_internal_resistor.ino

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

