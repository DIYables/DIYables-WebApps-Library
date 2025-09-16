/*
 * DIYables WebApps Library - WebTable Example
 * 
 * This example demonstrates how to create a web-based table interface
 * that displays real-time data in a two-column format (attribute-value pairs).
 * 
 * Features:
 * - Two-column table with attributes and real-time values
 * - WebSocket-based real-time updates
 * - Configurable table rows in setup()
 * - Dynamic value updates during runtime
 * - Modern responsive web interface
 * 
 * Hardware: Arduino Uno R4 WiFi or DIYables STEM V4 IoT
 * 
 * Instructions:
 * 1. Update WiFi credentials below
 * 2. Upload the code to your Arduino
 * 3. Open Serial Monitor to get the IP address
 * 4. Open web browser and go to:
 *    - Home page: http://[ARDUINO_IP]/
 *    - WebTable: http://[ARDUINO_IP]/web-table
 * 5. Watch real-time data updates in the table
 * 
 * Created by DIYables
 * Visit: https://diyables.com for more tutorials and projects
 */

#include <DIYablesWebApps.h>

// WiFi credentials - Update these with your network details
const char WIFI_SSID[] = "YOUR_WIFI_SSID";
const char WIFI_PASSWORD[] = "YOUR_WIFI_PASSWORD";

// Initialize web server and pages
UnoR4ServerFactory serverFactory;
DIYablesWebAppServer server(serverFactory, 80, 81);
DIYablesHomePage homePage;
DIYablesWebTablePage tablePage;

// Variables to simulate sensor data
float temperature = 20.5;
float humidity = 65.0;
int lightLevel = 512;
unsigned long uptime = 0;
bool ledState = false;
int counter = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("DIYables WebApp - Web Table Example");

  // Initialize built-in LED
  pinMode(LED_BUILTIN, OUTPUT);

  // Add web apps
  server.addApp(&homePage);
  server.addApp(&tablePage);

  // Optional: Add 404 page for better user experience
  server.setNotFoundPage(DIYablesNotFoundPage());

  // Start the WebApp server
  server.begin(WIFI_SSID, WIFI_PASSWORD);

  // Set up callback for data requests
  tablePage.onTableValueRequest(onDataRequested);

  // Configure table structure in setup - attributes are set once
  setupTableStructure();

  Serial.println("WebTable Server started!");
}

void loop() {
  server.loop();

  // Update sensor values every 2 seconds
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 2000) {
    updateSensorValues();
    sendRealTimeUpdates();
    lastUpdate = millis();
  }

  // Toggle LED every 5 seconds
  static unsigned long lastLedToggle = 0;
  if (millis() - lastLedToggle > 5000) {
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);

    // Send LED status update to web interface
    tablePage.sendValueUpdate("LED Status", ledState ? "ON" : "OFF");

    lastLedToggle = millis();
  }

  delay(10);
}

// Setup table structure - called once in setup()
void setupTableStructure() {
  Serial.println("Setting up table structure...");

  // Add table rows with attributes only (no values stored)
  tablePage.addRow("Device Name");
  tablePage.addRow("Temperature");
  tablePage.addRow("Humidity");
  tablePage.addRow("Light Level");
  tablePage.addRow("Uptime");
  tablePage.addRow("LED Status");
  tablePage.addRow("Counter");
  tablePage.addRow("WiFi SSID");
  tablePage.addRow("IP Address");
  tablePage.addRow("Free Memory");

  Serial.println("Table structure configured with " + String(tablePage.getRowCount()) + " rows");
}

// Simulate sensor readings and send values to web interface
void updateSensorValues() {
  // Simulate temperature sensor (20-30°C range)
  temperature = 20.0 + (sin(millis() / 10000.0) * 5.0) + random(-10, 10) / 10.0;

  // Simulate humidity sensor (40-80% range)
  humidity = 60.0 + (cos(millis() / 8000.0) * 15.0) + random(-20, 20) / 10.0;

  // Simulate light sensor (0-1023 range)
  lightLevel = 512 + (sin(millis() / 5000.0) * 400) + random(-50, 50);
  if (lightLevel < 0) lightLevel = 0;
  if (lightLevel > 1023) lightLevel = 1023;

  // Update uptime
  uptime = millis() / 1000;

  // Increment counter
  counter++;
}

// Send real-time updates to web interface
void sendRealTimeUpdates() {
  // Send individual value updates to web clients
  tablePage.sendValueUpdate("Temperature", String(temperature, 1) + "°C");
  tablePage.sendValueUpdate("Humidity", String(humidity, 1) + "%");
  tablePage.sendValueUpdate("Light Level", String(lightLevel));
  tablePage.sendValueUpdate("Uptime", formatUptime(uptime));
  tablePage.sendValueUpdate("Counter", String(counter));
  tablePage.sendValueUpdate("Free Memory", String(getFreeMemory()) + " bytes");
}

// Callback function called when web client requests table data
void onDataRequested() {
  Serial.println("Web client requested table data");

  // Send all current values to web interface
  tablePage.sendValueUpdate("Device Name", "Arduino Uno R4");
  tablePage.sendValueUpdate("Temperature", String(temperature, 1) + "°C");
  tablePage.sendValueUpdate("Humidity", String(humidity, 1) + "%");
  tablePage.sendValueUpdate("Light Level", String(lightLevel));
  tablePage.sendValueUpdate("Uptime", formatUptime(uptime));
  tablePage.sendValueUpdate("LED Status", ledState ? "ON" : "OFF");
  tablePage.sendValueUpdate("Counter", String(counter));
  tablePage.sendValueUpdate("WiFi SSID", WIFI_SSID);
  tablePage.sendValueUpdate("IP Address", WiFi.localIP().toString());
  tablePage.sendValueUpdate("Free Memory", String(getFreeMemory()) + " bytes");
}

// Format uptime in human-readable format
String formatUptime(unsigned long seconds) {
  unsigned long days = seconds / 86400;
  unsigned long hours = (seconds % 86400) / 3600;
  unsigned long minutes = (seconds % 3600) / 60;
  unsigned long secs = seconds % 60;

  String result = "";
  if (days > 0) result += String(days) + "d ";
  if (hours > 0) result += String(hours) + "h ";
  if (minutes > 0) result += String(minutes) + "m ";
  result += String(secs) + "s";

  return result;
}

// Get approximate free memory
int getFreeMemory() {
  // Simple approximation for demonstration
  // In a real application, you might use a more accurate method
  return 2048 - (counter % 1024);
}
