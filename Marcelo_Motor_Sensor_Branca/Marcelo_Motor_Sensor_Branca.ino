int pinLed = 13;
int pinSe = A2;
int pinSd = A3;
const int motor1 = 5; //velocidade motor 1 - de 0 a 255
const int motor2 = 6; //velocidade motor 2 - de 0 a 255
const int dir1 = 7; //direcao do motor 1 - HIGH ou LOW
const int dir2 = 8; //direcao do motor 2 - HIGH ou LOW
int limite = 700;
bool linhabranca = true;
void setup() {
  Serial.begin(9600);
  Serial.println("Robo Falcon Conectado!");
  Serial.println("Salles");
  pinMode(pinSe, INPUT);
  pinMode(pinSd, INPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
}
void loop() {
  int se = analogRead(pinSe);// 0 (branco) - 1023 (preto)
  int sd = analogRead(pinSd);

  if (linhabranca == true) {
    se = 1023 - se;
    sd = 1023 - sd;
    limite = 400; // Linha Branca
      }else{
          limite = 700; //Linha Preta
      }
  Serial.print(se);
  Serial.print(" ");
  Serial.println(sd);
  Serial.println();

  // Os dois sensores na linha = Frente
  if (se > limite && sd > limite) {
    digitalWrite(dir1, HIGH); //SENTIDO DE ROTACAO
    digitalWrite(dir2, HIGH);
    analogWrite(motor1, 150); //VELOCIDADE
    analogWrite(motor2, 150);
  }
  // Sensor Esquerda no Branco
  //Sensor Direito no Preto = Direita
  if (se < limite && sd > limite) {
    digitalWrite(dir1, HIGH); //SENTIDO DE ROTACAO
    digitalWrite(dir2, HIGH);
    analogWrite(motor1, 143); //VELOCIDADE
    analogWrite(motor2, 0);
  }
   // Sensor Esquerda no Preto
  //Sensor Direito no Branco = Direita
  if (se > limite && sd < limite) {
    digitalWrite(dir1, HIGH); //SENTIDO DE ROTACAO
    digitalWrite(dir2, HIGH);
    analogWrite(motor1, 0); //VELOCIDADE
    analogWrite(motor2, 143);
  }
  else{
    digitalWrite(pinLed, LOW);
  }
 }//FIM DO LOOP()
