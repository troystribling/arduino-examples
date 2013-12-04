// led_digital_output.ino
// control leds with digital output ports

const int firstLedPin   = 3;
const int secondLedPin  = 5;
const int thirdLedPin   = 6;

void setup() {
  pinMode(firstLedPin, OUTPUT);
  pinMode(secondLedPin, OUTPUT);
  pinMode(thirdLedPin, OUTPUT);
}

void blink(int pin, int duration) {
  digitalWrite(pin, HIGH);  // turn led off
  delay(duration);
  digitalWrite(pin, LOW);   // turn led on
  delay(duration);
}

void loop() {
  blink(firstLedPin, 1000);
  blink(secondLedPin, 1000);
  blink(thirdLedPin, 1000);
}

