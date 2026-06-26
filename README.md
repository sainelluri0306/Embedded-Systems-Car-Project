# ECE 306 Embedded Systems Project — Smart Car

![Language](https://img.shields.io/badge/Language-C/C++-blue)
![MCU](https://img.shields.io/badge/MCU-MSP430FR2355-red)
![Interface](https://img.shields.io/badge/Wireless-ESP32%20BLE%2FWiFi-green)
![Domain](https://img.shields.io/badge/Domain-Embedded%20Systems-lightgrey)

---

## Overview
This project was developed for **ECE 306** and focuses on embedded control of a small robotic car platform using a dual-microcontroller setup.

The **TI MSP430FR2355** is used as the primary controller for real-time motor and sensor handling, while an **ESP32 module** is used as a wireless interface for communication (BLE/WiFi depending on configuration).

The project emphasizes embedded C programming, peripheral configuration, and system-level integration between hardware components.

---

## Key Features
- PWM-based DC motor control using MSP430 timers  
- GPIO-based direction control for motor driver interface  
- ADC-based sensor sampling for analog inputs  
- Interrupt and/or polling-based input handling depending on subsystem design  
- Modular firmware structure separating control logic and hardware drivers  
- BLE/WiFi communication handled through ESP32 interface module  
- Serial or wireless communication bridge between MSP430 and ESP32  
- Configurable architecture for testing different control behaviors  

---

## Hardware Used
- TI **MSP430FR2355** microcontroller (primary control unit)  
- ESP32 module (BLE / WiFi communication interface)  
- DC motors with motor driver circuit (H-bridge or equivalent)  
- Power regulation circuitry  
- Sensor modules (IR / analog sensors depending on configuration)  
- Supporting passive components and wiring  

---

## Software Environment
- Embedded C (MSP430 code using Code Composer Studio)  
- ESP32 firmware using Arduino framework or ESP-IDF (based on implementation)  
- GPIO, PWM, ADC, timers (MSP430 peripherals)  
- UART / BLE / WiFi communication stack (ESP32 side)  

---

## Code Organization
