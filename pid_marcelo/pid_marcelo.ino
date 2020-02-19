////////SEGUIDOR DE LINHA 2018/////////
#include <QTRSensors.h>


const int btn1 = 0;


int cruzeiro = 120;

int pwma = 6;
int ain2 = 4;
int ain1 = 3;
int pwmb = 5;
int bin2 = 7;
int bin1 = 8;

int P = 0;
int I = 0;
int D = 0;
int LAST = 0;
float vel;

#define NUM_SENSORS   8     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   10     // emitter is controlled by digital pin 2

// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
QTRSensorsRC qtrrc((unsigned char[]) {14, 15, 16, 17, 18, 19, 20, 21},NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

unsigned int position = 0;

void setup()
{

  pinMode(btn1, INPUT);

  pinMode(pwma, OUTPUT);
  pinMode(ain1, OUTPUT);
  pinMode(ain2, OUTPUT);
  pinMode(pwmb, OUTPUT);
  pinMode(bin1, OUTPUT);
  pinMode(bin2, OUTPUT);

  pinMode(13, OUTPUT);

  //Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  delay(1500);
  digitalWrite(13, HIGH);
  for (int j = 0; j < 250; j++)
  {

    qtrrc.calibrate();

  }

  digitalWrite(13, LOW);

  digitalWrite(ain1, LOW);
  digitalWrite(ain2, HIGH);

  digitalWrite(bin1, HIGH);
  digitalWrite(bin2, LOW);

  analogWrite(pwma, 0);
  analogWrite(pwmb, 0);
}


void loop()
{

  if (digitalRead(btn1) == 1) {

    for (;;)
    {

      qtrrc.read(sensorValues);

      position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0); // 0 = LINHA PRETA   //  1 = LINHA BRANCA


      P = ((position) - (3500)); /// ERROR
      /////FREIOS PARA CURVA/////
      if (P < -3500) {
        analogWrite(pwma, 40); // MOTOR DIREITO
        analogWrite(pwmb, 80); // MOTOR ESQUERDO
        digitalWrite(ain1, LOW);
        digitalWrite(ain2, HIGH);
        digitalWrite(bin1, LOW);
        digitalWrite(bin2, HIGH);

      } else if (P > 3500) {
        analogWrite(pwma, 80); // MOTOR DIREITO
        analogWrite(pwmb, 40); // MOTOR ESQUERDO
        digitalWrite(ain1, HIGH);
        digitalWrite(ain2, LOW);
        digitalWrite(bin1, HIGH);
        digitalWrite(bin2, LOW);

      }

      else {
        D = (P - LAST); /// ERRO MENOS ERRO ANTERIOR , DERIVATIVO
        I = (P + LAST); //ERRO MAIS ERRO ANTERIOR , INTEGRAL


       vel = (P * 0.0005) + (D * 0) + (I * 0); //para velocidade de 120   

       // vel=(P*0.455) + (D*0.6879) + (I*0.005698); //para velocidade de 200

        //vel=(P*0.55)+(D*0.68)+(I*0); // para velocidade de 230


        if (vel > cruzeiro) vel = cruzeiro;
        if (vel < -cruzeiro) vel = -cruzeiro;

        analogWrite(pwma, cruzeiro - vel); // VELOCIDADE PARA MOTOR DIREITO
        analogWrite(pwmb, cruzeiro + vel); //  VELOCIDADE PARA MOTOR ESQUERDO

        digitalWrite(ain1, LOW);  ///FRENTE
        digitalWrite(ain2, HIGH);
        digitalWrite(bin1, HIGH); ///FRENTE
        digitalWrite(bin2, LOW);

        LAST = P;
      }
    }
  }
}


