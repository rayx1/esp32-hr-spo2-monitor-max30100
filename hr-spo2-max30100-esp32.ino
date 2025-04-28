#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <FS.h>
#include <SPIFFS.h>
#include "MAX30100_PulseOximeter.h"

PulseOximeter pox;
WebServer server(80);
WebSocketsServer ws(81);

// Your ESP32 Hotspot credentials
const char* ssid = "ESP32_HR_Monitor";
const char* password = "12345678";

float heartRate = 0.0;
float spo2 = 0.0;
float perfusionIndex = 0.0;

unsigned long lastSampleTime = 0;
const int sampleInterval = 1000; // 1 second

void onBeatDetected() {
  Serial.println("Beat!");
}

void handleRoot() {
  File file = SPIFFS.open("/index.html", "r");
  if (!file) {
    server.send(500, "text/plain", "Failed to open /index.html");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

void handleChartJS() {
  File file = SPIFFS.open("/chart.js", "r");
  if (!file) {
    server.send(500, "text/plain", "Failed to open /chart.js");
    return;
  }
  server.streamFile(file, "application/javascript");
  file.close();
}

void setup() {
  Serial.begin(115200);
  delay(500);

  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS failed to mount.");
    return;
  }

  // Setup WiFi AP (Hotspot)
  WiFi.softAP(ssid, password);
  Serial.println();
  Serial.print("Hotspot IP: ");
  Serial.println(WiFi.softAPIP());

  // Initialize MAX30100
  if (!pox.begin()) {
    Serial.println("MAX30100 init failed");
    while (1);
  }
  Serial.println("MAX30100 initialized");

  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);

  // Setup server routes
  server.on("/", handleRoot);
  server.on("/chart.js", handleChartJS);
  server.begin();
  Serial.println("HTTP server started");

  // Start WebSocket
  ws.begin();
  ws.onEvent(onWebSocketEvent);
}

void loop() {
  pox.update();
  server.handleClient();
  ws.loop();

  unsigned long now = millis();
  if (now - lastSampleTime >= sampleInterval) {
    lastSampleTime = now;

    heartRate = pox.getHeartRate();
    spo2 = pox.getSpO2();
    perfusionIndex = 0.0; // (Optional) Need custom implementation for PI

    String json = "{\"heartRate\":" + String(heartRate) +
                  ",\"spo2\":" + String(spo2) +
                  ",\"pi\":" + String(perfusionIndex) + "}";

    Serial.println(json);    // <-- Debug serial monitor
    ws.broadcastTXT(json);        // <-- Send to all connected WebSocket clients
  }
}

void onWebSocketEvent(uint8_t client_num, WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_CONNECTED) {
    Serial.println("WebSocket connected");
  }
}