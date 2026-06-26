# ECE 306 Embedded Systems Project — Autonomous Car

![MCU](https://img.shields.io/badge/MCU-MSP430FR2355-red)
![Interface](https://img.shields.io/badge/ESP32-BLE%2FWiFi-green)
![Language](https://img.shields.io/badge/Language-C-blue)
![System](https://img.shields.io/badge/Type-Autonomous%20Embedded%20System-lightgrey)

Table of Contents
Overview
Features
Hardware
Software
Images
Videos
License
Contact

## Overview
This MSP430 Embedded Car is a class project built around the MSP430FR2355 microcontroller along with supporting peripherals to achieve both remote-controlled operation and autonomous behavior. The system is designed to demonstrate embedded C programming applied to a physical platform, including motor control and black-line detection/following.

## Features
PWM-based control of vehicle motion  
DAC-based output for smoother and more stable movement  
Calibrated sensor readings for improved line detection accuracy  
Real-time data handling using interrupts (ADC, timers, GPIO)  
IR sensor-based line detection and tracking logic  
Wireless control support using an ESP32 IoT module  
Modular firmware structure for easier development and updates  

## Hardware
MSP430FR2355 microcontroller  
LCD display module  
FET driver board  
DC motors  
IR emitter and detector sensors  
ESP32 IoT module  

## Software
The project was developed using Code Composer Studio version 12.8.1
