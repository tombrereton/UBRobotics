//Refer to Car.cpp and the TEST.ino notes

#ifndef Car_h
#define Car_h

#include "Arduino.h"

class Car
{
  public:
	  Car(int direction0, int direction1, int interrupt0, int interrupt1, int pwm0, int pwm1, int buzzer);
    void displayCounters();
    void turn(int ticks);
    void move(int speed);
    void stop();
	int counter[2];
	bool state[2];
	int interruptPin[2]; //Right, Left
  bool isRunning;
  private:
    int pwmPin[2]; //Right, Left
    int directionPin[2]; // Right, Left
    int buzzerPin; //PWM only
};

#endif
