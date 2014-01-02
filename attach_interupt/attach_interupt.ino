// attach_interupt.ino
// attach interrupt example

int pin = 13;
volatile int state = LOW;

void setup() {
  Serial.begin(9600);
  Serial.println("Start Test");
  pinMode(pin, OUTPUT);
  attachInterrupt(0, blink, CHANGE);
}

void loop() {
  digitalWrite(pin, state);
}

void blink() {
  state = !state;
  Serial.print("blink: ");Serial.println(state);
}
