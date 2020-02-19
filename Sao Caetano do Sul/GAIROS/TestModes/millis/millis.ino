int ExternalClock=0;

void setup() {
  Serial.begin(9600);
  delay(5000);
  ExternalClock=millis();
}

void loop() {
  Serial.println(millis()-ExternalClock);
}
