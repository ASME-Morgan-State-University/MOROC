#include <WiFi.h>

const char* ssid = "NETGEAR37";
const char* password = "luckyocean160";

IPAddress staticIP(192, 168, 1, 101); // desired static IP
IPAddress gateway(192, 168, 1, 1); // gateway IP
IPAddress subnet(255, 255, 255, 0); // subnet mask

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  WiFi.config(staticIP, gateway, subnet);
  
  Serial.print("Connecting to Wi-Fi . . .");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(" .");
  }
  Serial.println("\nConnected to Wi-Fi.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {}