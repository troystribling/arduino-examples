/*
  keypad.ino

  interface with a 4x3 10 pin keypad from Jameco. Jameco Part no. 2082206
  https://www.jameco.com/webapp/wcs/stores/servlet/ProductDisplay?langId=-1&storeId=10001&catalogId=10001&productId=2082206

  Pin layout

  key   X     Y
  1     p10   p6
  2     p10   p5
  3     p10   p4
  4     p9    p6
  5     p9    p5
  6     p9    p4
  7     p7    p6
  8     p7    p5
  0     p7    p4
  9     p8    p4
  #     p2    p1
  *     p2    p3

  x pins = {10, 9, 7, 8, 2}
  y pins = { 6, 5, 4, 3, 1}

  row pins are configured as inputs and column
  pins as outputs. key press connects input to output and is detected by determining which pins are connected.

*/

const int numRows         = 5;
const int numCols         = 5;
const int debounceTime    = 10;

const char keymap[numRows][numCols] = {
  {'1', '2', '3', '-', '-'},
  {'4', '5', '6', '-', '-'},
  {'7', '8', '0', '-', '-'},
  {'-', '-', '9', '-', '-'},
  {'-', '-', '-', '*', '#'},
};

const int rowPins[numRows] = {11, 10, 8, 9, 3};
const int colPins[numCols] = {7, 6, 5, 4, 2};

void setup() {
  Serial.begin(9600);
  // set row pins as input and enable pull-up resistor by setting value to HIGH
  for(int row = 0; row < numRows; row++) {
    pinMode(rowPins[row], INPUT);
    digitalWrite(rowPins[row], HIGH);
  }
  // set column pins as output and make all inactive by setting value to HIGH
  for (int col = 0; col < numCols; col++) {
    pinMode(colPins[col], OUTPUT);
    digitalWrite(colPins[col], HIGH);
  }
}

void loop() {
  char key = getKey();
  if (key != 0) {
    Serial.print("Key: ");Serial.println(key);
  }
}

char getKey() {
  // 0 indicates no key pressed
  char key = 0;
  // keys press is detected by activating columns and reading rows
  for (int col = 0; col < numCols; col++) {
    digitalWrite(colPins[col], LOW);
    for (int row = 0; row < numRows; row++) {
      if (keymap[row][col] != '-') {
        if (digitalRead(rowPins[row]) == LOW) {
          delay(debounceTime);
          while(digitalRead(rowPins[row]) == LOW) {
            delay(debounceTime);
          }
          key = keymap[row][col];
        }
      }
    }
    digitalWrite(colPins[col], HIGH);
  }
  return key;
}

