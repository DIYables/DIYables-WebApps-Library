/*
 * DIYables WebApp Library - Custom WebApp Example
 * 
 * This example shows you how to create your own simple web application.
 * The web page has:
 * - Buttons to control Arduino LED
 * - A slider to set values
 * - Display of sensor data
 * 
 * Perfect for beginners to learn web-Arduino communication!
 * 
 * Hardware: Arduino Uno R4 WiFi or DIYables STEM V4 IoT
 * 
 * Setup:
 * 1. Change WiFi name and password below
 * 2. Upload to your Arduino
 * 3. Open Serial Monitor to see IP address
 * 4. Go to http://[IP_ADDRESS]/custom in your browser
 */

#include <DIYablesWebApps.h>
#include "CustomWebApp.h"

// CHANGE THESE TO YOUR WIFI DETAILS
const char WIFI_SSID[] = "YOUR_WIFI_SSID";
const char WIFI_PASSWORD[] = "YOUR_WIFI_PASSWORD";

// Create server and pages
UnoR4ServerFactory serverFactory;
DIYablesWebAppServer webAppsServer(serverFactory, 80, 81);
DIYablesHomePage homePage;
CustomWebAppPage customPage;

// Variables for your app
int myValue = 50;
unsigned long lastSensorRead = 0;

void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.println("Starting Custom WebApp...");

  // Add pages to server
  webAppsServer.addApp(&homePage);
  webAppsServer.addApp(&customPage);

  // TODO: Add pre-built apps or other custom apps here
  //   - Pre-built apps: DIYablesWebMonitorPage, DIYablesWebSliderPage, etc.
  //   - Custom apps: webAppsServer.addApp(&anotherCustomApp);

  // Start WiFi and web server
  if (!webAppsServer.begin(WIFI_SSID, WIFI_PASSWORD)) {
    while (1) {
      Serial.println("Failed to connect to WiFi!");
      delay(1000);
    }
  }

  // Set up what happens when web page sends commands
  customPage.onCustomMessageReceived([](const String& payload) {
    Serial.println("Received: " + payload);

    // TODO: Implement your message handling here
    // Examples:
    // - Control LEDs, motors, sensors
    // - Process commands and data
    // - Trigger actions based on payload content

    // For now, just echo the message back
    customPage.sendToWeb("Received: " + payload);
  });

  Serial.println("Custom WebApp ready!");
  customPage.sendToWeb("Arduino is ready!");
}

void loop() {
  // Handle web server
  webAppsServer.loop();

  // Send sensor data every 3 seconds
  if (millis() - lastSensorRead > 3000) {
    // TODO: Read your sensors here
    // Example: int sensorReading = analogRead(A0);

    // Send example data as simple string
    String data = "Uptime: " + String(millis() / 1000) + " seconds";
    customPage.sendToWeb(data);
    Serial.println("sent: " + data);

    lastSensorRead = millis();
  }

  // TODO: Add your custom code here!

  delay(10);
}
