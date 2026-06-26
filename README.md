# ECE 306 Embedded Systems Project — Smart Car

![Language](https://img.shields.io/badge/Language-C/C++-blue)
![Platform](https://img.shields.io/badge/Microcontroller-ESP32--S3-green)
![Domain](https://img.shields.io/badge/Domain-Embedded%20Systems-lightgrey)
![Control](https://img.shields.io/badge/Control-GPIO%20%2F%20PWM%20%2F%20ADC-orange)

---

## Overview
This project is an embedded systems implementation developed for **ECE 306**, focusing on microcontroller-based control of a small robotic car platform.

The system integrates motor control, sensor input handling, and basic communication logic using an ESP32-S3 microcontroller. The emphasis of the project is on embedded C programming, peripheral configuration, and structured firmware design.

---

## Key Features
- PWM-based DC motor control for speed and direction management  
- GPIO handling for digital input/output interfacing  
- ADC-based sensor data acquisition (where applicable in the build)  
- Modular firmware organization separating drivers and application logic  
- Interrupt-based or polling-based input handling depending on subsystem  
- Basic communication support for external control/monitoring (WiFi or serial, depending on configuration)  
- Configurable code structure to support hardware iteration  

---

## Hardware Used
- ESP32-S3 microcontroller  
- DC motors with motor driver circuit  
- Power regulation and distribution circuitry  
- Sensor modules (IR / analog sensors depending on configuration)  
- Supporting passive components and wiring infrastructure  

---

## Software Environment
- Embedded C / C++ (ESP-IDF or Arduino framework depending on setup)  
- Development using Eclipse / VS Code / PlatformIO (project-dependent)  
- Peripheral APIs: GPIO, PWM, ADC, timers, WiFi (if enabled)  

---

## Code Organization
The project is structured to separate hardware control from application logic:
