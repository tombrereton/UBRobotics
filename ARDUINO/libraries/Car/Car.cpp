#include "Car.h"
#include "Arduino.h"

/*
WIRING THE ROVER 5

1. Make sure the Motor Controller has power (VS and GND connected from battery)
2. Connect Left track to Channel 1, Right to Channel 2
3. Take any TWO of the Digital Pins from the Arduino and connect to the controller's CH1 Direction and CH2 Direction headers. Make note of the pin numbers.
4. Refer to Rover 5 manual online for schematic of its rotary encoders
5. Connect the Left and Right interrupt jumpers from the Rover 5 to CH1 and CH2 INT pins respectively. Also connect the respective ground pins.
6. Take any TWO analog out (PWM) pin from the Arduino and connect to the controller's CH1 PWM and CH2 PWM headers. Make note of the pin numbers
OPTIONAL: Connect a buzzer across any digital pin and GND

The pin numbers you noted will be declared when you make an instance of the Car class. For example:

	Car car(22, 24, 2, 3, 4, 5, 6);

Where the numbers correspond to the pins noted. The meaning of the pins are explained below, in that order
*/

Car::Car(int direction0, int direction1, int interrupt0, int interrupt1, int pwm0, int pwm1, int buzzer) {

/*
Variable Declarations

direction0 = Left Track Direction Pin DIGITAL
direction1 = Right Track Direction Pin DIGITAL

interrupt0 = Interrupt Pin for Left Track DIGITAL
interrupt1 = Interrupt Pin for Right Track DIGITAL

pwm0 = Left Track PWM Pin ANALOG OUT
pwm1 = Right Track PWM Pin ANALOG OUT

buzzer = Pin for diagnostic buzzer DIGITAL (If no buzzer just set to unused digital pin)
*/


//Now initialise all PIN NUMBERS to a variable

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
//Display encoder count to serial monitor
Serial.print("Left: ");
Serial.print(counter[1]);
Serial.print(", Right: ");
Serial.println(counter[0]);
}

void Car::turn(int ticks) { //Method for turning car. 'ticks' defines how many steps it will turn for (calibration required to convert to angle)
isRunning = true; //Car is running

counter[0] = 0; //Reset encoder counter

	if (ticks < 0){ //If number of steps is NEGATIVE, turn CLOCKWISE (set direction pins as required)
		digitalWrite(directionPin[0], HIGH);
		digitalWrite(directionPin[1], LOW);
	}
	else if (ticks > 0){ //If number of steps is POSITIVE, turn ANTICLOCKWISE (set direction pins as required)
		digitalWrite(directionPin[0], LOW);
		digitalWrite(directionPin[1], HIGH);
	}

	/*
	The following code turns the wheels at maximum speed. Experiment with analogWrite() at different speeds of each track to get the smoothest turning
	*/

	digitalWrite(pwmPin[0], HIGH);
	digitalWrite(pwmPin[1], HIGH);

	
	while (counter[0] < abs(ticks)){ //While the magnitude of ticks is below the required number of steps, stay in loop
		delayMicroseconds(1);
	}

	//Stop tracks, they have moved sufficient number of steps

	digitalWrite(pwmPin[0], LOW);
	digitalWrite(pwmPin[1], LOW);
	Serial.print("End of Cycle.");
	isRunning = false; //Important
}

void Car::move(int speed){ //Move forward at given speed between -255 and 255
	if (speed <= 0){ //If speed is negative, then REVERSE the direction
		digitalWrite(directionPin[0], HIGH);	
		digitalWrite(directionPin[1], HIGH);	
	}

	else { //If positive, make sure direction reverse pins are LOW on both tracks
		digitalWrite(directionPin[0], LOW);	
		digitalWrite(directionPin[1], LOW);	
	}

	if (abs(speed) > 255){ //If magnitude of speed is greater than allowed, cast it back to maximum speed
		speed = 255;
	}

	//Set PWM pins to given speed
	analogWrite(pwmPin[0], abs(speed));
	analogWrite(pwmPin[1], abs(speed));
}

void Car::stop(){ //Stop the car by bringing both PWM pins to LOW
	digitalWrite(pwmPin[0], LOW);
	digitalWrite(pwmPin[1], LOW);
}