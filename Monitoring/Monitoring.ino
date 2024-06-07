// Montoring
// Author: Arya Pathak
// Date: 20 January 2024


#include <Wire.h>
#include "DHT.h"
#include "Seeed_BMP280.h"
#include <WiFiMulti.h>
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

// WiFi and InfluxDB credentials
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define INFLUXDB_URL "YOUR_INFLUXDB_URL"
#define INFLUXDB_TOKEN "YOUR_INFLUXDB_TOKEN"
#define INFLUXDB_ORG "YOUR_INFLUXDB_ORG"
#define INFLUXDB_BUCKET "YOUR_INFLUXDB_BUCKET"
#define TZ_INFO "YOUR_TIMEZONE"

// Sensor pins
#define DHT_PIN 4
#define BMP_SDA 21
#define BMP_SCL 22

// Create sensor instances
DHT dht(DHT_PIN, DHT11);
BMP280 bmp280;

// Sensor readings variables
float temperature = 0;
float humidity = 0;
float pressure = 0;

// InfluxDB client instance
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// Data point for sensor readings
Point sensor("weather");

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  // Initialize sensors
  dht.begin();
  bmp280.begin(BMP_SDA, BMP_SCL);

  // Connect to WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Add tags to the sensor data point
  sensor.addTag("device", "ESP32");
  sensor.addTag("SSID", WIFI_SSID);

  // Sync time for certificate validation and batch writing
  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  // Check InfluxDB connection
  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }
}

void loop() {
  // Read sensor data
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  pressure = bmp280.readPressure();

  // Clear previous fields and add new sensor data
  sensor.clearFields();
  sensor.addField("temperature", temperature);
  sensor.addField("humidity", humidity);
  sensor.addField("pressure", pressure);

  // Check WiFi connection
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost");
    WiFi.reconnect();
    return;
  }

  // Write data point to InfluxDB
  if (!client.writePoint(sensor)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  // Display readings on serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" Pa");

  delay(1000); // Wait for 1 second
}
