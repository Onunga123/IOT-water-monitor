# IoT-Based Offline Real-Time Water Quality Monitoring System

A compact ESP32-based water quality monitoring project designed for offline use in remote or low-connectivity environments. The system measures water temperature and Total Dissolved Solids (TDS), then displays the results on a local web dashboard hosted by the ESP32 itself.

This project is ideal for:
- rural or off-grid water monitoring
- field testing for household or agricultural water sources
- educational IoT and embedded systems projects
- low-cost continuous water quality checks without internet access

## Features

- ESP32 Wi‑Fi access point mode (no internet required)
- Real-time TDS measurement
- DS18B20 temperature sensor support
- Offline dashboard served from the ESP32
- Water quality status classification:
  - Safe
  - Caution
  - Unsafe
- Automated sensor readings every 3 seconds
- Dashboard refreshes every 5 seconds

## Hardware Required

- ESP32 development board
- TDS sensor module
- DS18B20 temperature sensor
- 4.7k pull-up resistor for DS18B20
- Breadboard and jumper wires
- Power source for ESP32

## Pin Configuration

The project is configured as follows:

- TDS sensor output -> GPIO34
- DS18B20 data pin -> GPIO4
- DS18B20 power -> 3.3V
- DS18B20 ground -> GND
- TDS sensor VCC -> 3.3V (as used in this code)
- TDS sensor GND -> GND

## Software Requirements

Install the following Arduino libraries in your Arduino IDE:

- WiFi
- WebServer
- OneWire
- DallasTemperature

## Access Point Configuration

The ESP32 starts its own Wi‑Fi hotspot:

- SSID: `WaterSafe`
- Password: `12345678`

After uploading the code, connect your phone/laptop to this Wi‑Fi network and open the ESP32's IP address shown in the Serial Monitor.

Example:
- Open the Serial Monitor
- Look for the access point IP, such as `192.168.4.1`
- Then visit:
  `http://192.168.4.1/`

## Water Quality Logic

The system evaluates the results using thresholds defined in the code:

- If TDS > 500 or temperature < 10°C or temperature > 40°C:
  - Status = `Unsafe`
- Else if TDS > 300 or temperature < 15°C or temperature > 35°C:
  - Status = `Caution`
- Else:
  - Status = `Safe`

## Project Structure

```text
IOT-water-monitor/
├── ESP32_Water_Quality_Monitor/
│   └── ESP32_Water_Quality_Monitor.ino
├── libraries/
└── README.md
```

## How It Works

1. The ESP32 boots and creates a local access point.
2. The DS18B20 sensor reads water temperature.
3. The TDS sensor reads analog values and converts them into ppm.
4. The values are evaluated against the threshold logic.
5. The dashboard updates automatically with the latest values.
6. The user can view water quality from any device connected to the ESP32 hotspot.

## Example Dashboard

The web page displays:

- Temperature in °C
- TDS in ppm
- Status indicator with color coding:
  - Green for Safe
  - Orange for Caution
  - Red for Unsafe

## Author

Onunga Christopher

## License

This project is licensed under the MIT License.

MIT License

Copyright (c) 2026 Onunga Christopher

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## Notes

- The TDS conversion formula is based on a simple calibration approach and may require adjustment depending on sensor characteristics and water chemistry.
- This project is intended for learning and prototyping.
- For field deployment, calibration and sensor validation should be performed against a known reference instrument.

## Future Improvements

Possible upgrades include:
- MQTT or local data logging
- SD card storage
- battery-powered operation
- pH and turbidity sensing
- alert buzzer or relay control
- better calibration routines

## Disclaimer

This project is provided for educational and prototype use. Hardware calibration and testing should be done before using it for real-world water safety decisions.
