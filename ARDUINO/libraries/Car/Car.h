//Refer to Car.cpp and the TEST.ino notes

#ifndef Car_h
#define Car_h

#include "Arduino.h"

class Car
{
  public:
	  Car(int direction0, int direction1, int interrupt0, int interrupt1, int pwm0, int pwm1, int buzzer, int turningSpeed);
    void displayCounters();
    void turn(int ticks);
    void gyroturn(int radians);
    void move(int distance, int speed);
    void stop();
    int calibrategyro(); //RETURNS raw calib value
	int counter[2];
	bool state[2];
	int interruptPin[2]; //Right, Left
  bool isRunning;
  private:
    int turningSpeed;
    int pwmPin[2]; //Right, Left
    int directionPin[2]; // Right, Left
    int buzzerPin; //PWM only
    int rightangle = 0; //Raw value of a 90 degree turn CCW after calibration
};

#endif
