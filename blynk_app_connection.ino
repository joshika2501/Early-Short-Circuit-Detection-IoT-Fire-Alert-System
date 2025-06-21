// Taken from the blynk cloud
#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "SmartSafetySystem"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

// Basic library
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);   

// Wi-Fi credentials
char ssid[] = "YourWiFi";
char pass[] = "YourPassword";

// Pins
#define MQ2_POWER_PIN D6
#define ACS_POWER_PIN D7
#define ANALOG_PIN A0
#define RELAY_PIN D2
#define BUZZER_PIN D5

BlynkTimer timer;
bool buzzerMuted = false; 

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(MQ2_POWER_PIN, OUTPUT);
  pinMode(ACS_POWER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
 
  digitalWrite(RELAY_PIN, HIGH);  
  digitalWrite(BUZZER_PIN, LOW);  

  dht.begin();
  timer.setInterval(3000L, readSensors);
}

void loop() {
  Blynk.run();
  timer.run();

// Virtual switch to mute/unmute from Blynk
BLYNK_WRITE(V4) {
  int state = param.asInt();
  buzzerMuted = (state == 1);
  if (buzzerMuted) {
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("🔇 Buzzer muted via Blynk app.");
  } else {
    Serial.println("🔊 Buzzer unmuted via Blynk app.");
  }
}

void readSensors() {
  int gasValue = readMQ2();
  float current = readCurrent();
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Gas: "); Serial.print(gasValue);
  Serial.print("  Current: "); Serial.print(current);
  Serial.print("  Temp: "); Serial.print(temperature);
  Serial.print("  Humidity: "); Serial.println(humidity);

  Blynk.virtualWrite(V0, gasValue);
  Blynk.virtualWrite(V1, current);
  Blynk.virtualWrite(V2, temperature);
  Blynk.virtualWrite(V3, humidity);

  if ((gasValue > 400 || current > 0.7) && !buzzerMuted) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(RELAY_PIN, LOW);
    Blynk.logEvent("alert", "⚠️ Gas/Current anomaly detected!");
  } else {
    digitalWrite(RELAY_PIN, HIGH);
    if (!buzzerMuted) digitalWrite(BUZZER_PIN, LOW);
  }
}

int readMQ2() {
  digitalWrite(ACS_POWER_PIN, LOW);
  digitalWrite(MQ2_POWER_PIN, HIGH);
  delay(1000);
  int val = analogRead(ANALOG_PIN);
  digitalWrite(MQ2_POWER_PIN, LOW);
  return val;
}

float readCurrent() {
  digitalWrite(MQ2_POWER_PIN, LOW);
  digitalWrite(ACS_POWER_PIN, HIGH);
  delay(500);
  int raw = analogRead(ANALOG_PIN);
  digitalWrite(ACS_POWER_PIN, LOW);

  float voltage = raw * (3.3 / 1023.0);
  float current = (voltage - 2.5) / 0.185;
  return abs(current);
}
