# Weather Station using Xtensa LX7-based ESP32-S3 microcontroller (In progress)

A custom weather station project designed to read environmental data using multiple sensors and display/log it through various interfaces. This project is written without using external libraries, directly following sensor datasheets and protocols — for full control and deeper embedded systems understanding.

## Current status
**In Progress** – Actively developing and adding features.

## Implemented:
- **MQ135** – Air quality/gas sensor (reads analog values, prepped for calibration).

- **Si7021** – Temperature and humidity sensor via I²C (bare-metal driver).

- **BMP280** – Currently being integrated (pressure via I²C).

## Planned Features:
- **LCD Display** – Show current temperature, humidity, air quality in real-time.

- **Wi-Fi** Communication – Send sensor data to a computer or cloud (via ESP module or similar).

- **SD Card Logging** – Store data locally if Wi-Fi is unavailable or unreliable.
