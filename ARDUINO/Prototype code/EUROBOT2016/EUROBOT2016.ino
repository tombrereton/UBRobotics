#include <Servo.h>
#include <Car.h> //Include the library

Car car(10, 11, 2, 3, 6, 7, 13, 255); //Make a new instance of class 'car' called 'Car' with the following pins

/*
Refer to Car.cpp in the library for the meaning of the numbers

This code is the bare minimum required to get the chassis moving, and a bit more. Use the code as reference to make your own commands.
*/

void setup() {
Serial.begin(9600);

attachInterrupt(car.interruptPin[0], onPulse, CHANGE); //Attach interrupt pins. Even though we have set up interrupts for both tracks, simultaneously running two interrupts causes problems (workaround needed)
Servo myservo;
myservo.attach(9);

//START
delay(1000);
myservo.write(175);

car.move(1300,250); //distance,speed
car.move(1300,-250); //distance,speed

car.move(650,250); //distance,speed
car.gyroturn(-1.57);
myservo.write(45);
car.move(650,250); //distance,speed
car.gyroturn(-1.57);
car.move(650,250); //distance,speed
car.gyroturn(-1.57);
car.move(650,250); //distance,speed
myservo.write(175);

}

void loop() {
}

/*

Following snippet of code is neccesary for the interrupt to work properly. Always include in your sketches.

*/


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
