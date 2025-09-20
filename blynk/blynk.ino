/*************************************************************
  Blynk IoT ESP32 Code
  Fix for "Please specify your BLYNK_TEMPLATE_ID and BLYNK_TEMPLATE_NAME"
*************************************************************/

// Replace with your Blynk IoT details
#define BLYNK_TEMPLATE_ID "TMPL308GBa6j7"       // Get this from Blynk console
#define BLYNK_TEMPLATE_NAME "NEW project "
#define BLYNK_AUTH_TOKEN "KPZFBzNR_GRb9RzCdDwJU7CpehX2FZb3"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// -------- Pin Definitions --------
#define PIN_VOLT   32    
#define PIN_CURR   33    
#define PIN_MQ2    34    
#define PIN_RELAY  25    
#define PIN_DHT    4     
#define PIN_BUZZER 27    

// -------- DHT Configuration --------
#define DHTTYPE DHT11
DHT dht(PIN_DHT, DHTTYPE);

// -------- Sensor Calibration --------
const float VCC = 3.3;              
const int ADC_MAX = 4095;           
const float VOLTAGE_REF = 25.0;     
const float ACS712_SENSITIVITY = 0.100; 

// -------- Variables --------
float voltageValue = 0;
float currentValue = 0;
float gasValue = 0;
float temperature = 0;
float humidity = 0;

// -------- WiFi Credentials --------
char ssid[] = "12345678";     
char pass[] = "12345678"; 

BlynkTimer timer;

// -------- Send Sensor Data to Blynk --------
void sendSensorData() {
  // Voltage
  int rawVolt = analogRead(PIN_VOLT);
  voltageValue = (rawVolt * VOLTAGE_REF) / ADC_MAX;

  // Current
  int rawCurr = analogRead(PIN_CURR);
  float voltageOut = (rawCurr * VCC) / ADC_MAX;
  float offset = VCC / 2;
  currentValue = (voltageOut - offset) / ACS712_SENSITIVITY;

  // Gas
  int rawGas = analogRead(PIN_MQ2);
  gasValue = (rawGas * VCC) / ADC_MAX;

  // DHT
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  // Send values to Blynk Virtual Pins
  Blynk.virtualWrite(V0, voltageValue);
  Blynk.virtualWrite(V1, currentValue);
  Blynk.virtualWrite(V2, gasValue);
  Blynk.virtualWrite(V3, temperature);
  Blynk.virtualWrite(V4, humidity);

  // Safety Check
  if (gasValue >= 0.20) {
    digitalWrite(PIN_RELAY, HIGH);
    digitalWrite(PIN_BUZZER, HIGH);
    Blynk.logEvent("gas_alert", "⚠ Gas Detected! Relay & Buzzer ON");
  } else {
    digitalWrite(PIN_RELAY, LOW);
    digitalWrite(PIN_BUZZER, LOW);
  }

  // Debug Output
  Serial.println("===== Sensor Readings =====");
  Serial.print("Voltage: "); Serial.print(voltageValue); Serial.println(" V");
  Serial.print("Current: "); Serial.print(currentValue); Serial.println(" A");
  Serial.print("Gas: "); Serial.print(gasValue); Serial.println(" Tb");
  Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" *C");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
  Serial.println("===========================");
}

// -------- Control Relay from Blynk --------
BLYNK_WRITE(V5) {
  int relayState = param.asInt();
  digitalWrite(PIN_RELAY, relayState);
}

// -------- Control Buzzer from Blynk --------
BLYNK_WRITE(V6) {
  int buzzerState = param.asInt();
  digitalWrite(PIN_BUZZER, buzzerState);
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(2000);

  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_RELAY, LOW);
  digitalWrite(PIN_BUZZER, LOW);

  // Connect to WiFi + Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Send data every 2 seconds
  timer.setInterval(2000L, sendSensorData);

  Serial.println("ESP32 Monitoring System with Blynk Started...");
}

void loop() {
  Blynk.run();
  timer.run();
}
