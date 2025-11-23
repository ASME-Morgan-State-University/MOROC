int ML1 = 18; //Motor Left Front - low
int ML2 = 19; // - high

int MR1 = 22;//Motor right Back - low
int MR2 = 23;// - high 



void setup() {
Serial.begin(115200);
}

// Forward
void loop() {
forward();
back();
stop();
left();
right();
}

void forward(){
  
  pinMode(ML1, OUTPUT);
  pinMode(ML2, OUTPUT);

  pinMode(MR1, OUTPUT);
  pinMode(MR2, OUTPUT);
  digitalWrite(ML1,LOW ); 
  digitalWrite(ML2,HIGH );

  digitalWrite(MR1, LOW); 
  digitalWrite(MR2, HIGH);
  Serial.print("backward\n");

 
  Serial.print("forward\n");
  delay(3000);
}

void back(){

  pinMode(ML1, OUTPUT);
  pinMode(ML2, OUTPUT);

  pinMode(MR1, OUTPUT);
  pinMode(MR2, OUTPUT);

 //Front motor 
  digitalWrite(ML1, HIGH); // left
  digitalWrite(ML2, LOW);

  digitalWrite(MR1, HIGH); //right
  digitalWrite(MR2, LOW);
  //Front Motor

  delay(3000);
}

void stop(){

  pinMode(ML1, OUTPUT);
  pinMode(ML2, OUTPUT);

  pinMode(MR1, OUTPUT);
  pinMode(MR2, OUTPUT);

    // Brake
  digitalWrite(ML1, LOW);
  digitalWrite(ML2, LOW);

  digitalWrite(MR1, LOW); 
  digitalWrite(MR2, LOW);
  Serial.print("stop\n");
  delay(3000);
}

void right(){
   
  pinMode(ML1, OUTPUT);
  pinMode(ML2, OUTPUT);

  pinMode(MR1, OUTPUT);
  pinMode(MR2, OUTPUT);

 //Left Motor backward
  digitalWrite(ML1,LOW ); // Motor front
  digitalWrite(ML2,HIGH );

  //right motor forward
  digitalWrite(MR1, HIGH); // Motor front
  digitalWrite(MR2, LOW);
  Serial.print("right\n");
  delay(3000);
}

  void left(){
    // Brake
  digitalWrite(ML1, HIGH);// Motor front
  digitalWrite(ML2, LOW);

  digitalWrite(MR1, LOW); // Motor back
  digitalWrite(MR2, HIGH);
  Serial.print("left\n");
  delay(3000);
  }


