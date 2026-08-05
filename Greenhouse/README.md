# Automated Greenhouse Climate Control System

## Overview
This project is an automated climate control system designed for a greenhouse environment. Built on a bare-metal ATmega32 microcontroller, it continuously monitors environmental data and autonomously manages cooling, heating, and irrigation actuators. The system also features a manual override interface and an LCD for real-time monitoring.

## Hardware Components
* **Microcontroller:** ATmega32
* **Sensors:** LM35 Temperature Sensor
* **Display:** 16x2 Character LCD (wired in 8-bit mode)
* **Inputs:** 
  * Matrix Keypad (for setting target environmental thresholds)
  * 3x Tactile Pushbuttons (for manual overrides: Fan, Heater, Pump)
* **Actuators:**
  * Water Pump (Simulated via DC Motor)
  * Cooling Fan (Simulated via DC Motor)
  * Heater (Simulated via Lamp)
* **Power & Isolation:** NPN Transistors (e.g., 2N2222) or dedicated Motor Drivers (e.g., L293D) to isolate the ATmega32 logic pins from the high-current demands of the actuators.

## Software Architecture
The codebase is written in standard C and utilizes a layered architecture to keep hardware logic separate from the main application flow.

* **Application Layer:** A non-blocking State Machine that handles sensor polling, keypad integer conversion, and actuator triggering without trapping the microcontroller in empty loops.
* **Hardware Abstraction Layer (HAL):** Custom drivers for the Keypad, LCD, and Relays (Pump, Heater, Fan).
* **Microcontroller Abstraction Layer (MCAL):** Custom Digital Input/Output (DIO) driver that maps generic group and pin numbers to precise hardware registers (`PORTA`, `PORTB`, etc.) using bit-math macros (e.g., `DIO_TogglePin`).

## Simulation Notes (Proteus)
The system is designed and verified using Proteus ISIS. When simulating:
* Ensure the active `LM35.MDF` simulation model is installed in your Proteus library directory to prevent netlist linker errors.
* Direct connections between ATmega logic pins and heavy loads (like DC motors) will cause logic contention (yellow pins). Ensure isolation circuitry is modeled, or artificially raise the coil resistance of the simulated loads.

## Usage Guide
1. **Startup:** Upon powering the system, the 16x2 LCD initializes and the system enters its default monitoring state.
2. **Setting Thresholds:** Press the `*` key on the keypad to enter configuration mode. Enter a two-digit integer for the target Temperature, followed by a two-digit integer for the target Moisture.
3. **Monitoring:** The LCD continuously displays the current `Temp` and `Moist` values.
4. **Manual Overrides:** Use the dedicated hardware pushbuttons to manually toggle the Fan, Heater, or Water Pump. The code implements software debouncing and non-blocking wait states to ensure reliable input reading.
