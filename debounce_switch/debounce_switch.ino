// debounce_switch.ino
// an algorithm to more reliably detect switch activation.

const int inputPin        = 2;
const int ledPin          = 13;
const int debounceDelay   = 10;
int count                 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
  digitalWrite(inputPin, HIGH);
}

void loop() {
  if (debounce(inputPin)) {
    digitalWrite(ledPin, LOW);
  } else {
    count++;
    Serial.print("total detections: ");Serial.println(count);
    digitalWrite(ledPin, HIGH);
  }
}

// before declaring the pin in state observer a specicfied number of
// sequential reads to be in that state
boolean debounce(int pin) {
  boolean currentState, previousState;
  previousState = digitalRead(pin);
  for (int i; i < debounceDelay; i++) {
    delay(1);
    currentState = digitalRead(pin);
    if (currentState != previousState) {
      i = 0;
      previousState = currentState;
    }
  }
  return currentState;
}
