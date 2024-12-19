# Mini Display Encoder Testing Tool

## Overview
A diagnostic device developed for US Digital that provides real-time visualization and testing capabilities for various types of encoders. This tool supports multiple encoder interfaces including QEI (Quadrature), Analog, and PWM, making it an essential troubleshooting instrument.

## Features
- Multiple encoder interface support:
  - Quadrature Encoder Interface (QEI)
  - Analog voltage reading
  - PWM signal processing (10-bit and 12-bit)
- Real-time position display
- Index signal detection
- Moving average filtering for stable readings
- Interactive mode selection
- Reset functionality
- SSD1306 OLED display interface

## Hardware Requirements
- Arduino-compatible microcontroller
- SSD1306 OLED Display (128x32 pixels)
- Pin Connections:
  - MOSI: Pin 11
  - CLK: Pin 12
  - DC: Pin 9
  - CS: Pin 10
  - RESET: Pin 8
  - Button 1: Pin 2
  - Button 2: Pin 3
  - Encoder A: Pin 4
  - Encoder B: Pin 5
  - Index: Pin 6
  - PWM Input: Pin 7
  - Analog Input: A0

## Software Dependencies
- SPI Library
- Wire Library
- Adafruit_GFX Library
- Adafruit_SSD1306 Library
- Bounce2 Library
- Encoder Library

## Operating Modes

### QEI Mode
- Displays quadrature encoder position
- Supports index signal reset
- Real-time position updates

### Analog Mode
- Voltage measurement (0-5V range)
- Moving average filtering
- 3-decimal precision display

### PWM Mode
- Supports both 10-bit and 12-bit resolution
- Duty cycle measurement
- Position calculation
- Filtered readings with moving average

## Usage Instructions
1. Power on the device
2. Use Button 1 to cycle through available modes
3. Press Button 2 to select desired mode
4. In QEI mode, Button 2 acts as reset
5. Display automatically updates with current readings

## Development
- Written in Arduino C++
- Modular design for easy maintenance
- Debounced button inputs
- Interrupt-driven index detection

## Troubleshooting Features
- Real-time signal monitoring
- Noise filtering through averaging
- Visual feedback for all measurements
- Auto-scaling display for different modes

## Contributing
This is a capstone project developed for US Digital. For modifications or improvements, please submit a pull request.

## License
[Insert appropriate license information]

## Acknowledgments
- US Digital for project sponsorship
- Adafruit for display and sensor libraries
