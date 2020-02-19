#include <QTRSensors.h>
#define IRpin 8
QTRSensorsAnalog matrizSensores((unsigned char[]) {A6, A5, A4, A3, A2, A1}, 6);
QTRSensorsAnalog marcadorL((unsigned char[]) {A7}, 1);
QTRSensorsAnalog marcadorR((unsigned char[]) {A0}, 1);
unsigned int arraySensores[6];
unsigned int markerL[1];
unsigned int markerR[1];
int LineError=0;
bool OnMarker=false;
bool OnMarker_Last=false;

int GetError(){
  LineError = map(matrizSensores.readLine(arraySensores, QTR_EMITTERS_ON, 1), 0, 5000, -100, 100);
}

bool CheckMarker(){
  marcadorL.readCalibrated(markerL, QTR_EMITTERS_ON);
  marcadorR.readCalibrated(markerR, QTR_EMITTERS_ON);
  if(markerL[0]<250 || markerR[0]<250){
    OnMarker=true;
  } else {
    OnMarker=false;
  }
  if(OnMarker==true && OnMarker_Last==false && abs(LineError)<100){
    return true;
  } else {
    return false;
  }
  OnMarker_Last=OnMarker;
}
