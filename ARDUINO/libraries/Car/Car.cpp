#include "Car.h"
#include "Arduino.h"



Car::Car(int direction0, int direction1, int interrupt0, int interrupt1, int pwm0, int pwm1, int buzzer) {
  
directionPin[0] = direction0;
directionPin[1] = direction1;

interruptPin[0] = interrupt0;
interruptPin[1] = interrupt1;

pwmPin[0] = pwm0;
pwmPin[1] = pwm1;

pinMode(directionPin[0], OUTPUT);
pinMode(directionPin[1], OUTPUT);

pinMode(interruptPin[0], INPUT);
pinMode(interruptPin[1], INPUT);

//Set Encoder Pin States
digitalWrite(interruptPin[0], LOW);
digitalWrite(interruptPin[1], LOW);

//Test
buzzerPin = buzzer;
}



void Car::displayCounters() {
Serial.print("Left: ");
Serial.print(counter[1]);
Serial.print(", Right: ");
Serial.println(counter[0]);
}

void Car::turn(int ticks) {
	counter[0] = 0;

	if (ticks < 0){
		digitalWrite(directionPin[0], HIGH);
		digitalWrite(directionPin[1], LOW);
	}
	else if (ticks > 0){
		digitalWrite(directionPin[0], LOW);
		digitalWrite(directionPin[1], HIGH);
	}

	digitalWrite(pwmPin[0], HIGH);
	digitalWrite(pwmPin[1], HIGH);

	isRunning = true;

	while (counter[0] < abs(ticks)){
		delayMicroseconds(1);
	}

	digitalWrite(pwmPin[0], LOW);
	digitalWrite(pwmPin[1], LOW);
	Serial.print("End of Cycle.");
	isRunning = false;
	tone(buzzerPin, 440, 500);
}
