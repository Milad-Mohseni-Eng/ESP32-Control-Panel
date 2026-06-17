# ESP32 Control Panel (OLED + Sensors + LEDs)

## 📌 Overview
This project is a smart ESP32-based control panel using an OLED display, joystick navigation, sound sensor, and multiple LEDs.

---

## ⚙️ Features
- OLED menu system
- Sound detection mode
- RGB LED control mode
- Light sensor mode
- Buzzer alerts
- Magic Light Cup detection
- Joystick navigation

---

## 🔌 Hardware Used
- ESP32 Dev Board
- 0.96" OLED Display (I2C)
- Joystick Module
- Sound Sensor
- Magic Light Cup Module
- RGB LED
- 2-color LED
- Flash LED
- Buzzer

---

## 📌 Pin Connections

### OLED (I2C)
- SDA → GPIO 21
- SCL → GPIO 22
- VCC → 3.3V
- GND → GND

### Inputs
- Joystick Y → GPIO 35
- Menu Button → GPIO 33
- Sound Sensor → GPIO 36
- Light Cup → GPIO 13

### Outputs
- Buzzer → GPIO 14
- RGB LED → GPIO 25, 26, 27
- 2-color LED → GPIO 16, 17
- Flash LED → GPIO 4

---

## 🚀 How It Works
Use joystick to navigate menu:
- SOUND MODE → detects sound level
- RGB MODE → controls LED colors
- LIGHT MODE → detects tilt/light cup state

---

## 🛠 Requirements
- Arduino IDE
- ESP32 Board Package
- Libraries:
  - Adafruit SSD1306
  - Adafruit GFX

---

## 📷 Project Status
✔ Fully working version (tested on ESP32)
