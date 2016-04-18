#include <Servo.h>
#include <Car.h> //Include the library

Car car(10, 11, 2, 3, 6, 7, 13, 255); //Make a new instance of class 'car' called 'Car' with the following pins
Servo leftarm, rightarm;
int leftarmPin = 9;
int rightarmPin = 13;
const int pingPin = 13;
float M_PI = 3.14159265359;

/*
Refer to Car.cpp in the library for the meaning of the numbers

This code is the bare minimum required to get the chassis moving, and a bit more. Use the code as reference to make your own commands.
*/

void setup() {
Serial.begin(9600);
leftarm.attach(leftarmPin);
rightarm.attach(rightarmPin);
attachInterrupt(car.interruptPin[0], onPulse, CHANGE); //Attach interrupt pins. Even though we have set up interrupts for both tracks, simultaneously running two interrupts causes problems (workaround needed)

//START

delay(1000);
leftclose(); //RETRACT ARMS
rightclose();

car.move(1300,250); //distance,speed
delay(5000);
car.move(1300,-250); //distance,speed
car.move(700,250); //distance,speed
car.gyroturn(-M_PI/2);

leftopen();
rightopen();

car.move(700,250); //distance,speed
rightclose();
car.gyroturn(-M_PI/2);
rightopen();
car.move(800,250); //distance,speed
rightclose();
car.gyroturn(-M_PI/2);
rightopen();
car.move(700,250); //distance,speed

leftclose();
rightclose();
car.turn(100);
car.move(1700,-250);
}

void loop(){
}

long readSensor() {


  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  return(cm);
  delay(100);
}
/*

Following snippet of code is neccesary for the interrupt to work properly. Always include in your sketches.

*/
long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void onPulse() {
  
  if ((car.state[0] == false) && (digitalRead(car.interruptPin[0]) == HIGH)){
    car.counter[0] ++;
    car.state[0] = true;
  }
  else if ((car.state[0] == true) && (digitalRead(car.interruptPin[0]) == LOW)){
    car.counter[0] ++;
    car.state[0] = false;
  }
}

void leftclose(){
  leftarm.write(175);
}
void leftopen(){
  leftarm.write(45);
}
void rightclose(){
  rightarm.write(45);
}
void rightopen(){
  rightarm.write(175);
}

