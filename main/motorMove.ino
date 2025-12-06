int ML1 = 18; //Motor Left
int ML2 = 19; //

int MR1 = 26;//Motor right 
int MR2 = 25;// 

int motorSpeed = 128; // Global speed control (0-255)
int native_stop= 500; // Native Stop time build into each function

void motorSetup() {
  pinMode(ML1, OUTPUT);
  pinMode(ML2, OUTPUT);
  pinMode(MR1, OUTPUT);
  pinMode(MR2, OUTPUT);
}

void forward(int ms_time){
  // Left Motor forward
  analogWrite(ML1, 0); 
  analogWrite(ML2, motorSpeed);

  // Right Motor forward
  analogWrite(MR1, 0); 
  analogWrite(MR2, motorSpeed);

  Serial.print("forward\n");
  delay(ms_time);
  stop(native_stop);
}

void backward(int ms_time){
  // Left Motor backward
  analogWrite(ML1, motorSpeed);
  analogWrite(ML2, 0);

  // Right Motor backward
  analogWrite(MR1, motorSpeed);
  analogWrite(MR2, 0);

  Serial.print("backward\n");
  delay(ms_time);
  stop(native_stop);

}

void stop(int ms_delay){
  analogWrite(ML1, 0);
  analogWrite(ML2, 0);
  analogWrite(MR1, 0);
  analogWrite(MR2, 0);
  Serial.print("stop\n");
  delay(ms_delay);
}

void right(int ms_time){ 
  //Left Motor forward
  analogWrite(ML1, 0); // Motor front
  analogWrite(ML2, motorSpeed);

  //Right motor backward
  analogWrite(MR1, motorSpeed); // Motor front
  analogWrite(MR2, 0);

  Serial.print("right\n");
  delay(ms_time);
  stop(native_stop);
}

void left(int ms_time){
  // Left Motor backward
  analogWrite(ML1, motorSpeed);// Motor front
  analogWrite(ML2, 0);

  // Right motor forward
  analogWrite(MR1, 0); // Motor back
  analogWrite(MR2, motorSpeed);

  Serial.print("left\n");
  delay(ms_time);
  stop(native_stop);

}