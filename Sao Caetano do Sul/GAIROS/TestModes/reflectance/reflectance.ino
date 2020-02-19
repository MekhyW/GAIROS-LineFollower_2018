#include <QTRSensors.h>
#define IRpin 1
QTRSensorsRC matrizSensores((unsigned char[]) {14, 15, 16, 17, 18, 19, 20, 21}, 8);
QTRSensorsAnalog marcadorL((unsigned char[]) {A7}, 1);
QTRSensorsAnalog marcadorR((unsigned char[]) {A0}, 1);
unsigned int arraySensores[6];
unsigned int markerL[1];
unsigned int markerR[1];
int LineError=0;
bool OnMarker=false;
bool OnMarker_Last=false;

int GetError(){
  LineError = map(matrizSensores.readLine(arraySensores, QTR_EMITTERS_ON, 1), 0, 7000, -100, 100);
}

bool CheckMarker(){
  marcadorL.readCalibrated(markerL, QTR_EMITTERS_ON);
  marcadorR.readCalibrated(markerR, QTR_EMITTERS_ON);
  if(markerL[0]<250||markerR[0]<250){
    OnMarker=true;
  } else {
    OnMarker=false;
  }
  if(OnMarker=true && OnMarker_Last==false && abs(LineError)<2500){
    return true;
  } else {
    return false;
  }
  OnMarker_Last=OnMarker;
}

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing");
  pinMode(IRpin, OUTPUT);
  digitalWrite(IRpin, HIGH);
  for(int i=0; i<100; i++){
    matrizSensores.calibrate(QTR_EMITTERS_ON);
    marcadorL.calibrate(QTR_EMITTERS_ON);
    marcadorR.calibrate(QTR_EMITTERS_ON);
    Serial.println(i);
  }
}

void loop() {
  Serial.println(analogRead(14));
}
