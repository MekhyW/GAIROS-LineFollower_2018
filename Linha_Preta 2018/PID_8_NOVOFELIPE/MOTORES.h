void Parar_Motores(){
  analogWrite(5, 0);
  analogWrite(9, 0);
}

void Inicializar_Motores(){
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  Parar_Motores();
}

void MoverEsquerda(int vel){
  analogWrite(5, constrain(vel, 0, 255));
}

void MoverDireita(int vel){
  analogWrite(9, constrain(vel, 0, 255));
}

