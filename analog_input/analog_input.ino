// analog_input.ino
//  use a potentiometer to control the lash duration of an led

const int ledPin    = 13;
const int potPin    = 0;
const int maxDelay  = 1000;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int val = analogRead(potPin);
  int percent = map(val, 0, 1023, 0, 100);
  int delayVal = maxDelay*percent/100 ;
  digitalWrite(ledPin, HIGH);
  delay(delayVal + 1);
  digitalWrite(ledPin, LOW);
  delay(maxDelay - delayVal + 1);
  Serial.println(percent);
}

