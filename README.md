# Mini Display Encoder Testing Tool

## Overview
The Mini Display Encoder Testing Tool is a diagnostic device developed in collaboration with US Digital as part of a university capstone project. This tool provides a visual interface for testing and troubleshooting encoders before sending them for repairs, helping to streamline the maintenance process.

## Features
- Real-time encoder signal visualization
- Multiple display test patterns
- Interactive graphical interface
- Compact and portable design
- Support for SSD1306 OLED display

## Hardware Requirements
- Arduino-compatible microcontroller
- SSD1306 OLED Display
- Connection pins:
  - MOSI: Pin 11
  - CLK: Pin 12
  - DC: Pin 10
  - CS: Pin 0
  - RESET: Pin 8

## Software Dependencies
- SPI Library
- Wire Library
- Adafruit GFX Library
- Adafruit SSD1306 Library

## Display Capabilities
- Screen Height: 32 pixels
- Multiple drawing functions:
  - Line drawing
  - Rectangle rendering
  - Circle drawing
  - Triangle rendering
  - Character display
  - Bitmap animation
  - Scrolling text

## Installation
1. Install required libraries through Arduino IDE
2. Connect the OLED display using the specified pin configuration
3. Upload the code to your Arduino board
4. Power on the device

## Usage
The device will automatically run through a series of display tests demonstrating:
- Basic pixel operations
- Line drawing patterns
- Geometric shapes (rectangles, circles, triangles)
- Text rendering
- Scrolling animations
- Bitmap display

## Troubleshooting Functions
- Visual feedback for encoder signals
- Signal integrity testing
- Real-time response monitoring
- Pattern generation for encoder testing

## Contributing
This project was developed as part of a university capstone program in partnership with US Digital. For modifications or improvements, please submit a pull request.

## License
[Insert appropriate license information]

## Acknowledgments
- US Digital for project sponsorship
- [Your University Name] Capstone Program
- Adafruit for display libraries
