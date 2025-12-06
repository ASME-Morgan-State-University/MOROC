#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;

void Tempsetup() {
  if (!aht.begin()) {
    Serial.println("Could not find AHT20 sensor, check wiring!");
    while (1) delay(10);
  }
}

void readTempurature() { // Read temperature and send via WebSocket
  sensors_event_t temp;
  aht.getEvent(NULL, &temp); // This allows for us to only ask for temp
  int output_temp = round(temp.temperature * 10) / 10.0;
  Serial.println(String(output_temp));
  wsServer.loop();
  String tempStr = String(output_temp);
  wsServer.broadcastTXT(tempStr); // Returns temperature rounded to 1 decimal
}

