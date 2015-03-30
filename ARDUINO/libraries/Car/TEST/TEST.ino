#include <Car.h>
Car car(22, 24, 2, 3, 4, 5, 6);

void setup() {
  // put your setup code here, to run once:
attachInterrupt(0, onPulse, CHANGE);
car.turn(500);
  delay (1000);
car.turn(-200);
}

void loop() {
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
