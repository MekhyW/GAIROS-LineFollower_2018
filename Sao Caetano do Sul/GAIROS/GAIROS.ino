#define MappingRunTime 50000
int Track[500]={0};
int TrackLenght=0;
int Position=0;
#include "buttons.h"
#include "PID.h"
#include "readers.h"
#include "drive.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing");
  pinMode(IRpin, OUTPUT);
  digitalWrite(IRpin, HIGH);
  pinMode(buttonPinL, INPUT);
  pinMode(buttonPinR, INPUT);
  Drive_Initialize();
  delay(2000);
  for(int i=0; i<80; i++){
    Serial.println("Calibrating");
    matrizSensores.calibrate(QTR_EMITTERS_ON);
    marcadorL.calibrate(QTR_EMITTERS_ON);
    marcadorR.calibrate(QTR_EMITTERS_ON);
    delay(1);
  }
  Drive_Stop();
}

void loop() {
  Serial.println("PressToStart");
  if(WaitButtonPress()==0){
    MappingRun();
  } else {
    TrueRun();
  }
}


void MappingRun(){
  ExternalClock=millis();
  Drive_Begin(60);
  while((millis()-ExternalClock)<MappingRunTime && digitalRead(buttonPinL)==LOW && digitalRead(buttonPinR)==LOW){
    GetError();
    CalculatePID(LineError);
    Drive(40+PID_value, 40-PID_value);
    if(CheckMarker()==true){
      Position++;
    }
    if(Track[Position]<LineError){
       Track[Position]=LineError;
    }
    Serial.println(LineError);
    delay(10);
  }
  Drive_Stop();
  TrackLenght=Position;
  Position=0;
}


void TrueRun(){
  ExternalClock=millis();
  Drive_Begin(200);
  while((Position<TrackLenght || (Position==TrackLenght && abs(P)>250)) && digitalRead(buttonPinL)==LOW && digitalRead(buttonPinR)==LOW){
    CalculatePID(GetError());
    Drive(200-abs(Track[Position]*2)+PID_value, 200-abs(Track[Position]*2)-PID_value);
    if(CheckMarker()==true){
      Position++;
    }
    Serial.println("TrueRun");
  }
  Drive_Finish(200);
  Position=0;
}
