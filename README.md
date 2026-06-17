# IoT-Based Transformer Monitoring System ⚡☁️

Developed a cloud-connected Industrial Safety Architecture using an ESP32 and the ThingSpeak IoT platform. This system enables real-time monitoring of transformer temperature and electrical loads, automatically routing priority email alerts to duty engineers during critical failures. 

The implementation demonstrates IoT communication, cloud integration, API rate-limit management, and embedded system control using Wi-Fi.

## 📌 Architecture Overview

This project is built using an ESP32 microcontroller and the ThingSpeak IoT platform, developed in a Wokwi simulation environment. 

It enables automated safety protocols by continuously reading sensor data. If temperature or electrical load thresholds are exceeded for a sustained period (15 seconds), the microcontroller triggers webhooks (ThingHTTP/React) to send emergency notifications via the internet.

### Core Concepts Demonstrated:
* Cloud communication
* Embedded systems control
* API rate-limit handling & state logic
* Wi-Fi-based device networking

## 🎯 Features
* 🌡️ **Real-time Monitoring:** Tracks temperature and electrical load.
* 📧 **Automated Alerts:** Routes priority email alerts for duty engineers.
* ☁️ **Cloud Integration:** Uses ThingSpeak for IoT communication and data logging.
* ⚙️ **Rate Limiting:** Utilizes custom C++ state-lock algorithms to manage server API limits safely.
* 🧪 **Simulation:** Fully developed and tested using Wokwi (no hardware required).

## 🛠️ Technologies Used
* **Hardware:** ESP32 Microcontroller, DHT22 Sensor, Potentiometer (Simulated Load)
* **Cloud:** ThingSpeak IoT Platform
* **Software:** Arduino IDE (C++), Wokwi Simulator
