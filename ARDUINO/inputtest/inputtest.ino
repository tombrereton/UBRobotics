int buzzerPin = 10;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(11,OUTPUT);
setPwmFrequency(buzzerPin,1);
}

void loop() {
  // put your main code here, to run repeatedly:
int value = analogRead(A0);
Serial.println(value);
//analogWrite(11,value/4);

  if ((analogRead(A0) >= 1000)&&(analogRead(A0) <= 1024)){
    tone(buzzerPin,262);
  }
  else if ((analogRead(A0) >= 300)&&(analogRead(A0) <= 999)){
    tone(buzzerPin,294);
  }
  else if ((analogRead(A0) >= 75)&&(analogRead(A0) <= 110)){
    tone(buzzerPin,330);
  }
  else if ((analogRead(A0) >= 66)&&(analogRead(A0) <= 74)){
    tone(buzzerPin,349);
  }
  else if ((analogRead(A0) >= 55)&&(analogRead(A0) <= 65)){
    tone(buzzerPin,392);
  }
  else if ((analogRead(A0) >= 30)&&(analogRead(A0) <= 40)){
    tone(buzzerPin,440);
  }
  else if ((analogRead(A0) >= 10)&&(analogRead(A0) <= 25)){
    tone(buzzerPin,494);
  }
  else {
    noTone(buzzerPin);
  }
}

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
