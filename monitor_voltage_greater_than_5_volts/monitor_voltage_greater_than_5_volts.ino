// monitor_voltage_greater_than_5_volts.ino
// an arduino can not directly measure a voltage greater tha 5 volts. this example will
// demonstrate how to monitor voltages grater than 5 volts.

const int batteryPin = 0;
const long referenceVoltage = 5000;

// multiplier defines maximum measurable voltage in multiples of reference voltage;
// vm = vd*multiplier
// where vm = measured voltage, vd = detected voltage
const int multiplier = 2;

void setup() {
  Serial.begin(9600);
}

void loop() {
  long anaVal = analogRead(batteryPin)*referenceVoltage;
  long vd = anaVal/1023;
  long vm = vd*multiplier;
  Serial.println(vm);
  delay(1000);
}

