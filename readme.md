# BikeComputer v1

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Hardware: ESP32-S3](https://img.shields.io/badge/Hardware-ESP32--S3-red.svg)](https://www.waveshare.com/esp32-s3-nano.htm)
[![Language: C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Framework: PlatformIO](https://img.shields.io/badge/Framework-PlatformIO-orange.svg)](https://platformio.org/)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](../../issues)

A smart, standalone ESP32-based bike computer with touch interface, offline session recording, and integrated web server.

---

## Key Features
Real-time display of current speed, average speed, and top speed (per session and overall)
- Accurate measurement of trip distance and total elapsed time (per session and overall)
- Live monitoring and display of outdoor temperature
- Recording Individual Trip Sessions
- Local storage of trips directly on the ESP32
- Integrated web server (in STA or client mode)
- Downloading ride data via the website
- Full control via touchscreen
-Various screens (main menu, live display, sessions screen, settings)
---

## Hardware Components

| Component | Model|
|---|---|
| **Microcontroller** | ESP32-S3-Nano from Waveshare |
| **Display & Touch** | 2.8 inch TFT SPI ModuleILI9341 (with Touch) |
| **Temperature Sensor** | BMP280 (I²C) |
| **Compass / Magnetometer** | GY-271 QMC5883L (I²C) |
| **GPS Module** | GY-GPS6MV2 Neo-M8M (with external antenna) |
| **Storage** | 5V SD Card Module Open-Smart |

---
## Wiring


| Component | Module Pin | ESP32-S3 Pin | GPIO |
|---|---|---|---|
| **TFT Display (ILI9341)** | VCC / GND | 3V3 / GND | - |
| | LED | 3V3 | - |
| | SCK | D13 | GPIO48 |
| | MOSI / SDI | D11 | GPIO38 |
| | MISO / SDO | D12 | GPIO47 |
| | CS | - | GPIO5 |
| | DC | - | GPIO9 |
| | RST | D8 | GPIO17 |
| **Touch (Display)** | T_CLK | D13 | GPIO48 |
| | T_DIN | D11 | GPIO38 |
| | T_DO | D12 | GPIO47 |
| | T_CS | D7 | GPIO10 |
| **SD Card Module** | CS | D3 | GPIO6 |
| | SCK / MOSI / MISO | D13 / D11 / D12 | GPIO48 / 38 / 47 |
| **I²C Sensors (BMP280 & GY-271)** | VCC / GND | 3V3 / GND | - |
| | SDA | A4 | GPIO11 |
| | SCL | A5 | GPIO12 |
| **GPS (GY-GPS6MV2)** | VCC / GND | 3V3 / GND | - |
| | RX | D1 / TXD | GPIO43 |
| | TX | D0 / RXD | GPIO44 |

---
## License & Credits

This project is open-source and available under the [MIT License](LICENSE).

If you use, modify, or feature this project, please provide a link back to this repository!

made by SimDev
