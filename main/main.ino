void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  ledsetup();
  // Tempsetup();
  motorSetup();
  servoSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  lights_on();
  delay(1000);
  sweep();
  forward(2000);
  backward(2000);
  left(2000);
  right(2000);

}
