int dirPin[4] = {3, 5, 7, 9};
int pwmPin[4] = {2, 4, 6, 8};
int interruptPin[4] = {18, 19, 20, 21};
int counter[4] = {0, 0, 0, 0};

int baseSpeed = 50;
int correctionFactor = 5; //Gain of correction when encoders are not equal to each other

void setup() {
  // put your setup code here, to run once:

for (int i = 0; i < 4; i ++){
  pinMode(dirPin[i], OUTPUT);
  pinMode(interruptPin[i], INPUT);
  digitalWrite(interruptPin[i], HIGH);
}
Serial.begin(9600);

attachInterrupt(digitalPinToInterrupt(interruptPin[0]), count0, CHANGE);
attachInterrupt(digitalPinToInterrupt(interruptPin[1]), count1, CHANGE);
attachInterrupt(digitalPinToInterrupt(interruptPin[2]), count2, CHANGE);
attachInterrupt(digitalPinToInterrupt(interruptPin[3]), count3, CHANGE);

  for (int i = 0; i < 4; i++){
    analogWrite(pwmPin[i], baseSpeed);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  printCount();

  int averageCount = (counter[0] + counter[1] + counter [2] + counter[3]) / 4;

  for (int i = 0; i < 4; i ++){
    int correction = averageCount - counter[i];
    int adjusted = baseSpeed + correction * correctionFactor;
    
    analogWrite(pwmPin[i], adjusted);
  }
}

void count0(){
  counter[0] ++;
}
void count1(){
  counter[1] ++;
}
void count2(){
  counter[2] ++;
}
void count3(){
  counter[3] ++;
}

void printCount(){

  for (int i = 0; i < 4; i ++){
    Serial.print(counter[i]);
    Serial.print(" ");
  }
  Serial.println();
}

