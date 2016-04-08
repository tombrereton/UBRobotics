#include <Car.h> //Include the library

<<<<<<< HEAD
Car car(10, 11, 2, 3, 6, 7, 13); //Make a new instance of class 'car' called 'Car' with the following pins
=======
Car car(10, 11, 4, 5, 6, 7, 13); //Make a new instance of class 'car' called 'Car' with the following pins
>>>>>>> 9cb1823afaead44ad04604d05c8d4c5d3aa0aaa9

/*
Refer to Car.cpp in the library for the meaning of the numbers

This code is the bare minimum required to get the chassis moving, and a bit more. Use the code as reference to make your own commands.
*/

void setup() {
attachInterrupt(car.interruptPin[0], onPulse, CHANGE); //Attach interrupt pins. Even though we have set up interrupts for both tracks, simultaneously running two interrupts causes problems (workaround needed)
car.turn(500); //Turn the car anticlockwise by 500 ticks
  delay (3000); //Pause for 1000 ms (It's good practice to put in breaks between commands)
car.turn(-500); //Turn the car clockwise by 200 ticks
delay (2000);
car.move(100);
delay (3000);
car.stop();
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
