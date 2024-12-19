// Include necessary libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Bounce2.h>
#include <Encoder.h>

// Define OLED display dimensions and pin connections
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_DC 9
#define OLED_CS 10 //this pin is changed from 10 to 7, since 10 is a slave select pin for SPI on the UNO
#define OLED_RESET 8

// For Hardware SPI use these pins for the the Arduino UNO
// MOSI: pin 11
// SCK: pin 13

// Initialize OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

// Define button pins and analog input pin
const int buttonPin1 = 2;
const int buttonPin2 = 3;
const int analogInputPin = A0;
const int pwmInputPin = A1;

// Define QEI encoder pins
const int encoderPinA = 4;
const int encoderPinB = 5;
const int encoderIndexPin = 6;

// Define PWM encoder pins
const int encoderPWM = 7;

// Initialize Encoder object
Encoder myEncoder(encoderPinA, encoderPinB);

// Initialize debouncers for buttons
Bounce button1Debouncer = Bounce();
Bounce button2Debouncer = Bounce();

// Global variables for mode selection and display
int selectedOption = 0;
const unsigned long debounceDelay = 80;
bool inSelectionMode = true;
bool modeSelected = false;
int selectedMode = 0; // 0 = QEI, 1 = ANALOG, 2 = PWM 10, 3 = PWM 12
volatile long encoderPosition = 0;
int pwmPosition = 0;

// Define constants for debouncing
const unsigned long DEBOUNCE_INTERVAL = 5;  // Debounce interval in milliseconds
const unsigned int NUM_READINGS = 10;      // Number of readings for moving average

unsigned long previousMillis = 0;   // Variable to store the previous time
unsigned long ton = 0;              // Variable to store ton time
unsigned long toff = 0;             // Variable to store toff time
unsigned int readIndex = 0;         // Index for circular buffer of readings
int readings[NUM_READINGS];        // Circular buffer for readings
// int pwmPosition = 0;               // Variable to store calculated PWM position

// Global veriable for calculating moving average of analog voltage
const int numReadings = 10;
int total = 0;
int average = 0;

// Function prototypes
void displayOperatingModeSelection();
void displaySelectedMode(String mode);
void resetEncoder();
void updateAnalogVoltage();
void calculatePWMPosition();
void displayPosition(bool);

// Setup function
void setup() {
  // Initialize serial communication and SPI
  Serial.begin(9600);
  SPI.begin(OLED_CS);

  // Set pin modes for buttons and encoder
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderIndexPin, INPUT_PULLUP);

  // Attach debouncers to buttons and set debounce interval
  button1Debouncer.attach(buttonPin1, INPUT_PULLUP);
  button1Debouncer.interval(debounceDelay);
  button2Debouncer.attach(buttonPin2, INPUT_PULLUP);
  button2Debouncer.interval(debounceDelay);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.display();
  delay(1500);

  // Display mode selection screen
  display.clearDisplay();
  displayOperatingModeSelection();

  // Attach interrupt for encoder index pin
  attachInterrupt(digitalPinToInterrupt(encoderIndexPin), resetEncoder, FALLING);
}

// Main loop function
void loop() {
  // Update debouncers for buttons
  button1Debouncer.update();
  button2Debouncer.update();

  // Check for button presses
  if (button1Debouncer.fell()) {
    selectedOption = (selectedOption + 1) % 4; //alternates between 0 and 1 depending on button press (0 = QEI, 1 = ANALOG)
    modeSelected = false; // Reset modeSelected flag
    displayOperatingModeSelection();
  }

  if (button2Debouncer.fell() && !modeSelected) {
    selectedMode = selectedOption; // Set the mode to the selected option
    modeSelected = true; // Set modeSelected flag
    displaySelectedMode(selectedMode);
  }

  // Execute selected mode only if a mode is selected
  if (modeSelected) {
    switch (selectedMode) {
      case 0: // QEI
        encoderPosition = myEncoder.read(); // Read the encoder position
        if (button2Debouncer.fell()) {
          resetEncoder(); // Reset the encoder position
          displayPosition(true); // Update the display with the reset message
        } else {
          displayPosition(false); // Continuously update the display without the reset message
        }
        break;
      case 1: // ANALOG
        updateAnalogVoltage();
        break;
      case 2: // PWM 10 BIT
      case 3: // PWM 12 BIT
        calculatePWMPosition();
        break;
    }
  }
}

// Function to display the operating mode selection screen
void displayOperatingModeSelection() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  // display.setCursor(12, 0); // Set the text starting position
  // display.print("Select Mode");
  display.setTextColor(selectedOption == 0 ? SSD1306_BLACK : SSD1306_WHITE, selectedOption == 0 ? SSD1306_WHITE : SSD1306_BLACK);
  display.setCursor(36, 0);
  display.print("QEI");
  display.setTextColor(selectedOption == 1 ? SSD1306_BLACK : SSD1306_WHITE, selectedOption == 1 ? SSD1306_WHITE : SSD1306_BLACK);
  display.setCursor(60, 0);
  display.print("ANALOG");
  display.setTextColor(selectedOption == 2 ? SSD1306_BLACK : SSD1306_WHITE, selectedOption == 2 ? SSD1306_WHITE : SSD1306_BLACK);
  display.setCursor(36, 12);
  display.print("PWM 10 BIT");
  display.setTextColor(selectedOption == 3 ? SSD1306_BLACK : SSD1306_WHITE, selectedOption == 3 ? SSD1306_WHITE : SSD1306_BLACK);
  display.setCursor(36, 24);
  display.print("PWM 12 BIT");
  display.display();
}

// Function to reset the encoder position when the index pin is triggered
void resetEncoder() {
  myEncoder.write(0); // Reset the encoder position
}

void updateAnalogVoltage() {
  delay(5); // added short delay to have better voltage reading/reduce jitter

  // calculating the average
  total -= readings[readIndex];
  readings[readIndex] = analogRead(analogInputPin);
  total += readings[readIndex];
  readIndex = (readIndex + 1) % numReadings;
  average = total / numReadings;
  float voltage = (average * 5) / 1023.0;

  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 16);
  display.fillRect(0, 16, 128, 16, SSD1306_BLACK); // Clear the previous voltage reading
  display.print("Voltage: ");
  display.print(voltage, 3); // Display voltage with 3 decimal places
  display.print(" V");
  display.display();
}


void calculatePWMPosition() {
  unsigned long currentMillis = millis();  // Get current time
  if (currentMillis - previousMillis >= DEBOUNCE_INTERVAL) {
    // Capture ton and toff times
    ton = pulseIn(encoderPWM, HIGH);
    toff = pulseIn(encoderPWM, LOW);

    // Calculate PWM position
    int pwmResolution = 0;
    int x = 0;
    float dutyRatio = 0.0;
    if (selectedMode == 2) {
      pwmResolution = 1023;
      x = ((ton * 1026) / (ton + toff)) - 1;
      if (x <= 1022) {
        pwmPosition = x;
      } else if (x == 1024) {
        pwmPosition = 1023;
      } else {
        pwmPosition = -1; // Handle unexpected values
      }
    } else {
      pwmResolution = 4095;
      x = ((ton * 4098) / (ton + toff)) - 1;
      if (x <= 4094) {
        pwmPosition = x;
      } else if (x == 4096) {
        pwmPosition = 4095;
      } else {
        pwmPosition = -1; // Handle unexpected values
      }
    }

    // Update readings buffer
    readings[readIndex] = pwmPosition;
    readIndex = (readIndex + 1) % NUM_READINGS;

    // Calculate moving average
    int total = 0;
    for (int i = 0; i < NUM_READINGS; i++) {
      total += readings[i];
    }
    int average = total / NUM_READINGS;

    // Calculate duty ratio
    dutyRatio = (float)average / pwmResolution;

    // Update display, etc.
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Mode: PWM");
    display.setCursor(64, 0);
    display.print(selectedMode == 2 ? "10-Bit" : "12-Bit");
    display.setCursor(0, 12);
    display.print("Duty: ");
    display.print(dutyRatio * 100, 2);
    display.print("%");
    display.setCursor(0, 24);
    display.print("Position: ");
    display.print(average);
    display.display();

    previousMillis = currentMillis;  // Update previous time
  }
}


void displayPosition(bool showReset) {
  long position = encoderPosition; // Read the encoder's position

  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 16);
  display.fillRect(0, 16, 128, 16, SSD1306_BLACK); // Clear the previous position
  display.print("Position: ");
  display.print(position);
  if (showReset) {
    display.setCursor(96, 0);
    display.print("Reset");
  } else {
    display.fillRect(96, 0, 32, 8, SSD1306_BLACK); // Clear the reset message
  }
  display.display();
}

// Function to display the selected mode
void displaySelectedMode(int mode) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Mode:");
  display.setCursor(64, 0);
  display.print(mode == 0 ? "QEI" : mode == 1 ? "ANALOG" : mode == 2 ? "PWM 10-bit" : "PWM 12-bit");
  display.setCursor(64, 8);
  display.display();
}