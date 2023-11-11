# Automated Plant Watering System

This project is an automated plant watering system using Arduino, DHT sensors for measuring temperature and humidity, and RTC for scheduling watering times.

## Table of Contents
- [Components](#components)
- [Installation](#installation)
- [Usage](#usage)
- [Configuration](#configuration)
- [Contributing](#contributing)
- [License](#license)

## Components
- Arduino board
- DHT sensors (DHT11)
- Moisture sensors
- RTC (Real-Time Clock) module (DS3231)
- LDR sensor
- Water pumps
- Resistors, wires, and other necessary components

## Installation
1. **Hardware Setup:**
    - Connect the components as per the circuit diagram provided in the repository.
2. **Software Setup:**
    - Upload the Arduino sketch (`plant_watering_system.ino`) to your Arduino board using the Arduino IDE or any compatible IDE.
    - Make sure to install necessary libraries like DHT, Adafruit_Sensor, and RTClib.

## Usage
1. **Power up the system:**
    - Connect the Arduino board to a power source.
2. **Monitoring:**
    - The system will periodically read temperature, humidity, and soil moisture levels.
    - LDR sensor measures light intensity.
3. **Watering:**
    - Water pumps will be activated based on the configured schedule and soil moisture levels.
4. **Logging:**
    - Real-time data, including temperature, humidity, and soil moisture levels, will be logged to the Serial Monitor.

## Configuration
- **Pin Configuration:**
    - Adjust the pins and sensor types in the code if your setup is different.
- **Date and Time:**
    - Set the current date and time in the `RTC.adjust(DateTime(2020,4,29, 10,59,50));` line.
- **Watering Schedule:**
    - Configure the watering schedule and soil moisture threshold in the code.
