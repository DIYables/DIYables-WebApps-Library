/*
 * This example demonstrates how to create a web-base    Serial.println("Starting Web Temperature Server...");
    
    // Add web apps to server
    server.addApp(&homePage);
    server.addApp(&temperaturePage);
    
    // Set 404 Not Found page (optional - for better user experience)
    server.setNotFoundPage(DIYablesNotFoundPage());re display
 * using the DIYables WebApps library with Arduino Uno R4 WiFi.
 * 
 * The library automatically detects the Arduino Uno R4 WiFi platform and
 * includes the appropriate abstraction layer for seamless operation.
 * 
 * The web page displays a thermometer visualization that shows temperature
 * readings in real-time through WebSocket communication.
 * 
 * Features:
 * - Real-time temperature display with thermometer visualization
 * - Configurable temperature range and units
 * - Auto-connecting WebSocket for seamless communication
 * - Mobile-responsive design with professional UI
 * - Automatic platform detection and abstraction
 * - Compatible with both WiFi and Ethernet connections

 * Hardware: Arduino Uno R4 WiFi or DIYables STEM V4 IoT
 */

#include <DIYablesWebApps.h>

// WiFi credentials - UPDATE THESE WITH YOUR NETWORK
const char WIFI_SSID[] = "YOUR_WIFI_SSID";
const char WIFI_PASSWORD[] = "YOUR_WIFI_PASSWORD";

// Create web app instances
UnoR4ServerFactory serverFactory;
DIYablesWebAppServer server(serverFactory, 80, 81);  // HTTP port 80, WebSocket port 81
DIYablesHomePage homePage;
DIYablesWebTemperaturePage temperaturePage(-10.0, 50.0, "°C");  // Min: -10°C, Max: 50°C

// Temperature simulation variables
float currentTemp = 25.0;  // Starting temperature
unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting Web Temperature Server...");

  // Add web apps to server
  server.addApp(&homePage);
  server.addApp(&temperaturePage);

  // Set 404 Not Found page (optional - for better user experience)
  server.setNotFoundPage(DIYablesNotFoundPage());

  // Set up temperature callback for value requests
  temperaturePage.onTemperatureValueRequested(onTemperatureValueRequested);

  // Start the server
  server.begin(WIFI_SSID, WIFI_PASSWORD);
}

void loop() {
  // Handle web server and WebSocket communications
  server.loop();

  // Simulate temperature readings
  simulateTemperature();

  // Send temperature update every 2 seconds
  if (millis() - lastUpdate >= 2000) {
    temperaturePage.sendTemperature(currentTemp);

    // Print temperature to Serial Monitor
    Serial.println("Temperature: " + String(currentTemp, 1) + "°C");

    lastUpdate = millis();
  }

  delay(10);  // Small delay for stability
}

void simulateTemperature() {
  // Simple temperature simulation - slowly increases and decreases
  static bool increasing = true;

  if (increasing) {
    currentTemp += 0.1;  // Increase temperature slowly
    if (currentTemp >= 35.0) {
      increasing = false;  // Start decreasing when it reaches 35°C
    }
  } else {
    currentTemp -= 0.1;  // Decrease temperature slowly
    if (currentTemp <= 15.0) {
      increasing = true;  // Start increasing when it reaches 15°C
    }
  }
}

/**
 * Callback function called when web interface requests temperature value
 * Send current temperature value to web interface
 */
void onTemperatureValueRequested() {
  Serial.println("Temperature value requested from web interface");

  // Send current temperature value (config is automatically sent by the library)
  temperaturePage.sendTemperature(currentTemp);
}

/*
 * Alternative setup for real temperature sensor (DS18B20 example):
 * 
 * #include <OneWire.h>
 * #include <DallasTemperature.h>
 * 
 * #define ONE_WIRE_BUS 2
 * OneWire oneWire(ONE_WIRE_BUS);
 * DallasTemperature sensors(&oneWire);
 * 
 * void setup() {
 *     // ... existing setup code ...
 *     sensors.begin();
 * }
 * 
 * float readTemperature() {
 *     sensors.requestTemperatures();
 *     return sensors.getTempCByIndex(0);
 * }
 * 
 * // In loop(), replace simulateTemperature() with:
 * // currentTemp = readTemperature();
 */
