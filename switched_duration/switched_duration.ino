// switched_duration.ino
// deterime how long a switch has been pressed

const int ledPin              = 13;
const int inputPin            = 2;
const int debounceTime        = 20;

static unsigned long startTime  = 0;
static unsigned long lastTime   = 0;
static boolean state            = 0;
static boolean lastState        = 0;

int count = 0;

void setup() {
  pinMode(inputPin, INPUT);
  digitalWrite(inputPin, HIGH);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

long switchedTime() {
  long currentTime = millis();
  if (digitalRead(inputPin) != state) {
    state = !state;
    startTime = currentTime;
  }
  return currentTime - startTime;
}

void loop() {
  int duration = switchedTime();
  if (duration > debounceTime) {
    if (state == LOW) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
  }
  if (duration == 0) {
    Serial.print("STATE: "); Serial.print(lastState); Serial.print(","); Serial.println(lastTime);
  }
  lastTime = duration;
  lastState = state;
  delay(1);
}

