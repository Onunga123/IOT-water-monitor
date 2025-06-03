// IoT-Based Offline Real-Time Water Quality Monitoring System
// Hardware: ESP32, TDS sensor, DS18B20 temperature sensor
// Mode: Access Point (no internet)

#include <WiFi.h>
#include <WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ========== Pin Configuration ==========
#define TDS_PIN 34
#define ONE_WIRE_BUS 4

// ========== WiFi Access Point Credentials ==========
const char* ssid = "WaterSafe";
const char* password = "12345678";

// ========== Sensor Initialization ==========
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
WebServer server(80);

// ========== Global Variables ==========
float temperature = 0.0;
float tdsValue = 0.0;
String waterStatus = "Safe";
unsigned long lastSensorRead = 0;
const unsigned long sensorInterval = 3000;

// ========== Function to Read Sensor Data ==========
void readSensors() {
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);

  int analogValue = analogRead(TDS_PIN);
  float voltage = analogValue * (3.3 / 4095.0);
  tdsValue = (133.42 * pow(voltage, 3)) - (255.86 * pow(voltage, 2)) + (857.39 * voltage);

  if (tdsValue > 500 || temperature < 10 || temperature > 40) {
    waterStatus = "Unsafe";
  } else if (tdsValue > 300 || temperature < 15 || temperature > 35) {
    waterStatus = "Caution";
  } else {
    waterStatus = "Safe";
  }
}

// ========== Function to Return HTML Dashboard ==========
String getHTMLPage() {
  String color = (waterStatus == "Safe") ? "#2ecc71" :
                 (waterStatus == "Caution") ? "#f39c12" : "#e74c3c";

  String page = R"====(
  <!DOCTYPE html>
  <html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Water Quality Dashboard</title>
    <style>
      body {
        background-color: #121212;
        color: #ffffff;
        font-family: 'Segoe UI', sans-serif;
        text-align: center;
        margin: 0;
        padding: 0;
      }
      .header {
        background-color: #1e1e1e;
        padding: 20px;
        font-size: 24px;
        font-weight: bold;
        box-shadow: 0 2px 5px rgba(0,0,0,0.5);
      }
      .card {
        background-color: #1e1e1e;
        border-radius: 15px;
        margin: 30px auto;
        padding: 25px;
        width: 90%;
        max-width: 350px;
        box-shadow: 0 0 15px rgba(0,0,0,0.3);
      }
      .status {
        padding: 15px;
        border-radius: 10px;
        font-size: 18px;
        font-weight: bold;
        background-color: )====" + color + R"====(; color: white;
      }
    </style>
    <meta http-equiv="refresh" content="5">
  </head>
  <body>
    <div class="header">IoT Water Quality Monitor</div>
    <div class="card">
      <p>Temperature: <strong>)====" + String(temperature, 1) + R"====( °C</strong></p>
      <p>TDS: <strong>)====" + String(tdsValue, 1) + R"====( ppm</strong></p>
      <p class="status">Status: )====" + waterStatus + R"====(</p>
    </div>
  </body>
  </html>
  )====";

  return page;
}

// ========== Web Server Route ==========
void handleRoot() {
  server.send(200, "text/html", getHTMLPage());
}

// ========== Setup Function ==========
void setup() {
  Serial.begin(115200);
  sensors.begin();

  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");
  Serial.println(WiFi.softAPIP());

  readSensors();
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server started");
}

// ========== Main Loop ==========
void loop() {
  unsigned long now = millis();
  if (now - lastSensorRead >= sensorInterval) {
    readSensors();
    lastSensorRead = now;
  }
  server.handleClient();
}
