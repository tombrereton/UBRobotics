int const memory = 10;
int peak = 0;
int delayRecord[memory];

void setup() {
analogReference(INTERNAL);
Serial.begin(57600);
setPwmFrequency(6,1);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(6,analogRead(A0) / 4);

  //LAGGER
  /*
  for (int i = 0; i < memory; i ++){
    delayRecord[i] = analogRead(A0);
  }
  
  for (int i = 0; i < memory; i ++){
    analogWrite(6,delayRecord[i]/4);
  }
  */
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
