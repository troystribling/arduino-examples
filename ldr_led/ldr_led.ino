// ldr_led.ino
// use an ldr to control the LED blink rate

const int ledPin        = 13;   	// LED connected to digital pin 13
const int sensorPin     = 0;     	// connect sensor to analog input 0

const int minDuration   = 100;   	// minimum wait between blinks
const int maxDuration   = 1000;  	// maximum wait between blinks

void setup() {
	pinMode(ledPin, OUTPUT); 	// enable output on the led pin
	Serial.begin(9600); 			// initialize Serial
}

void loop() {
	int rate = analogRead(sensorPin); 										// read the analog input
	rate = map(rate, 200, 800, minDuration, maxDuration);	// convert to blink rate
	rate = constrain(rate, minDuration, maxDuration); 		// constrain the value
	Serial.println(rate);																	// print rate to serial port
	digitalWrite(ledPin, HIGH); 													// set the LED off delay( rate);
	delay(rate); 																					// wait duration dependent on light level
	digitalWrite(ledPin, LOW); 														// set the LED off delay( rate);
	delay(rate); 																					// wait duration dependent on light level
}

