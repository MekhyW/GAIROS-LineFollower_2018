#define motorL 3
#define motorLdirA 4
#define motorLdirB 2
#define motorR 6
#define motorRdirA 7
#define motorRdirB 5

void Drive_Stop(){
  digitalWrite(motorLdirA, HIGH);
  digitalWrite(motorLdirB, HIGH);
  digitalWrite(motorRdirA, HIGH);
  digitalWrite(motorRdirB, HIGH);
  analogWrite(motorL, 0);
  analogWrite(motorR, 0);
}

void Drive_Initialize(){
  pinMode(motorL, OUTPUT);
  pinMode(motorLdirA, OUTPUT);
  pinMode(motorLdirB, OUTPUT);
  pinMode(motorR, OUTPUT);
  pinMode(motorRdirA, OUTPUT);
  pinMode(motorRdirB, OUTPUT);
  Drive_Stop();
}

void Drive_Begin(float vel){
  digitalWrite(motorLdirA, LOW);
  digitalWrite(motorLdirB, HIGH);
  digitalWrite(motorRdirA, HIGH);
  digitalWrite(motorRdirB, LOW);
  float progVel=0;
  while(progVel<vel){
    analogWrite(motorL, progVel);
    analogWrite(motorR, progVel);
    delay(1);
    progVel+=(vel/200);
  }
}

void Drive_Finish(float currvel){
  digitalWrite(motorLdirA, LOW);
  digitalWrite(motorLdirB, HIGH);
  digitalWrite(motorRdirA, HIGH);
  digitalWrite(motorRdirB, LOW);
  float progVel=currvel;
  while(progVel>0){
    analogWrite(motorL, progVel);
    analogWrite(motorR, progVel);
    delay(1);
    progVel-=(currvel/500);
  }
}

void Drive(int velL, int velR){
  digitalWrite(motorLdirA, LOW);
  digitalWrite(motorLdirB, HIGH);
  digitalWrite(motorRdirA, HIGH);
  digitalWrite(motorRdirB, LOW);
  analogWrite(motorL, constrain(velL, 0, 255));
  analogWrite(motorR, constrain(velR, 0, 255));
}

void Spin(int vel){
  digitalWrite(motorLdirA, LOW);
  digitalWrite(motorLdirB, HIGH);
  digitalWrite(motorRdirA, LOW);
  digitalWrite(motorRdirB, HIGH);
  analogWrite(motorL, vel);
  analogWrite(motorR, vel);
}
