// charlie_plexing.ino
// use 3 output pins to drive 6 leds in a charlie plexed configuration

int ledPins[] = {2,3,4};

const int NUMBER_OF_PINS = sizeof(ledPins)/sizeof(ledPins[0]);
const int NUMBER_OF_LEDS = NUMBER_OF_PINS * (NUMBER_OF_PINS - 1);

byte ledPairs[NUMBER_OF_LEDS/2][2] = {{2,1}, {1,0}, {2,0}};

void setup() {
}

void lightLed(int led) {

  int indexA = ledPairs[led/2][0];
  int indexB = ledPairs[led/2][1];
  int ledPinA = ledPins[indexA];
  int ledPinB = ledPins[indexB];

  // turn off all LEDs not connected to given LED
  for(int i = 0; i < NUMBER_OF_PINS; i++) {
    if (ledPins[i] != ledPinA && ledPins[i] != ledPinB) {
      // set pinmode to input
      pinMode(ledPins[i], INPUT);
      // turn off pull-up resistor
      digitalWrite(ledPins[i], LOW);
    }
  }

  pinMode(ledPinA, OUTPUT);
  pinMode(ledPinB, OUTPUT);

  if (led % 2 == 0) {
    digitalWrite(ledPinA, LOW);
    digitalWrite(ledPinB, HIGH);
  } else {
    digitalWrite(ledPinA, HIGH);
    digitalWrite(ledPinB, LOW);
  }
}

void loop() {
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    lightLed(i);
    delay(1000);
  }
}