// rotary_encoder.ino
// read a rotary encoder

const int encoderPinA                 = 4;
const int encoderPinB                 = 2;
const int encoderStepsPerRevolution   = 30;

int angle             = 0;
int encoderPos        = 0;
boolean encoderALast  = LOW;

boolean encoderA;

void setup() {
  Serial.begin(9600);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  digitalWrite(encoderPinA, HIGH);
  digitalWrite(encoderPinB, HIGH);
}

void loop() {
  encoderA = digitalRead(encoderPinA);
  if (encoderALast == HIGH && encoderA == LOW) {
    if (digitalRead(encoderPinB) == LOW) {
      encoderPos--;
    } else {
      encoderPos++;
    }
  }
  angle = 360 * (encoderPos % encoderStepsPerRevolution)/encoderStepsPerRevolution;
  Serial.print("Postion: ");Serial.println(encoderPos)
  Serial.print("Anglel: ");Serial.println(angle);
  encoderALast = encoderA;
  delay(1000);
}

