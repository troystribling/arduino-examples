#include <Servo.h>

Servo myservo;

int angle = 0;

void setup() {
  myservo.attach(9);
}

void loop() {
  for(angle = 0; angle < 180; angle += 10) {
    myservo.write(angle);
    delay(100);
  }
  for(angle = 180; angle >= 1; angle -= 10) {
    myservo.write(angle);
    delay(100);
  }
}
