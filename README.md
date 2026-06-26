# ECE 306 Embedded Systems Project — Autonomous Car

![MCU](https://img.shields.io/badge/MCU-MSP430FR2355-red)
![Interface](https://img.shields.io/badge/ESP32-BLE%2FWiFi-green)
![Language](https://img.shields.io/badge/Language-C-blue)
![System](https://img.shields.io/badge/Type-Autonomous%20Embedded%20System-lightgrey)

## Overview
This project was developed for ECE 306 and implements an autonomous embedded car system using a dual-microcontroller architecture.

The TI MSP430FR2355 serves as the primary controller responsible for real-time motor control and sensor processing. An ESP32 module is used as a wireless interface (BLE/WiFi depending on configuration) for external communication and debugging support.

The system focuses on embedded C programming, peripheral configuration, and integrating autonomous decision-making at the firmware level.

## Key Features
- Autonomous motion control based on sensor input  
- PWM-based DC motor control using MSP430 timers  
- GPIO-based motor direction control  
- ADC-based sensor data acquisition  
- Real-time control loop for decision making  
- Interrupt or polling-based sensor handling depending on subsystem design  
- Modular firmware architecture separating control, drivers, and communication  
- UART communication between MSP430 and ESP32  
- ESP32 BLE/WiFi interface for monitoring or external interaction  

## Hardware
- TI MSP430FR2355 microcontroller (primary control unit)  
- ESP32 module (BLE/WiFi communication interface)  
- DC motors with motor driver circuit  
- Sensor array (IR / analog depending on implementation)  
- Power regulation circuitry  
- Supporting passive components and wiring  

## Software
- Embedded C (Code Composer Studio for MSP430)  
- ESP32 firmware using Arduino framework or ESP-IDF  
- MSP430 peripherals: GPIO, PWM, ADC, timers  
- ESP32 communication stack: UART + BLE/WiFi

## System Architecture

The project follows a layered embedded system design consisting of application logic, hardware drivers, and platform configuration.

### Source Layer (`src/`)
This layer contains all core firmware implementation including control logic, peripheral drivers, and system behavior.

- `main.c` — Entry point of the program and main execution loop  
- `adc.c` — ADC configuration and sensor data acquisition  
- `clocks.c` — System clock initialization and configuration  
- `Display.c` — Display/LCD interface handling  
- `init.c` — System initialization routines  
- `init_cmds.c` — Initialization command sequences  
- `led.c` — LED control functions  
- `movement_statemachine.c` — Movement decision state machine  
- `ports.c` — GPIO port configuration and control  
- `StateMachine.c` — High-level system state management  
- `switches.c` — Input handling for switches/buttons  
- `system.c` — System-level configuration and utilities  
- `timers.c` — Timer setup and interrupt handling  
- `uart.c` — UART communication interface  
- `wheels.c` — Motor and wheel control logic  

---

### Interface Layer (`includes/`)
This layer defines all shared interfaces, macros, and hardware abstraction headers used across the project.

- `adc.h` — ADC function declarations and definitions  
- `functions.h` — General-purpose function prototypes  
- `LCD.h` — Display interface definitions  
- `macros.h` — System-wide constants and macros  
- `ports.h` — GPIO definitions and mappings  
- `wheels.h` — Motor control interface definitions  

---

### Configuration Layer (`linker/`)
This layer defines the memory layout and hardware-specific configuration for the MSP430 microcontroller.

- `lnk_msp430fr2355.cmd` — Linker script defining memory sections and allocation
