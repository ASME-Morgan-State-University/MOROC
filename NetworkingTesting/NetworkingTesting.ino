
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <esp_system.h>  // for esp_random()

/* ==== Wi‑Fi (with static IP) ==== */
const char* ssid     = "NETGEAR37";
const char* password = "luckyocean160";

IPAddress staticIP(192, 168, 1, 101); // ESP32's desired static IP
IPAddress gateway (192, 168, 1, 1);   // gateway IP
IPAddress subnet  (255, 255, 255, 0); // subnet mask
// Optional: DNS servers
// IPAddress dns1(192, 168, 1, 1), dns2(8, 8, 8, 8);

/* ==== WebSocket server ==== */
const uint16_t WS_PORT  = 80;
WebSocketsServer wsServer(WS_PORT);

/* ==== RNG send cadence ==== */
const uint32_t SEND_INTERVAL_MS = 2000; // send a random number every 2 seconds
uint32_t lastSendMs = 0;

/* ==== Simple client registry (optional) ==== */
size_t clientCount = 0;

void onWsEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED: {
      IPAddress ip = wsServer.remoteIP(num);
      clientCount++;
      Serial.printf("[WS] Client #%u connected from %s. Total: %u\n",
                    num, ip.toString().c_str(), clientCount);
      // Announce server
      // wsServer.sendTXT(num, "{\"event\":\"hello\",\"role\":\"rng-server\"}");
      break;
    }

    case WStype_DISCONNECTED:
      if (clientCount > 0) clientCount--;
      Serial.printf("[WS] Client #%u disconnected. Total: %u\n", num, clientCount);
      break;

    case WStype_TEXT: {
      String cmd = String((const char*)payload, length);
      Serial.printf("[WS] Text from #%u: %s\n", num, cmd.c_str());
      if (cmd == "rng" || cmd == "sample" || cmd == "{\"type\":\"rng\"}") {
        uint32_t value = (uint32_t)esp_random() % 101;
        String msg = String(value);
        wsServer.sendTXT(num, msg);
      }
      break;
    }

    case WStype_PING:
      Serial.printf("[WS] Ping from #%u\n", num);
      break;

    case WStype_PONG:
      Serial.printf("[WS] Pong from #%u\n", num);
      break;

    default:
      break;
  }
}

void connectWifi() {
  Serial.println("Connecting to Wi‑Fi…");
  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false); // helps keep WS stable

  // Set static IP before begin()
  if (!WiFi.config(staticIP, gateway, subnet /*, dns1, dns2 */)) {
    Serial.println("WiFi.config() failed (static IP). Continuing with DHCP…");
  }

  WiFi.begin(ssid, password);

  // Wait for connection
  uint8_t attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    attempts++;
    if (attempts > 40) { // ~40s timeout
      Serial.println("\nWi‑Fi connect timeout. Retrying…");
      attempts = 0;
      WiFi.disconnect();
      delay(2000);
      WiFi.begin(ssid, password);
    }
  }

  Serial.println("\nConnected to Wi‑Fi.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  delay(100);

  randomSeed(esp_random()); // good hardware seed

  connectWifi();

  // Start WebSocket server
  wsServer.begin();
  wsServer.onEvent(onWsEvent);
  Serial.printf("RNG WebSocket server listening at ws://%s:%u\n",
                WiFi.localIP().toString().c_str(), WS_PORT);
}

void loop() {
  // Pump server events
  wsServer.loop();

  // Broadcast RNG at a fixed interval to all clients
  uint32_t now = millis();
  if (now - lastSendMs >= SEND_INTERVAL_MS) {
    lastSendMs = now;

    uint32_t value = (uint32_t)esp_random() % 101;
    String msg = String(value);

    wsServer.broadcastTXT(msg);
    Serial.printf("[WS] Broadcast RNG: %u\n", value);
  }
}
