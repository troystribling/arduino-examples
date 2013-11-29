// ldr_audio.ino
// use an ldr to control digital outtpt to which a speaker may be connected

const int outputPin     = 9; 		// Speaker connected to digital pin 9
const int sensorPin     = 0; 		// connect sensor to analog input 0

const int minDuration   = 1; 		// 1ms on, 1ms off (500 Hz)
const int maxDuration   = 10; 		// 10ms on, 10ms off (50 hz)

void setup() {
	pinMode(outputPin, OUTPUT); 	// enable output on the led pin
}

void loop() {
	int sensorReading = analogRead(sensorPin); 		        // read the analog input
	int rate = map(sensorReading, 200,800, minDuration, maxDuration);
	rate = constrain(rate, minDuration, maxDuration); 	  // constrain the value
	digitalWrite( outputPin, HIGH); 					            // set the LED on
	delay( rate); 										                    // wait duration dependent on light level
	digitalWrite( outputPin, LOW); 						            // set the LED off
	delay( rate);
}
