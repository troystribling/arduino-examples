// dot_matrix_led_display_scan_leds.ino
// scan the red/orange leds on the Lite On two color 5x7 LED dot matrix
// http://www.jameco.com/webapp/wcs/stores/servlet/ProductDisplay?langId=-1&storeId=10001&catalogId=10001&productId=1955159

const int columnPins[] = {2, 3, 4, 5, 6};
const int rowPins[] = {9, 10, 11, 12, 15, 16, 17};

const int NUMBER_OF_COLUMNS = sizeof(columnPins)/sizeof(columnPins[0]);
const int NUMBER_OF_ROWS = sizeof(rowPins)/sizeof(rowPins[0]);

int pixel   = 0;
int column  = 0;
int row     = 0;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUMBER_OF_ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
  }
  for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {
    pinMode(columnPins[j], OUTPUT);
    digitalWrite(columnPins[j], HIGH);
  }
}

void loop() {
  if (pixel > NUMBER_OF_ROWS * NUMBER_OF_COLUMNS - 1) {
    pixel = 0;
  }

  if (NUMBER_OF_ROWS > NUMBER_OF_COLUMNS) {
    row = pixel / NUMBER_OF_ROWS;
    column = row % NUMBER_OF_ROWS;
  } else {
    column = pixel / NUMBER_OF_COLUMNS;
    row = column % NUMBER_OF_COLUMNS;
  }

  for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {
    digitalWrite(columnPins[j], LOW);
    for (int i = 0; i < NUMBER_OF_ROWS; i++) {
     if (column > j) {
        digitalWrite(rowPins[i], HIGH);
      } else if (column == j && row >= i) {
        digitalWrite(rowPins[i], HIGH);
      } else {
        digitalWrite(columnPins[j], LOW);
      }
      delayMicroseconds(300);
      digitalWrite(rowPins[i], LOW);
    }
    digitalWrite(columnPins[j], HIGH);
  }
  pixel++;
}


