// pin_change_int.ino
// illustartes the use on pin change interrupts

#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>

#define PIN 15
volatile byte burp=0;
byte cmd=0;

void setup() {
  Serial.begin(9600);
  Serial.print("PinChangeInt test on pin ");
  Serial.print(PIN);
  Serial.println();
  pinMode(PIN, INPUT);
  digitalWrite(PIN, HIGH);
  PCintPort::attachInterrupt(PIN, burpcount, RISING);
}

void loop() {
  cmd=Serial.read();
  if (cmd=='p') {
    Serial.print("burpcount:\t");
    Serial.println(burp, DEC);
  }
  cmd=0;
}

void burpcount() {
  burp++;
}

