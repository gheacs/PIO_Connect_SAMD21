# Simple Wearable Device README

This README provides an overview of a simple wearable device code written for an Arduino-compatible board using the PlatformIO development environment. This device combines temperature, humidity, pressure, and accelerometer data and displays it on an OLED screen while alerting you with a buzzer when the temperature exceeds a predefined threshold.

## Table of Contents

- [Hardware Requirements](#hardware-requirements)
- [Installation and Setup](#installation-and-setup)
- [Usage](#usage)
- [Contributing](#contributing)

## Hardware Requirements

To use this code, you will need the following hardware components:

- An Arduino-compatible board (e.g., Seeeduino XIAO)
- BME280 sensor for temperature, humidity, and pressure data
- MPU6050 accelerometer sensor
- SSD1306 OLED display
- A buzzer
- Appropriate wiring and power source

## Installation and Setup

1. Make sure you have PlatformIO installed on your computer. If not, you can download and install it from [PlatformIO Official Website](https://platformio.org/).

2. Clone or download the project code repository to your local machine.

3. Open the project folder using PlatformIO.

4. Ensure that you have the required libraries installed. These libraries include:
   - Adafruit GFX Library
   - Adafruit SSD1306
   - Adafruit BME280 Library
   - Adafruit MPU6050
   - Wire (standard Arduino library)

   You can install these libraries using the PlatformIO Library Manager or directly from the Arduino IDE if you prefer.

5. Connect your Arduino-compatible board to your computer via a USB cable.

6. Modify the code as needed to customize the behavior of your wearable device. For example, you can adjust the temperature threshold or change the data display format.

## Usage

1. Upload the modified code to your Arduino-compatible board using PlatformIO. Ensure that you have selected the correct board and COM port.

2. Once the code is uploaded successfully, the wearable device will start collecting data from the sensors and displaying it on the OLED screen.

3. If the temperature reading exceeds the predefined threshold (TEMP_THRESHOLD in the code), the buzzer will activate to alert you.

4. Data is also sent to the serial monitor for debugging purposes. You can view the data by opening the serial monitor in PlatformIO or the Arduino IDE.

5. Customize and expand upon this code to suit your specific project needs.

## Contributing

Contributions to this project are welcome. If you find any issues or want to improve the code, please open an issue or submit a pull request on the project's GitHub repository.


