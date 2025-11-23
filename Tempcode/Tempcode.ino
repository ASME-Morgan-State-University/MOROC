#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;

String inputString = "";   // holds incoming text

void setup() {
  Serial.begin(115200);
  if (!aht.begin()) {
    Serial.println("Could not find AHT20 sensor, check wiring!");
    while (1) delay(10);
  }
}
float readTempurature() { // This gives a floating value rather than a void
  sensors_event_t temp;
  aht.getEvent(NULL, &temp); // This allows for us to only ask for temp
  return temp.temperature; // Returns the value of temp
}

void loop() {
  float t = readTempurature();
  Serial.println(t, 2);

  delay(1000);
}