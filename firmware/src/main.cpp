#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Basic firmware sketch for Duckie water monitoring
// Reads dummy water-quality data and posts it to a backend API.

// TODO: replace with real credentials and sensor wiring
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";

const char* BACKEND_URL = "http://your-backend-host/api/measurements"; // replace when backend is deployed

void connectWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

struct Measurement {
  float temperature;
  float turbidity;
  float ph;
};

Measurement readSensors() {
  // TODO: replace with real sensor code (e.g., analogRead, I2C sensors, etc.)
  Measurement m{};
  m.temperature = 24.5; // deg C
  m.turbidity = 3.2;    // NTU
  m.ph = 7.1;
  return m;
}

void postMeasurement(const Measurement& m) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected, skipping POST");
    return;
  }

  HTTPClient http;
  http.begin(BACKEND_URL);
  http.addHeader("Content-Type", "application/json");

  StaticJsonDocument<256> doc;
  doc["device_id"] = "duckie-esp32-001";
  doc["temperature"] = m.temperature;
  doc["turbidity"] = m.turbidity;
  doc["ph"] = m.ph;

  String body;
  serializeJson(doc, body);

  int code = http.POST(body);
  Serial.print("POST /measurements -> status: ");
  Serial.println(code);

  http.end();
}

unsigned long lastPost = 0;
const unsigned long POST_INTERVAL_MS = 30 * 1000; // 30 seconds

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Duckie firmware starting...");
  connectWifi();
}

void loop() {
  unsigned long now = millis();
  if (now - lastPost >= POST_INTERVAL_MS) {
    lastPost = now;
    Measurement m = readSensors();
    Serial.println("Sending measurement...");
    postMeasurement(m);
  }

  delay(100);
}
