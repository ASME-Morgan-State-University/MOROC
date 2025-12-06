void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // ledsetup();
  // Tempsetup();
  motorSetup();
  servoSetup();
  // networkSetup();

  // Avaliable functions:
  // forward(int ms_time)
  // backward(int ms_time)
  // right(int ms_time)
  // left(int ms_time)
  // stop(int ms_delay)
  // sweep()
  // readTempurature()
  // Dont forget to put ; at the end of each function call
   

  // put your main code below here:


}

void loop() {
  forward(1000);
  backward(1000);
  right(1000);
  left(1000);
  stop(1000);
  sweep();
  readTempurature();
  Serial.println("DONE");
}
