// rotary_encoder.ino
// read a rotary encoder

const int encoderPinA                 = 4;
const int encoderPinB                 = 2;
const int encoderStepsPerRevolution   = 30;

int angle             = 0;
int encoderPos        = 0;
boolean encoderALast  = HIGH;
boolean encoderBLast  = HIGH;

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
  Serial.print("encoderA: ");Serial.println(encoderA);
  Serial.print("encoderALast: ");Serial.println(encoderALast);
  if (encoderALast != encoderA) {
    boolean encoderB = digitalRead(encoderPinB);
    Serial.print("encoderB: ");Serial.println(encoderB);
    Serial.print("encoderBLast: ");Serial.println(encoderBLast);
    if (encoderB == LOW) {
      encoderPos--;
    } else {
      encoderPos++;
    }
    encoderBLast = encoderB;
    angle = 360 * (encoderPos % encoderStepsPerRevolution)/encoderStepsPerRevolution;
    Serial.print("Postion: ");Serial.println(encoderPos);
    Serial.print("Angel: ");Serial.println(angle);
    encoderALast = encoderA;
  }
  Serial.println("");
  delay(1000);
}

