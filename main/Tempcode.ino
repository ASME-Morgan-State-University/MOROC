#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;

void Tempsetup() {
  Serial.begin(115200);
  if (!aht.begin()) {
    Serial.println("Could not find AHT20 sensor, check wiring!");
    while (1) delay(10);
  }
}
float readTempurature() { // This gives a floating value rather than a void
  sensors_event_t temp;
  aht.getEvent(NULL, &temp); // This allows for us to only ask for temp
  return round(temp.temperature * 10) / 10.0; // Returns temperature rounded to 1 decimal
}

