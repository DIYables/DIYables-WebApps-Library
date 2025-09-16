/*
 * DIYables WebApp Library - Web Plotter Example
 * 
 * This example demonstrates the Web Plotter feature:
 * - Real-time data visualization
 * - Multiple data series support
 * - Auto-scaling Y-axis
 * - Responsive web interface
 * - WebSocket communication for instant updates
 * 
 * Hardware: Arduino Uno R4 WiFi or DIYables STEM V4 IoT
 * 
 * Setup:
 * 1. Update WiFi credentials below
 * 2. Upload the sketch to your Arduino
 * 3. Open Serial Monitor to see the IP address
 * 4. Navigate to http://[IP_ADDRESS]/webplotter
 */

#include <DIYablesWebApps.h>

// WiFi credentials - UPDATE THESE WITH YOUR NETWORK
const char WIFI_SSID[] = "YOUR_WIFI_SSID";
const char WIFI_PASSWORD[] = "YOUR_WIFI_PASSWORD";

// Create WebApp server and page instances
UnoR4ServerFactory serverFactory;
DIYablesWebAppServer webAppsServer(serverFactory, 80, 81);
DIYablesHomePage homePage;
DIYablesWebPlotterPage webPlotterPage;

// Simulation variables
unsigned long lastDataTime = 0;
const unsigned long DATA_INTERVAL = 1000;  // Send data every 1000ms
float timeCounter = 0;

void setup() {
  Serial.begin(9600);
  delay(1000);

  // TODO: Initialize your hardware pins and sensors here

  Serial.println("DIYables WebApp - Web Plotter Example");

  // Add home and web plotter pages
  webAppsServer.addApp(&homePage);
  webAppsServer.addApp(&webPlotterPage);

  // Optional: Add 404 page for better user experience
  webAppsServer.setNotFoundPage(DIYablesNotFoundPage());

  // Configure the plotter
  webPlotterPage.setPlotTitle("Real-time Data Plotter");
  webPlotterPage.setAxisLabels("Time (s)", "Values");
  webPlotterPage.enableAutoScale(true);
  webPlotterPage.setMaxSamples(50);

  // Start the WebApp server
  if (!webAppsServer.begin(WIFI_SSID, WIFI_PASSWORD)) {
    while (1) {
      Serial.println("Failed to start WebApp server!");
      delay(1000);
    }
  }

  // Set up callbacks
  webPlotterPage.onPlotterDataRequest([]() {
    Serial.println("Web client requested data");
    sendSensorData();
  });

  Serial.println("\nWebPlotter is ready!");
  Serial.println("Usage Instructions:");
  Serial.println("1. Connect to the WiFi network");
  Serial.println("2. Open your web browser");
  Serial.println("3. Navigate to the Arduino's IP address");
  Serial.println("4. Click on 'Web Plotter' to view real-time data");
  Serial.println("\nGenerating simulated sensor data...");
}

void loop() {
  // Handle web server and WebSocket connections
  webAppsServer.loop();

  // Send sensor data at regular intervals
  if (millis() - lastDataTime >= DATA_INTERVAL) {
    lastDataTime = millis();
    sendSensorData();
    timeCounter += DATA_INTERVAL / 1000.0;  // Convert to seconds
  }
}

void sendSensorData() {
  // Generate simulated sensor data
  // In a real application, replace these with actual sensor readings

  // Simulated temperature sensor (sine wave with noise)
  float temperature = 25.0 + 5.0 * sin(timeCounter * 0.5) + random(-100, 100) / 100.0;

  // Simulated humidity sensor (cosine wave)
  float humidity = 50.0 + 20.0 * cos(timeCounter * 0.3);

  // Simulated light sensor (triangle wave)
  float light = 512.0 + 300.0 * (2.0 * abs(fmod(timeCounter * 0.2, 2.0) - 1.0) - 1.0);

  // Simulated analog pin reading
  float analogValue = analogRead(A0);

  // Send data using different methods:

  // Method 1: Send individual values (uncomment to use)
  // webPlotterPage.sendPlotData(temperature);

  // Method 2: Send multiple values at once
  webPlotterPage.sendPlotData(temperature, humidity, light / 10.0, analogValue / 100.0);

  // Method 3: Send array of values (alternative approach)
  // float values[] = {temperature, humidity, light / 10.0, analogValue / 100.0};
  // webPlotterPage.sendPlotData(values, 4);

  // Method 4: Send raw data string (for custom formatting)
  // String dataLine = String(temperature, 2) + " " + String(humidity, 1) + " " + String(light / 10.0, 1);
  // webPlotterPage.sendPlotData(dataLine);

  // Print to Serial Monitor in Serial Plotter compatible format
  // Format: Temperature Humidity Light Analog (tab-separated for Serial Plotter)
  Serial.print(temperature, 1);
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t");
  Serial.print(light / 10.0, 1);
  Serial.print("\t");
  Serial.println(analogValue / 100.0, 2);
}
