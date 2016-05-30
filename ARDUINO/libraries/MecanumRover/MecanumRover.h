#ifndef MecanumRover_h
#define MecanumRover_h

#include "Arduino.h"

class MecanumRover
{
  public:
    MecanumRover(int dir0, int dir1, int dir2, int dir3, int pwm0, int pwm1, int pwm2, int pwm3, int int0, int int1, int int2, int int3, int base, float factor); //Constructor
    void adjustSpeed();
    void move(int ticks);
    float correctionFactor; //Linear correction gain of wheels
    int baseSpeed; //Base speed of movement
	int interruptPin[4]; //Interrupt pins of Arduino for 4 wheels
    int counter[4]; //Counter of encoder
  private:
    int pwmPin[4]; //PWM pins of controller for speed of all 4 wheels
    int directionPin[4]; //Digital pins of controller for direction for 4 wheels
};

#endif