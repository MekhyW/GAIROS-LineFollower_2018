#define buttonPinL 11
#define buttonPinR 12
int ExternalClock=0;

int WaitButtonPress(){
  while(digitalRead(buttonPinL)==HIGH || digitalRead(buttonPinR)==HIGH){  //flush pre-press
    delay(1);
  }
  while(digitalRead(buttonPinL)==LOW && digitalRead(buttonPinR)==LOW){
    delay(1);
    Serial.println("Awaiting press");
  }
  if(digitalRead(buttonPinL)==HIGH){
    while(digitalRead(buttonPinL)==HIGH){
      delay(1);
    }
    return 0;
  } else {
    while(digitalRead(buttonPinR)==HIGH){
      delay(1);
    }
    return 1;
  }
}
