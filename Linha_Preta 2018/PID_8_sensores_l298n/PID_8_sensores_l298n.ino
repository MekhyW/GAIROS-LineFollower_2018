#include <QTRSensors.h>

//motor_A
int IN1 = 7 ;
int IN2 = 8 ;
int velocidadeA = 5;

//motor_B
int IN3 = 3 ;
int IN4 = 4 ;
int velocidadeB = 6;

int setpoint = 3500; // como são 8 sensores, variam de 0 a 7.000, onde 3.500 é a metade ou seja, robô simétrico sobre a linha

float KP = 0.3;   //valor ajustável
float KD = 7;     //valor ajustável
int erroAnterior = 0;

int velocidade = 255; 


QTRSensorsRC matrizSensores((unsigned char[]) {14, 15, 16, 17, 18, 19, 20, 21}, 8);  
// OITO SENSORES DE LUZ PARA SEGUIR A LINHA

void setup()
{
  pinMode(IN1, OUTPUT);   //motor esquerda
  pinMode(IN2, OUTPUT);   //motor esquerda
  pinMode(IN3, OUTPUT);   //motor direita
  pinMode(IN4, OUTPUT);   //motor direita
  pinMode(velocidadeA, OUTPUT);
  pinMode(velocidadeB, OUTPUT);
  

  // INICIA GIRO HORÁRIO PARA CALIBRAR SOBRE A LINHA
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(velocidadeA, 175);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(velocidadeB, 50);

  // CALIBRAÇÃO DOS SENSORES - 5 SEGUNDOS
  for (int i = 0; i < 250; i++)
  {
    Serial.println("CALIBRANDO");
    matrizSensores.calibrate();
    delay(20);
  }
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(velocidadeA, 127);
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(velocidadeB, 127);
  delay(2000);
}
// FIM DO SETUP
void loop()
{
  // LEITURA DOS SENSORES
  unsigned int arraySensores[8];
  int leituraSensores = matrizSensores.readLine(arraySensores);

  // CÁLCULO PD
  int erro = leituraSensores - setpoint;
  int sinalControlador = KP * erro + KD * (erro - erroAnterior);
  erroAnterior = erro;
  int novaVelocidadeMotor1 = velocidade + sinalControlador;
  int novaVelocidadeMotor2 = velocidade - sinalControlador;

  // CORREÇÃO DOS VALORES EXTREMOS DOS MOTORES
  if (novaVelocidadeMotor1 < 127)
    novaVelocidadeMotor1 = 127;
  if (novaVelocidadeMotor2 < 127)
    novaVelocidadeMotor2 = 127;

  if (novaVelocidadeMotor1 > 255)
    novaVelocidadeMotor1 = 255;
  if (novaVelocidadeMotor2 > 255)
    novaVelocidadeMotor2 = 255;

  // APLICAÇÃO DAS NOVAS VELOCIDADES DOS MOTORES VIA PWM
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(velocidadeA, novaVelocidadeMotor1);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(velocidadeB, novaVelocidadeMotor2);

} // FIM DO VOID LOOP
// FIM DO PROGRAMA

