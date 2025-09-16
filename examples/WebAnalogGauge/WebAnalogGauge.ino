/*
 * DIYables WebApp Library - Web Analog Gauge Example
 * 
 * This  Serial.println("\nWebAnalogGauge is ready!");
  Serial.print("IP Address: ");
  Serial.println(webAppsServer.getLocalIP());
  Serial.println("Open your web browser and navigate to:");
  Serial.print("1. http://");
  Serial.print(webAppsServer.getLocalIP());
  Serial.println("/ (Home page)");
  Serial.print("2. http://");
  Serial.print(webAppsServer.getLocalIP());
  Serial.println("/webanalogGauge (Analog Gauge)");
  Serial.println("\nSimulating sensor data...");monstrates the Web Analog Gauge application:
 * - Real-time analog gauge visualization
 * - Simulated sensor data with smooth animation
 * - WebSocket communication for live updates
 * - Beautiful analog gauge with tick marks and smooth pointer movement
 * 
 * Features:
 * - Automatic gauge value simulation
 * - Smooth animation between values
 * - Range: 0° to 280° (customizable)
 * - Real-time WebSocket updates
 * - Professional analog gauge appearance
 * 
 * Hardware: Arduino Uno R4 WiFi or DIYables STEM V4 IoT
 * 
 * Setup:
 * 1. Update WiFi credentials below
 * 2. Upload the sketch to your Arduino
 * 3. Open Serial Monitor to see the IP address
 * 4. Navigate to http://[arduino-ip]/web-gauge in your web browser
 */

#include <DIYablesWebApps.h>

// WiFi credentials - UPDATE THESE WITH YOUR NETWORK
const char WIFI_SSID[] = "YOUR_WIFI_SSID";
const char WIFI_PASSWORD[] = "YOUR_WIFI_PASSWORD";

// Create WebApp server and page instances
UnoR4ServerFactory serverFactory;
DIYablesWebAppServer webAppsServer(serverFactory, 80, 81);
DIYablesHomePage homePage;

// Gauge configuration constants
const float GAUGE_MIN_VALUE = 0.0;
const float GAUGE_MAX_VALUE = 100.0;
const String GAUGE_UNIT = "%";

DIYablesWebAnalogGaugePage webAnalogGaugePage(GAUGE_MIN_VALUE, GAUGE_MAX_VALUE, GAUGE_UNIT);  // Range: 0-100%
// Other examples:
// DIYablesWebAnalogGaugePage webAnalogGaugePage(-50.0, 150.0, "°C");  // Temperature: -50°C to 150°C
// DIYablesWebAnalogGaugePage webAnalogGaugePage(0.0, 1023.0, "");     // Analog sensor: 0-1023 (no unit)
// DIYablesWebAnalogGaugePage webAnalogGaugePage(0.0, 5.0, "V");       // Voltage: 0-5V

// Simulation variables
unsigned long lastUpdateTime = 0;
const unsigned long UPDATE_INTERVAL = 500;  // Update every 500ms (0.5 second)
const float STEP_SIZE = 1.0;                // Step size for simulation
float currentGaugeValue = GAUGE_MIN_VALUE;  // Start at minimum value
float step = STEP_SIZE;                     // Positive step means increasing, negative means decreasing

void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.println("DIYables WebApp - Web Analog Gauge Example");

  // Add web applications to the server
  webAppsServer.addApp(&homePage);
  webAppsServer.addApp(&webAnalogGaugePage);

  // Optional: Add 404 page for better user experience
  webAppsServer.setNotFoundPage(DIYablesNotFoundPage());

  // Start the WebApp server
  if (!webAppsServer.begin(WIFI_SSID, WIFI_PASSWORD)) {
    while (1) {
      Serial.println("Failed to start WebApp server!");
      delay(1000);
    }
  }

  setupCallbacks();
}

void setupCallbacks() {
  // Handle gauge value requests (when web page loads/reconnects)
  webAnalogGaugePage.onGaugeValueRequest([]() {
    webAnalogGaugePage.sendToWebAnalogGauge(currentGaugeValue);
    Serial.println("Web client requested gauge value - Sent: " + String(currentGaugeValue, 1) + GAUGE_UNIT);
  });
}

void loop() {
  // Handle WebApp server communications
  webAppsServer.loop();

  // Update gauge with simulated sensor data
  if (millis() - lastUpdateTime >= UPDATE_INTERVAL) {
    lastUpdateTime = millis();

    Serial.println("Updating gauge value...");  // Debug message

    // Simple linear simulation: step changes direction at boundaries
    currentGaugeValue += step;

    // Change direction when reaching boundaries
    if (currentGaugeValue >= GAUGE_MAX_VALUE || currentGaugeValue <= GAUGE_MIN_VALUE) {
      step *= -1;  // Reverse direction
    }

    // Ensure value stays within bounds (safety check)
    if (currentGaugeValue < GAUGE_MIN_VALUE) currentGaugeValue = GAUGE_MIN_VALUE;
    if (currentGaugeValue > GAUGE_MAX_VALUE) currentGaugeValue = GAUGE_MAX_VALUE;

    // Send the new value to all connected web clients
    webAnalogGaugePage.sendToWebAnalogGauge(currentGaugeValue);

    // Print to serial for debugging
    Serial.println("Gauge: " + String(currentGaugeValue, 1) + GAUGE_UNIT + " (" + (step > 0 ? "↑" : "↓") + ")");
  }

  delay(10);
}
