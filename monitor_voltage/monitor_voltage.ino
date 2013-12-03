// monitor_voltage.ino
// report a measured voltage

const int batterPin           = 0;
const float referenceVoltage  = 5.0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(batterPin);
  float volts = (referenceVoltage*val)/1023.0;
  Serial.println(volts);
  delay(2000);
}

