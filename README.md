# Autonomous Car - ECE 306 Embedded Systems Project

![MCU](https://img.shields.io/badge/MCU-MSP430FR2355-red)
![Interface](https://img.shields.io/badge/ESP32-BLE%2FWiFi-green)
![Language](https://img.shields.io/badge/Language-C-blue)
![System](https://img.shields.io/badge/Type-Autonomous%20Embedded%20System-yellow)

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Hardware](#hardware)
- [Software](#software)
- [Notes](#notes)

## Overview
This MSP430 Embedded Car is a class project built around the MSP430FR2355 microcontroller along with supporting peripherals to achieve both remote-controlled operation and autonomous behavior. The system demonstrates embedded C programming applied to a physical hardware platform, including motor control and black-line detection/following.

## Features
- PWM-based control of vehicle motion  
- DAC-based output for smoother and more stable movement  
- Calibrated sensor readings for improved line detection accuracy  
- Real-time interrupt-driven processing (ADC, timers, GPIO)  
- IR sensor-based line detection and tracking logic  
- Wireless control support using an ESP32 IoT module  
- Modular firmware structure for easier development and updates  

## Hardware
- MSP430FR2355 microcontroller  
- LCD display module  
- FET driver board  
- DC motors  
- IR emitter and detector sensors  
- ESP32 IoT module  

## Software
Developed using Code Composer Studio v12.8.1

## Notes
- Autonomous behavior is implemented at the firmware level using sensor feedback and state-based control logic  
- Wireless module is used for communication and external interaction support  
