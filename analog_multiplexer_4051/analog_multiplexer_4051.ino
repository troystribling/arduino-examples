// analog_multiplexer_4051.ino
// this example illustrates use of the 4051 analog multiplexer by using trim pots to control
// the color of an rgb led.

const int redPin        = 3;
const int greenPin      = 5;
const int bluePin       = 6;

const int inputPin      = 0;

const int channelPins[] = {7, 8, 9};
const int channelCount  = sizeof(channelPins)/sizeof(channelPins[0]);;

const int redChannel    = 0;
const int greenChannel  = 1;
const int blueChannel   = 2;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < channelCount; i++) {
    pinMode(channelPins[i], OUTPUT);
  }
}

void updateLed(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

int readChannel(int channelNumber) {
  Serial.print("CHANNEL: ");Serial.println(channelNumber);
  for (int bit = 0; bit < 3; bit++) {
    Serial.print("BIT: ");Serial.println(bit);
    int pin = channelPins[bit];
    Serial.print("PIN: ");Serial.println(pin);
    int isBitSet = bitRead(channelNumber, bit);
    Serial.print("BIT VALUE: ");Serial.println(isBitSet);
    digitalWrite(pin, isBitSet);
  }
  int val = analogRead(inputPin);
  Serial.print("RAW VALUE: ");Serial.println(val);
  val = map(val, 0, 1023, 0, 255);
  Serial.print("SCALED VALUE: ");Serial.println(val);
  return constrain(val, 0, 255);

}

void loop() {
  Serial.println("");
  int red = readChannel(redChannel);
  int green = readChannel(greenChannel);
  int blue = readChannel(blueChannel);
  Serial.print("RED: ");Serial.println(red);
  Serial.print("GREEN: ");Serial.println(green);
  Serial.print("BLUE: ");Serial.println(blue);
  updateLed(red, green, blue);
  delay(1000);
}

