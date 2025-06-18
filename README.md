# 🔥 Early Short Circuit Detection & IoT-Based Fire Alert System (with Machine Learning)

## 🔍 Overview

This project is an enhanced smart embedded system that detects early signs of short circuits and fire hazards by analyzing real-time current, voltage, gas concentration, and temperature data. Using Machine Learning, it intelligently identifies abnormal behavior and triggers safety protocols.

### 🚨 What Happens During a Fault:

* ML model detects electrical/gas anomalies
* Cuts off power via relay
* Sends instant alerts through IoT platforms (Blynk)
* Shares location with nearest fire station or emergency contacts

---

## ⚙️ Features

* ✅ Real-time anomaly detection with ML
* 🧠 ML model trained on voltage/current/gas/temp data
* 📲 IoT alerts (Blynk)
* 🔌 Automatic relay disconnection
* 🌐 Location-sharing via GPS or hardcoded coordinates

---

## 🧠 Machine Learning Integration

* Sensor data (voltage, current, gas, temperature) is collected and logged
* Trained on an Isolation Forest or Decision Tree model
* Model is optimized using TensorFlow Lite for Microcontrollers
* ESP32 runs the model inference to detect abnormal sensor behavior

### ML Pipeline:

1. Data Collection (data_logger.ino)
2. Model Training (`train_model.ipynb`)
3. Conversion to `.tflite` and upload to ESP32
4. Real-time prediction and fault classification

---

## 🛠️ Tech Stack

* **Microcontroller:** ESP32
* **Sensors:**

  * MQ-2 (Gas sensor)
  * ACS712 (Current sensor)
  * Voltage Sensor (0–25V analog)
  * DHT11 (Temperature & Humidity)
* **IoT Platforms:**

  * Blynk
  * ThingsBoard 
 
---


## 📲 Alert Methods

* **Blynk notifications** (mobile app)
---

## 📌 Location Sharing

All alert methods include approximate or GPS-based location:


* 📡 GPS module for real-time geolocation

---

## 🧪 Testing & Deployment

1. Deploy ESP32 with all sensors and GSM module
2. Collect real-time data and test ML predictions
3. Simulate hazards (e.g., gas leak, short circuit)
4. Verify alert delivery and device cutoff response

---

## 📷 Screenshots & Diagrams

Include in `docs/` or `hardware/`:

* Block diagram
* Circuit schematic
* ML model architecture
