// dot_matrix_led_display_image.ino
// Flash the red/orange leds on the Lite On two color 5x7 LED dot matrix
// http://www.jameco.com/webapp/wcs/stores/servlet/ProductDisplay?langId=-1&storeId=10001&catalogId=10001&productId=1955159

const int columnPins[] = {2, 3, 4, 5, 6};
const int rowPins[] = {9, 10, 11, 12, 15, 16, 17};

const int NUMBER_OF_COLUMNS = sizeof(columnPins)/sizeof(columnPins[0]);
const int NUMBER_OF_ROWS = sizeof(rowPins)/sizeof(rowPins[0]);

byte image1[] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B00000,
  B00000,
  B00000,
};

byte image2[] = {
  B00000,
  B10000,
  B01000,
  B00100,
  B00010,
  B00001,
  B00000,
};

byte image3[] = {
  B00000,
  B00001,
  B00010,
  B00100,
  B01000,
  B10000,
  B00000,
};

byte image4[] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
};

void setup() {
  for (int i = 0; i < NUMBER_OF_ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
  }
  for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {
    pinMode(columnPins[j], OUTPUT);
    digitalWrite(columnPins[j], HIGH);
  }
}

void show(byte* image, unsigned long duration) {
  unsigned long start = millis();
  while(start + duration > millis()) {
    for (int i = 0; i < NUMBER_OF_ROWS; i++) {
      digitalWrite(rowPins[i], HIGH);
      for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {
        boolean pixel = bitRead(image[i], j);
        if (pixel == 1) {
          digitalWrite(columnPins[j], LOW);
        }
        delayMicroseconds(300);
        digitalWrite(columnPins[j], HIGH);
      }
      digitalWrite(rowPins[i], LOW);
    }
  }
}

void loop() {
  show(image1, 80);
  show(image2, 80);
  show(image3, 80);
  show(image4, 80);
}

