// dot_matrix_led_display_flash_columns.ino
// Flash the red/orange columns on the Lite On two color 5x7 LED dot matrix
// http://www.jameco.com/webapp/wcs/stores/servlet/ProductDisplay?langId=-1&storeId=10001&catalogId=10001&productId=1955159

const int columnPins[] = {2, 3, 4, 5, 6};
const int rowPins[] = {9, 10, 11, 12, 15, 16, 17};

const int NUMBER_OF_COLUMNS = sizeof(columnPins)/sizeof(columnPins[0]);
const int NUMBER_OF_ROWS = sizeof(rowPins)/sizeof(rowPins[0]);

int currentColumn = 1;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUMBER_OF_ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
  }
  for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {
    pinMode(columnPins[j], OUTPUT);
  }
  setDisplayState(HIGH);
  setColumnState(currentColumn - 1, LOW);
  delay(5000);
}

void setDisplayState(int state) {
  for (int i = 0; i < NUMBER_OF_ROWS; i++) {
    digitalWrite(rowPins[i], HIGH);
  }
  for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
    digitalWrite(columnPins[i], state);
  }
}

void setColumnState(int column, int state) {
  digitalWrite(columnPins[column], state);
}

void loop() {
  Serial.print("Turn off column: "); Serial.println(currentColumn);
  setColumnState(currentColumn - 1, HIGH);
  if (currentColumn == NUMBER_OF_COLUMNS) {
    currentColumn = 0;
  }
  Serial.print("Turn on column: "); Serial.println(currentColumn+1);
  setColumnState(currentColumn, LOW);
  currentColumn++;
  delay(5000);
}
