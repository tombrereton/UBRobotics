#include <MecanumRover.h>
MecanumRover rover(3,5,7,9,2,4,6,8,18,19,20,21,50,5); //1-4 Direction Pins, 5-8 PWM Pins, 9-12 Interrupt Pins, 13 Base Speed, 14 Correction Factor 

void setup() {
  // put your setup code here, to run once:

attachInterrupt(digitalPinToInterrupt(rover.interruptPin[0]), count0, CHANGE);
attachInterrupt(digitalPinToInterrupt(rover.interruptPin[1]), count1, CHANGE);
attachInterrupt(digitalPinToInterrupt(rover.interruptPin[2]), count2, CHANGE);
attachInterrupt(digitalPinToInterrupt(rover.interruptPin[3]), count3, CHANGE);

rover.move(3000);
}

void loop() {
  // put your main code here, to run repeatedly:

}

//Keep the following interrupt code simple and non-intensive for accurate operation

void count0(){
  rover.counter[0] ++;
}
void count1(){
  rover.counter[1] ++;
}
void count2(){
  rover.counter[2] ++;
}
void count3(){
  rover.counter[3] ++;
}
