#include "Arduino.h"
#include "MecanumRover.h"

MecanumRover::MecanumRover(int dir0, int dir1, int dir2, int dir3, int pwm0, int pwm1, int pwm2, int pwm3, int int0, int int1, int int2, int int3, int base, float factor){
  directionPin[0] = dir0; //Initialise direction pins
  directionPin[1] = dir1;
  directionPin[2] = dir2;
  directionPin[3] = dir3;

  pwmPin[0] = pwm0; //Initialise PWM pins
  pwmPin[1] = pwm1; 
  pwmPin[2] = pwm2; 
  pwmPin[3] = pwm3;

  interruptPin[0] = int0; //Initialise interrupt pins
  interruptPin[1] = int1;
  interruptPin[2] = int2;
  interruptPin[3] = int3;

  baseSpeed = base; //Initialise base speed

  correctionFactor = factor; //Initialise correction factor

  for (int i = 0; i < 4; i ++){
    pinMode(directionPin[i], OUTPUT); //DirectionPin is a digital output pin
    pinMode(interruptPin[i], INPUT);  //InterruptPin is an input
    digitalWrite(interruptPin[i], HIGH); //A pullup resistor to protect Arduino as interrupt pin is 5v logic
  }
}

void MecanumRover::adjustSpeed(){ //Change the speed of the 4 wheels according to the average rotational displacement of all 4 wheels
  int averageCount = (counter[0] + counter[1] + counter [2] + counter[3]) / 4;  //Average rotational displacement of all 4 wheels

  for (int i = 0; i < 4; i ++){
    int correction = averageCount - counter[i]; //Difference of current wheel from average
    int adjusted = baseSpeed + correction * correctionFactor; //Change PWM level according to difference

    analogWrite(pwmPin[i], adjusted); //Write to PWM pin
  }
}

void MecanumRover::move(int ticks){ //Move forward/backward a number of ticks
  int startTime = millis();

  for (int i = 0; i < 4; i ++){
    analogWrite(pwmPin[i], baseSpeed);
    counter[i] = 0; //Initialise encoder count
  }

  while(counter[0] + counter[1] + counter[2] + counter[3] < ticks * 4){ //While total sum of encoders for all wheels is less than the desired distance x4

    for (int i = 0; i < 4; i ++){ //For all 4 wheels
      if (counter[i] >= abs(ticks)){ //If the wheel has turned as much as the magnitude of the required ticks
        analogWrite(pwmPin[i], 0); //Off
      }
    }
    adjustSpeed();
  }  
    
  for (int i = 0; i < 4; i ++){ //For all 4 wheels
    analogWrite(pwmPin[i], 0); //Off
  }

  float endTime = (millis() - startTime) / 1000;
  //Print results
  Serial.begin(9600);
  Serial.print("Encoder readings: ");
  for (int i = 0; i < 4; i ++){
    Serial.print(counter[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("Time of movement sequence: ");
  Serial.print(endTime);
  Serial.println(" seconds");
}