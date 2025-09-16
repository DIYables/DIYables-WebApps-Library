/*
 * DIYables WebApp Library - Web Digital Pins Example
 * 
 * This example demonstrates the Web Digital Pins feature with automatic command handling:
 * - Control output pins 0-13 via web interface  
 * - Monitor input pins 0-13 in real-time
 * - Individual pin ON/OFF control for outputs
 * - Real-time pin status feedback for inputs
 * - Bulk operations (All ON, All OFF, Toggle All) for outputs
 *
 * Hardware: Arduino Uno R4 WiFi or DIYables STEM V4 IoT
 * 
 * Setup:
 * 1. Update WiFi credentials below
 * 2. Upload the sketch to your Arduino
 * 3. Open Serial Monitor to see the IP address
 * 4. Navigate to http://[IP_ADDRESS]/webdigitalpins
 */

#include <DIYablesWebApps.h>

// WiFi credentials - UPDATE THESE WITH YOUR NETWORK
const char WIFI_SSID[] = "YOUR_WIFI_SSID";
const char WIFI_PASSWORD[] = "YOUR_WIFI_PASSWORD";

// Create WebApp server and page instances using platform abstraction
UnoR4ServerFactory serverFactory;
DIYablesWebAppServer webAppsServer(serverFactory, 80, 81);
DIYablesHomePage homePage;
DIYablesWebDigitalPinsPage webDigitalPinsPage;

// Array to store the state of each digital pin (0-13). Index corresponds to pin number.
int pinStates[16] = { 0 };  // Initialize all states to LOW (0)

void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.println("DIYables WebApp - Web Digital Pins Example");

  // Add home and digital pins pages
  webAppsServer.addApp(&homePage);
  webAppsServer.addApp(&webDigitalPinsPage);

  // Optional: Add 404 page for better user experience
  webAppsServer.setNotFoundPage(DIYablesNotFoundPage());

  // Pin Configuration Examples:
  // Method 1: Enable specific pins individually for output control
  webDigitalPinsPage.enablePin(0, WEB_PIN_OUTPUT);  // Enable pin 0 (TX - use with caution)
  webDigitalPinsPage.enablePin(1, WEB_PIN_OUTPUT);  // Enable pin 1 (RX - use with caution)
  webDigitalPinsPage.enablePin(2, WEB_PIN_OUTPUT);
  webDigitalPinsPage.enablePin(3, WEB_PIN_OUTPUT);
  webDigitalPinsPage.enablePin(4, WEB_PIN_OUTPUT);
  //webDigitalPinsPage.enablePin(5, WEB_PIN_OUTPUT);  // Comment/uncomment to disable/enable
  //webDigitalPinsPage.enablePin(6, WEB_PIN_OUTPUT);  // Comment/uncomment to disable/enable
  webDigitalPinsPage.enablePin(13, WEB_PIN_OUTPUT);  // Enable pin 13 (built-in LED)

  // Method 2: Enable pins for input monitoring
  webDigitalPinsPage.enablePin(8, WEB_PIN_INPUT);
  webDigitalPinsPage.enablePin(9, WEB_PIN_INPUT);
  //webDigitalPinsPage.enablePin(10, WEB_PIN_INPUT);  // Comment/uncomment to disable/enable
  //webDigitalPinsPage.enablePin(11, WEB_PIN_INPUT);  // Comment/uncomment to disable/enable

  // Method 3: Enable all pins at once (uncomment to use)
  // for (int pin = 0; pin <= 13; pin++) {
  //   webDigitalPinsPage.enablePin(pin, WEB_PIN_OUTPUT);  // or WEB_PIN_INPUT as needed
  // }

  // Method 4: Enable pins in a range using for loop (uncomment to use)
  // for (int pin = 7; pin <= 11; pin++) {
  //   webDigitalPinsPage.enablePin(pin, WEB_PIN_OUTPUT);  // or WEB_PIN_INPUT as needed
  // }

  // Initialize enabled pins
  int outputPins[] = { 0, 1, 2, 3, 4, 13 };  // Note: Pins 0,1 are TX/RX - use with caution
  for (int i = 0; i < 6; i++) {
    int pin = outputPins[i];
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    pinStates[pin] = LOW;
  }

  int inputPins[] = { 8, 9 };
  for (int i = 0; i < 2; i++) {
    int pin = inputPins[i];
    pinMode(pin, INPUT);  // Use INPUT_PULLUP if needed
    pinStates[pin] = digitalRead(pin);
  }

  // Start the WebApp server
  if (!webAppsServer.begin(WIFI_SSID, WIFI_PASSWORD)) {
    while (1) {
      Serial.println("Failed to start WebApp server!");
      delay(1000);
    }
  }

  // Return the current state to display on Web App
  webDigitalPinsPage.onPinRead([](int pin) {
    return pinStates[pin];  // Return the current state of the pin
    // You can implement custom read logic here if needed
  });

  // Handle the control request from Web App (for output pins)
  webDigitalPinsPage.onPinWrite([](int pin, int state) {
    digitalWrite(pin, state);
    pinStates[pin] = state;
    // You can implement custom control logic here if needed
  });

  // Handle pin mode change requests (optional)
  webDigitalPinsPage.onPinModeChange([](int pin, int mode) {
    if (mode == WEB_PIN_OUTPUT) {
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
      pinStates[pin] = LOW;
    } else if (mode == WEB_PIN_INPUT) {
      pinMode(pin, INPUT);  // or INPUT_PULLUP as needed
      pinStates[pin] = digitalRead(pin);
    }
    // You can implement custom mode change logic here if needed
  });
}

void loop() {
  // Handle WebApp server communications
  webAppsServer.loop();

  // Monitor input pins for real-time updates
  static unsigned long lastInputCheck = 0;
  if (millis() - lastInputCheck > 100) {  // Check every 100ms
    lastInputCheck = millis();

    // Check input pins for changes and send real-time updates
    int inputPins[] = { 8, 9 };
    for (int i = 0; i < 2; i++) {
      int pin = inputPins[i];
      int currentState = digitalRead(pin);

      if (currentState != pinStates[pin]) {
        pinStates[pin] = currentState;
        // Send real-time update to web clients
        webDigitalPinsPage.updatePinState(pin, currentState);
      }
    }
  }

  // Add your main application code here

  delay(10);
}
