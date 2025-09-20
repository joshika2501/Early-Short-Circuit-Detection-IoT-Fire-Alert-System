🔥 Early Short Circuit Detection & IoT-Based Fire Alert System (with Machine Learning + LoRa)
🔍 Overview

This project is a smart embedded safety system designed to detect early signs of short circuits and fire hazards by analyzing current, voltage, gas concentration, and temperature data.
It integrates Machine Learning models for anomaly detection and IoT platforms for real-time alerting, ensuring fast response and preventive action.

🚨 What Happens During a Fault

ML model detects anomalies (abnormal electrical/gas/temperature patterns).

Relay cuts off power supply instantly.

IoT Alert sent via Blynk / ThingsBoard.

Location shared with fire station/emergency contacts.

LoRa enables long-range, low-power communication, even without WiFi.

⚙ Features

✅ Real-time anomaly detection using ML
🧠 Multiple ML models (Logistic Regression, Decision Tree, Random Forest, Gradient Boosting, RNN, One-Class SVM)
📲 IoT alerts through Blynk / ThingsBoard
🔌 Automatic relay disconnection for fire prevention
📡 Location-sharing via GPS / hardcoded coordinates
📡 LoRa integration for remote communication in areas with no internet

 Machine Learning Integration

The system leverages traditional ML + deep learning + anomaly detection models to classify faults:

 ML Models Used

Logistic Regression / Decision Tree → simple & interpretable models for basic classification of normal vs fault states.

Random Forest / Gradient Boosting (XGBoost, LightGBM) → handle non-linear data and improve accuracy for mixed sensor readings.

Recurrent Neural Networks (RNNs) → detect time-series anomalies in sensor data streams.

One-Class SVM → useful for novel anomaly detection, especially rare short-circuit events.

 ML Pipeline

Data Collection → ( data_logger.ino) collects voltage, current, gas, and temperature values.

Model Training → ( train_model.ipynb) with scikit-learn, XGBoost, TensorFlow.

Model Conversion → trained models converted to TensorFlow Lite for ESP32.

Deployment → ESP32 runs .tflite inference for real-time predictions.

Fault Classification → abnormal readings trigger cutoff + IoT alert.

🛠 Tech Stack

Microcontroller: ESP32

Sensors:

MQ-2 → Gas detection

ACS712 → Current monitoring

Voltage Sensor (0–25V analog)

DHT11 → Temperature & Humidity

IoT Platforms:

Blynk (real-time alerts on mobile)

ThingsBoard (data visualization & analytics)

LoRa (long-range, low-power communication for rural/remote areas)

📲 Alert Methods

🔔 Blynk notifications on mobile app

📧 Email / SMS via IoT integration

📌 Location Sharing (GPS module / hardcoded coordinates)

📡 LoRa Integration

LoRa is used as a backup communication channel in case WiFi or GSM fails.

✅ Advantages of LoRa:

Low Cost → operates on unlicensed ISM bands, no SIM needed.

Long Range → up to 10+ km in open areas.

Low Power → ideal for battery-powered safety systems.

Reliable → ensures alerts even in remote/rural areas without internet.

🧪 Testing & Deployment

Deploy ESP32 with all sensors + GSM/GPS + LoRa module.

Collect real-time sensor data & validate ML predictions.

Simulate hazards (gas leak, short circuit, overheating).

Verify:

⚡ Relay cutoff response

📲 Alert delivery (Blynk/ThingsBoard/LoRa)

📡 Location sharing

🚀 Impact & Benefits

🏠 Home safety → prevents electrical fires.

🏭 Industrial monitoring → detects anomalies in machinery/equipment.

🌍 Scalable solution → low-cost, suitable for both urban & rural areas.

📶 Works offline with LoRa, ensuring uninterrupted alerts.
