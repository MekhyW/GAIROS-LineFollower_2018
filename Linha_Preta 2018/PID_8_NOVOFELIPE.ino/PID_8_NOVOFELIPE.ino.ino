#include <QTRSensors.h>
#include "MOTORES.h"
#include "PID.h"
QTRSensorsAnalog matrizSensores((unsigned char[]) {A0, A1, A2, A3, A4, A5, A6, A7}, 8); 
unsigned int arraySensores[8];

void setup() {
  Serial.begin(9600);
  //IR
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  //BOTAO
  pinMode(4, INPUT);
  Inicializar_Motores();
  Serial.println("APERTE PRA CALIBRAR");
  while(digitalRead(4)==0){
    delay(1);
  }
  delay(500);
  Serial.println("CALIBRANDO...");
  for (int i = 0; i < 50; i++) {
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
    MoverEsquerda(150);
    MoverDireita(150);
    matrizSensores.calibrate();
  }
  Parar_Motores();
  Serial.println("PRONTO");
  Serial.println("APERTE PRA CORRER");
  while(digitalRead(4)==0){
    delay(1);
  }
  delay(1000);
}

void loop() {
  CalculatePID(map(matrizSensores.readLine(arraySensores), 0, 7000, 100, -100));
  Serial.println(P);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);
  MoverEsquerda(150-abs(P)+PID_value);
  MoverDireita(150-abs(P)-PID_value);
}

