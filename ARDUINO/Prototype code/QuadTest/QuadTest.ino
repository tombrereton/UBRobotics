#include <Servo.h>
#include <MecanumRover.h>
#include <SPI.h>
#include <HCMAX7219.h>
#include <NewPing.h>

int leftArm = 40; //Pin numbers for seashell arms
int rightArm = 41;
Servo arm;
int bias = 30; //Arm will lower less with more bias

int rightAngle = 83;
int greenButton = 14; //Pin of green button for mode selection
int buzzerPin = 49; //Pin of buzzer
MecanumRover rover(3,5,7,9,
                   2,4,6,8,
                   18,19,20,21,
                   0,1,2,3,
                   50,4,49); //1-4 Direction Pins, 5-8 PWM Pins, 9-12 Interrupt Pins, 13-16 Current Read Pins, 15 Base Speed, 16 Correction Factor, 17 Buzzer Pin 

NewPing frontSensor(13, 12, 100);
NewPing rearSensor(31, 32, 100);

void setup(){
  // put your setup code here, to run once:
Serial.begin(9600);
//pinMode(greenButton, INPUT);
attachInterrupt(digitalPinToInterrupt(rover.interruptPin[0]), count0, CHANGE);
attachInterrupt(digitalPinToInterrupt(rover.interruptPin[1]), count1, CHANGE);
attachInterrupt(digitalPinToInterrupt(rover.interruptPin[2]), count2, CHANGE);
attachInterrupt(digitalPinToInterrupt(rover.interruptPin[3]), count3, CHANGE);
//rover.testHardware();

HCMAX7219 HCMAX7219(10);
Serial.println(digitalRead(greenButton));

leftClose();
rightClose();

  if (digitalRead(greenButton) == HIGH){ //Check if GREEN BUTTON was pressed
    HCMAX7219.Clear();
    HCMAX7219.print7Seg("GREEN", 8); //Green mode
    HCMAX7219.Refresh();
    delay(1000);
  }
  else {
    HCMAX7219.Clear();
    HCMAX7219.print7Seg("PURPLE", 8); //Purple mode
    HCMAX7219.Refresh(); 
    delay(1000);
    eurobotPurple();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}

//Keep the following interrupt code simple and non-intensive for accurate operation

void count0(){
  rover.counter[0] ++;
  rover.encoderChangeTime[0] = millis();
}
void count1(){
  rover.counter[1] ++;
  rover.encoderChangeTime[1] = millis();
}
void count2(){
  rover.counter[2] ++;
  rover.encoderChangeTime[2] = millis();
}
void count3(){
  rover.counter[3] ++;
  rover.encoderChangeTime[3] = millis();
}

void leftClose(){
  arm.attach(leftArm);
    for (int pos = 180; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      arm.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  arm.detach();
}

void leftOpen(){
  arm.attach(leftArm);
    for (int pos = 0; pos <= 180 - bias; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      arm.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  arm.detach();
}

void rightClose(){
  arm.attach(rightArm);
    for (int pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      arm.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  arm.detach();
}

void rightOpen(){
  arm.attach(rightArm);
    for (int pos = 180; pos >= 0 + bias; pos -= 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      arm.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  arm.detach();
}

void eurobotPurple(){
  rover.strafe(-100);
  rover.turn(rightAngle);
  rover.move(400,frontSensor,rearSensor);  
  rover.turn(-rightAngle);
  rover.move(500,frontSensor,rearSensor);
  rover.turn(-rightAngle);
  rover.move(500,frontSensor,rearSensor);
  leftOpen();
  rightOpen();
}

