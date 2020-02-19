void setup() {
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(digitalRead(11));
}
