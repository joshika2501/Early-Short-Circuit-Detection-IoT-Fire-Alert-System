#include <DHT.h>
// BY USING ESP8266 WITHOUT USING VOLTAGE SENSOR

#define MQ2_POWER_PIN D6      // GPIO12
#define ACS_POWER_PIN D7      // GPIO13
#define BUZZER_PIN D5         // GPIO14
#define RELAY_PIN D2          // GPIO4
#define DHTPIN D4             // GPIO2
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  pinMode(MQ2_POWER_PIN, OUTPUT);
  pinMode(ACS_POWER_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  
  digitalWrite(MQ2_POWER_PIN, LOW);
  digitalWrite(ACS_POWER_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, HIGH); 

  dht.begin();
}

void loop() {
  int gasValue = readMQ2();
  int currentRaw = readACS712();

  
  float voltage = currentRaw * (3.3 / 1023.0); 
  float current = (voltage - 2.5) / 0.185;     

 
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

 
  Serial.print("Gas Value: "); Serial.println(gasValue);
  Serial.print("Current (A): "); Serial.println(current);
  Serial.print("Temp: "); Serial.print(temperature); Serial.print(" °C, ");
  Serial.print("Humidity: "); Serial.println(humidity);

  
  bool gasDanger = gasValue > 400;     
  bool currentDanger = current > 0.7;   

  if (gasDanger || currentDanger) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(RELAY_PIN, LOW); 
    Serial.println("⚠️  Danger! Relay off. Buzzer on.");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RELAY_PIN, HIGH); // Power ON
    Serial.println("✅ Safe. Relay on.");
  }

  delay(3000); 
}


int readMQ2() {
  digitalWrite(ACS_POWER_PIN, LOW);    
  digitalWrite(MQ2_POWER_PIN, HIGH);   
  delay(2000);                         
  int value = analogRead(A0);
  digitalWrite(MQ2_POWER_PIN, LOW);   
  return value;
}


int readACS712() {
  digitalWrite(MQ2_POWER_PIN, LOW);    
  digitalWrite(ACS_POWER_PIN, HIGH);   
  delay(500);                          
  int value = analogRead(A0);
  digitalWrite(ACS_POWER_PIN, LOW);    
  return value;
}
