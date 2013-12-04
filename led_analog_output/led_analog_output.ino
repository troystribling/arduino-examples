// led_analog_output.ino
// control leds with analog output

const int firstLedPin   = 3;
const int secondLedPin  = 5;
const int thirdLedPin   = 6;

int brightness = 0;
int increment = 1;

void setup() {
}

void loop() {
  if (brightness > 255) {
    increment = -1;
  } else if (brightness < 1) {
    increment = 1;
  }
  brightness += increment;
  analogWrite(firstLedPin, brightness);
  analogWrite(secondLedPin, brightness);
  analogWrite(thirdLedPin, brightness);

  delay(10);
}

