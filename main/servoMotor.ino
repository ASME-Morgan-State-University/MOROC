#include <ESP32Servo.h>

Servo myServo;  

int servoPin = 4;  
int pos = 0;   // global position tracker
void servoSetup() {
  // myServo.setPeriodHertz(50);    // standard 50 hz servo
  myServo.attach(servoPin, 500, 2400); // attaches the servo on pin 4 to the servo object
  // myServo.write(0);              // initial position
}

void armOut() {
  if (pos < 90) {
    for (; pos <= 90; pos += 5) {   // use global pos
      myServo.write(pos);
      
      delay(100);
    }
  } else {
    Serial.println("It's already >= 90");
  }
  Serial.println(pos); // In serial monitor window, displays position of motor
}

void armIn() {
  if (pos > 0) {
    for (; pos >= 0; pos -= 5) {    // use global pos
      myServo.write(pos);
      delay(100);
    }
  } else {
    Serial.println("It's already <= 0");
  }
  Serial.println(pos); // In serial monitor window, displays position of motor
}

void sweep() {
  for (pos = 0; pos <= 90; pos += 5) {
    myServo.write(pos);
    delay(100);
  }
  for (pos = 90; pos >= 0; pos -= 5) {
    myServo.write(pos);
    delay(100);
  }
}
