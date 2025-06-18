#include <DHT.h>

// ----------- Pins ------------
#define MQ2_POWER_PIN D6      // GPIO12
#define ACS_POWER_PIN D7      // GPIO13
#define BUZZER_PIN D5         // GPIO14
#define RELAY_PIN D2          // GPIO4
#define DHTPIN D4             // GPIO2
#define DHTTYPE DHT11

// ----------- Sensor setup ------------
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  pinMode(MQ2_POWER_PIN, OUTPUT);
  pinMode(ACS_POWER_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  // Ensure all are off initially
  digitalWrite(MQ2_POWER_PIN, LOW);
  digitalWrite(ACS_POWER_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, HIGH); // Relay ON by default

  dht.begin();
}

void loop() {
  int gasValue = readMQ2();
  int currentRaw = readACS712();

  // Convert current sensor raw reading to amps (for 5A ACS712)
  float voltage = currentRaw * (3.3 / 1023.0); // ESP8266 = 3.3V
  float current = (voltage - 2.5) / 0.185;     // Sensitivity = 185mV/A

  // Read DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Print values
  Serial.print("Gas Value: "); Serial.println(gasValue);
  Serial.print("Current (A): "); Serial.println(current);
  Serial.print("Temp: "); Serial.print(temperature); Serial.print(" °C, ");
  Serial.print("Humidity: "); Serial.println(humidity);

  // Safety threshold logic
  bool gasDanger = gasValue > 400;       // Adjust as needed
  bool currentDanger = current > 0.7;    // Adjust depending on your appliance

  if (gasDanger || currentDanger) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(RELAY_PIN, LOW); // Cut off power
    Serial.println("⚠️  Danger! Relay off. Buzzer on.");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RELAY_PIN, HIGH); // Power ON
    Serial.println("✅ Safe. Relay on.");
  }

  delay(3000); // 3 sec delay between readings
}

// ---------- Read MQ-2 (Analog) ----------
int readMQ2() {
  digitalWrite(ACS_POWER_PIN, LOW);    // Ensure ACS is OFF
  digitalWrite(MQ2_POWER_PIN, HIGH);   // Power ON MQ-2
  delay(2000);                         // Warmup time (can reduce to 1000ms after initial test)
  int value = analogRead(A0);
  digitalWrite(MQ2_POWER_PIN, LOW);    // Turn off MQ-2
  return value;
}

// ---------- Read ACS712 (Analog) ----------
int readACS712() {
  digitalWrite(MQ2_POWER_PIN, LOW);    // Ensure MQ-2 is OFF
  digitalWrite(ACS_POWER_PIN, HIGH);   // Power ON ACS712
  delay(500);                          // Stabilize
  int value = analogRead(A0);
  digitalWrite(ACS_POWER_PIN, LOW);    // Turn off ACS712
  return value;
}
