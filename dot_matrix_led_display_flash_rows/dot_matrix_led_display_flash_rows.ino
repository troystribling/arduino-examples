// dot_matrix_led_display.ino
// This examples drives the Lite On two color 5x7 LED dot matrix
// http://www.jameco.com/webapp/wcs/stores/servlet/ProductDisplay?langId=-1&storeId=10001&catalogId=10001&productId=1955159

const int columnPins[] = {2, 3, 4, 5, 6};
const int rowPins[] = {9, 10, 11, 12, 15, 16, 17};

const int NUMBER_OF_COLUMNS = sizeof(columnPins)/sizeof(columnPins[0]);
const int NUMBER_OF_ROWS = sizeof(rowPins)/sizeof(rowPins[0]);

int currentRow = 1;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUMBER_OF_ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
  }
  for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {
    pinMode(columnPins[j], OUTPUT);
  }
  setDisplayState(LOW);
  setRowState(currentRow - 1, HIGH);
  delay(5000);
}

void setDisplayState(int state) {
  for (int i = 0; i < NUMBER_OF_ROWS; i++) {
    digitalWrite(rowPins[i], state);
  }
  for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
    digitalWrite(columnPins[i], LOW);
  }
}

void setRowState(int row, int state) {
  digitalWrite(rowPins[row], state);
}

void loop() {
  Serial.print("Turn off row: "); Serial.println(currentRow);
  setRowState(currentRow -1, LOW);
  if (currentRow == NUMBER_OF_ROWS) {
    currentRow = 0;
  }
  Serial.print("Turn on row: "); Serial.println(currentRow+1);
  setRowState(currentRow, HIGH);
  currentRow++;
  delay(5000);
}

