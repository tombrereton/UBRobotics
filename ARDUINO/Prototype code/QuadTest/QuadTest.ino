#include <MecanumRover.h>
#include <SPI.h>
#include <HCMAX7219.h>

int greenButton = 14; //Pin of green button for mode selection
MecanumRover rover(3,5,7,9,2,4,6,8,18,19,20,21,0,1,2,3,30,5); //1-4 Direction Pins, 5-8 PWM Pins, 9-12 Interrupt Pins, 13-16 Current Read Pins, 15 Base Speed, 16 Correction Factor 

void setup() {
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
if (digitalRead(greenButton) == HIGH){
  HCMAX7219.Clear();
  HCMAX7219.print7Seg("GREEN", 8); //Green mode
  HCMAX7219.Refresh();
  delay(1000);
}
else {
  HCMAX7219.Clear();
  HCMAX7219.print7Seg("YELLOW", 8); //Yellow mode
  HCMAX7219.Refresh(); 
  delay(1000);
}

rover.move(3000);
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
