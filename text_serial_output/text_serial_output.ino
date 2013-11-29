// text_serial_output.ino
// write text through serial port

char chrValue = 65;
byte byteValue = 65;
int intValue = 65;
float floatValue = 65.0;

void setup() {
	Serial.begin(9600);
}

void loop() {
	Serial.print(" chrValue: ");
	Serial.print(chrValue);
	Serial.print(' ');
	Serial.write(chrValue);
	Serial.print(' ');
	Serial.print(chrValue, DEC);
	Serial.print(' ');
	Serial.print(chrValue, HEX);
	Serial.print(' ');
	Serial.print(chrValue, OCT);
	Serial.print(' ');
	Serial.println(chrValue, BIN);

	Serial.print(" byteValue: ");
	Serial.print(byteValue);
	Serial.print(' ');
	Serial.write(byteValue);
	Serial.print(' ');
	Serial.print(byteValue, DEC);
	Serial.print(' ');
	Serial.print(byteValue, HEX);
	Serial.print(' ');
	Serial.print(byteValue, OCT);
	Serial.print(' ');
	Serial.println(byteValue, BIN);

	Serial.print(" intValue: ");
	Serial.print(intValue);
	Serial.print(' ');
	Serial.write(intValue);
	Serial.print(' ');
	Serial.print(intValue, DEC);
	Serial.print(' ');
	Serial.print(intValue, HEX);
	Serial.print(' ');
	Serial.print(intValue, OCT);
	Serial.print(' ');
	Serial.println(intValue, BIN);

	Serial.print(" floatValue: ");
	Serial.println(floatValue);

	Serial.println();

	chrValue++;
	byteValue++;
	intValue++;
	floatValue++;

	delay(1000);
}


