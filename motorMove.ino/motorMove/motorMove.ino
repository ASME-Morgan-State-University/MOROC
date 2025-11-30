int ML1 = 18; //Motor Left Front - low
int ML2 = 19; // - high

int MR1 = 17;//Motor right Back - low
int MR2 = 5;// - high 



void motorSetup() {
  pinMode(ML1, OUTPUT);
  pinMode(ML2, OUTPUT);
  pinMode(MR1, OUTPUT);
  pinMode(MR2, OUTPUT);
}

void forward(int ms_time){

  // Left Motor forward
  digitalWrite(ML1,LOW ); 
  digitalWrite(ML2,HIGH );

  // Right Motor forward
  digitalWrite(MR1, LOW); 
  digitalWrite(MR2, HIGH);

  Serial.print("forward\n");
  delay(ms_time);
}

void backward(int ms_time){

 // Left Motor backward
  digitalWrite(ML1, HIGH);
  digitalWrite(ML2, LOW);

  // Right Motor backward
  digitalWrite(MR1, HIGH);
  digitalWrite(MR2, LOW);

  Serial.print("backward\n");
  delay(ms_time);
}

void stop(int ms_delay){
  
  digitalWrite(ML1, LOW);
  digitalWrite(ML2, LOW);

  digitalWrite(MR1, LOW); 
  digitalWrite(MR2, LOW);
  
  Serial.print("stop\n");
  delay(ms_delay);
}

void right(int ms_time){ 
 //Left Motor forward
  digitalWrite(ML1,LOW ); // Motor front
  digitalWrite(ML2,HIGH );

  //Right motor backward
  digitalWrite(MR1, HIGH); // Motor front
  digitalWrite(MR2, LOW);

  Serial.print("right\n");
  delay(ms_time);
}

void left(int ms_time){
  // Left Motor backward
  digitalWrite(ML1, HIGH);// Motor front
  digitalWrite(ML2, LOW);

  // Right motor forward
  digitalWrite(MR1, LOW); // Motor back
  digitalWrite(MR2, HIGH);

  Serial.print("left\n");
  delay(ms_time);
}

void setup(){
  Serial.begin(115200);
  motorSetup();
  Serial.println("Motor Ready");

}

void loop(){
  forward(1000);
  backward(1000);
  right(2000);
  left(2000);
  stop(5000);
}
