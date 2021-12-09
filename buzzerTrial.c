int buzzer=11;
void setup() {

}
void loop() {
  tone(buzzer, 450);
  delay(1000);
  noTone(buzzer);
  delay(1000);

}