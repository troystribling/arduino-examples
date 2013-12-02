// voltage_alarms.ino
// flash and LED if voltage drops below a threshold

const long batteryFull        = 2250;
const long warningThreshold   = 2000;
const long criticalThreshold  = 1800;
const long maxDelay           = 1000;

const int ledPin      = 13;
const int batteryPin  = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int val = analogRead(batteryPin);
  int mvolts = map(val, 0, 1023, 0, 5000);
  Serial.println(mvolts);
  if (mvolts < criticalThreshold) {
    alarm(0);
  } else if (mvolts < warningThreshold) {
    int percent = map(mvolts, criticalThreshold, batteryFull, 0, 100);
    constrain(percent, 0, 100);
    alarm(percent);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void alarm(int percent) {
  int delayVal = maxDelay*percent/100;
  digitalWrite(ledPin, HIGH);
  delay(maxDelay - delayVal + 1);
  digitalWrite(ledPin, LOW);
  delay(delayVal + 1);
}
