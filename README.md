# Early-Short-Circuit-Detection-IoT-Fire-Alert-System
A smart embedded system that detects early signs of short circuits using real-time current, voltage, and temperature monitoring. When a potential fault is identified, the system cuts power and instantly alerts the nearest fire station and users via IoT platforms (Blynk, IFTTT, SMS, or email). 
# Early Short Circuit Detection & IoT-Based Fire Alert System 🔥

## 🔍 Overview
This project detects early signs of short circuits using current, voltage, and temperature sensors. When a fault is detected, the system immediately:
- Cuts off power via relay
- Sends alerts via Wi-Fi (Blynk, IFTTT, or email)
- Notifies the nearest fire station via SMS or online dashboard

## ⚙️ Features
- Real-time short circuit detection
- IoT-enabled alerts (SMS, Email, App)
- Local relay trip for circuit protection
- Fire station notification with location
- Optional offline alert using LoRa

## 🛠️ Tech Stack
- ESP32 (Wi-Fi)
- SIM800L (GSM/SMS)
- Blynk IoT Platform
- IFTTT Webhooks
- Firebase/ThingsBoard (Optional)

## 📦 Directory Structure
- `firmware/` – Arduino code for ESP32 and GSM
- `hardware/` – Circuit diagrams and schematics
- `iot_integration/` – Setup guides for cloud services
- `dashboard/` – Fire station dashboard (HTML/JS)
- `docs/` – Project documents and troubleshooting

## 📲 Alert Methods
- Blynk mobile notifications
- SMS via SIM800L
- Email via ESP32 SMTP
- LoRa message to base station (optional)

## 📌 Location & Contact Sharing
Hardcoded GPS or module-based location sharing included in all alerts.

## 📷 Screenshots
![System Block Diagram](hardware/circuit_diagram.png)
![Workflow](iot_integration/fire_station_alert_workflow.png)
