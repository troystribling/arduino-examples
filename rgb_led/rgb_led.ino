// rgb_led.ino

const int redPin    = 3;
const int greenPin  = 5;
const int bluePin   = 6;

int hue = 0;
int red, blue, green;

void setup() {
}

void hueToRGB() {
  int brightness = 125;
  unsigned int scaledHue = (hue * 6);
  unsigned int segment  = scaledHue / 256;
  unsigned int segmentOffset = scaledHue - (segment * 256);

  unsigned int complememt = 255;
  unsigned int prev = 255 - (brightness * (255 - segmentOffset)) / 256;
  unsigned int next = 255 - (brightness * segmentOffset) / 256;
  brightness = 255 - brightness;

  switch (segmentOffset) {
    case 0:
      red = brightness;
      green = next;
      blue = complememt;
    break;
    case 1:
      red = prev;
      green = brightness;
      blue = complememt;
    break;
    case 2:
      red = complememt;
      green = brightness;
      blue = next;
    break;
    case 3:
      red = complememt;
      green = prev;
      blue = brightness;
    break;
    case 4:
      red = next;
      green = complememt;
      blue = brightness;
    break;
    case 5:
    default:
      red = brightness;
      green = complememt;
      blue = prev;
    break;
  }
}

void loop() {
  hueToRGB();
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  hue++;
  if (hue > 255) {
    hue = 0;
  }
  delay(10);
}

