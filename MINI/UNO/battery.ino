#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
// Use <WiFi.h> and <HTTPClient.h> if using ESP32

const char* ssid = "your_SSID";          // Replace with your WiFi SSID
const char* password = "your_PASSWORD";  // Replace with your WiFi password
const char* serverUrl = "http://192.168.41.192:5000/data"; // Replace with your computer's IP address and Flask server port

const int voltagePin = A0;   // Pin connected to voltage sensor
const int currentPin = A1;   // Pin connected to current sensor
const int tempPin = A2;      // Pin connected to temperature sensor

WiFiClient client;
HTTPClient http;

void setup() {
  Serial.begin(9600);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

float readVoltage() {
  int sensorValue = analogRead(voltagePin);
  float voltage = sensorValue * (3.3 / 1023.0) * (11.0); // Assuming a voltage divider with a ratio of 1:11
  return voltage;
}

float readCurrent() {
  int sensorValue = analogRead(currentPin);
  float current = (sensorValue * (3.3 / 1023.0) - 2.5) * 20.0; // Assuming a 0-3.3V range with 2.5V as the zero current point, and a sensitivity of 100mV/A
  return current;
}

float readTemperature() {
  int sensorValue = analogRead(tempPin);
  float voltage = sensorValue * (3.3 / 1023.0);
  float temperature = voltage * 100.0; // Assuming a LM35 temperature sensor with a scale factor of 10mV/°C
  return temperature;
}

void loop() {
  float voltage = readVoltage();
  float current = readCurrent();
  float temperature = readTemperature();

  // Create JSON string
  String jsonData = "{\"voltage\": ";
  jsonData += String(voltage, 2);
  jsonData += ", \"current\": ";
  jsonData += String(current, 2);
  jsonData += ", \"temperature\": ";
  jsonData += String(temperature, 2);
  jsonData += "}";

  // Send data to server
  if (WiFi.status() == WL_CONNECTED) {
    http.begin(client, serverUrl);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonData);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(1000); // Send data every second
}
