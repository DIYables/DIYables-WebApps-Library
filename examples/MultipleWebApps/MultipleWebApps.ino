/*
 * DIYables WebApp Library - Multiple WebApps Example
 * 
 * This example demonstrates multiple web apps of the DIYables WebApp library:
 * - Home page with links to multiple web apps
 * - Web Monitor: Real-time serial monitoring via WebSocket
 * - Web Slider: Dual slider control
 * - Web Joystick: Interactive joystick control
 * - Web Rotator: Interactive rotatable disc control
 * - Web Analog Gauge: Professional circular gauge for sensor monitoring
 * - Web Table: Two-column data table with real-time updates
 * - Web Plotter: See WebPlotter example for real-time data visualization
 * 
 * Features:
 * - Simplified callback system - no manual command parsing needed
 * - Automatic state synchronization and JSON handling
 * - All protocol details handled by the library
 * - Template for hardware control
 * 
 * Hardware: Arduino Uno R4 WiFi or DIYables STEM V4 IoT
 * 
 * Setup:
 * 1. Update WiFi credentials below
 * 2. Upload the sketch to your Arduino
 * 3. Open Serial Monitor to see the IP address
 * 4. Navigate to the IP address in your web browser
 */

#include <DIYablesWebApps.h>

// WiFi credentials - UPDATE THESE WITH YOUR NETWORK
const char WIFI_SSID[] = "YOUR_WIFI_SSID";
const char WIFI_PASSWORD[] = "YOUR_WIFI_PASSWORD";

// Create WebApp server and page instances
UnoR4ServerFactory factory;
DIYablesWebAppServer webAppsServer(factory, 80, 81);
DIYablesHomePage homePage;
DIYablesWebMonitorPage webMonitorPage;
DIYablesWebSliderPage webSliderPage;
DIYablesWebJoystickPage webJoystickPage(false, 5);               // autoReturn=false, sensitivity=5
DIYablesWebRotatorPage webRotatorPage(ROTATOR_MODE_CONTINUOUS);  // Continuous rotation mode (0-360°)
DIYablesWebAnalogGaugePage webAnalogGaugePage(0.0, 100.0, "%");  // Range: 0-100%, units: %
DIYablesWebTablePage webTablePage;

// Variables to track states
int currentSlider1 = 64;         // Slider 1 value (0-255)
int currentSlider2 = 128;        // Slider 2 value (0-255)
int currentJoystickX = 0;        // Current joystick X value (-100 to 100)
int currentJoystickY = 0;        // Current joystick Y value (-100 to 100)
int currentRotatorAngle = 0;     // Current rotator angle (0-360°)
float currentGaugeValue = 50.0;  // Current gauge value (0.0-100.0)

void setup() {
  Serial.begin(9600);
  delay(1000);

  // TODO: Initialize your hardware pins here

  Serial.println("DIYables WebApp - Multiple Apps Example");

  // Add all web applications to the server
  webAppsServer.addApp(&homePage);
  webAppsServer.addApp(&webMonitorPage);
  webAppsServer.addApp(&webSliderPage);
  webAppsServer.addApp(&webJoystickPage);
  webAppsServer.addApp(&webRotatorPage);
  webAppsServer.addApp(&webAnalogGaugePage);
  webAppsServer.addApp(&webTablePage);
  // Add more web apps here (e.g., WebPlotter)

  // Set 404 Not Found page (optional - for better user experience)
  webAppsServer.setNotFoundPage(DIYablesNotFoundPage());

  // Configure table structure (only attribute names, values will be updated dynamically)
  webTablePage.addRow("Arduino Status");
  webTablePage.addRow("WiFi Connected");
  webTablePage.addRow("Uptime");
  webTablePage.addRow("Slider 1");
  webTablePage.addRow("Slider 2");
  webTablePage.addRow("Joystick X");
  webTablePage.addRow("Joystick Y");
  webTablePage.addRow("Rotator Angle");
  webTablePage.addRow("Gauge Value");

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
  // Web Monitor callback - echo messages back
  webMonitorPage.onWebMonitorMessage([](const String& message) {
    Serial.println("Web Monitor: " + message);
    webMonitorPage.sendToWebMonitor("Arduino received: " + message);
  });

  // Web Slider callback - handle slider values
  webSliderPage.onSliderValueFromWeb([](int slider1, int slider2) {
    // Store the received values
    currentSlider1 = slider1;
    currentSlider2 = slider2;

    // Print slider values (0-255) without String concatenation
    Serial.print("Slider 1: ");
    Serial.print(slider1);
    Serial.print(", Slider 2: ");
    Serial.println(slider2);

    // Update table with new slider values using String() conversion
    webTablePage.sendValueUpdate("Slider 1", String(slider1));
    webTablePage.sendValueUpdate("Slider 2", String(slider2));

    // TODO: Add your control logic here based on slider values
    // Examples:
    // - Control PWM: analogWrite(LED_PIN, slider1);
    // - Control servos: servo.write(map(slider1, 0, 255, 0, 180));
    // - Control motor speed: analogWrite(MOTOR_PIN, slider2);

    // Update gauge based on slider1 value (map 0-255 to 0-100)
    currentGaugeValue = map(slider1, 0, 255, 0, 100);
    webAnalogGaugePage.sendToWebAnalogGauge(currentGaugeValue);
    char gaugeStr[16];
    snprintf(gaugeStr, sizeof(gaugeStr), "%.1f%%", currentGaugeValue);
    webTablePage.sendValueUpdate("Gauge Value", String(gaugeStr));
  });

  // Handle slider value requests
  webSliderPage.onSliderValueToWeb([]() {
    webSliderPage.sendToWebSlider(currentSlider1, currentSlider2);
  });

  // Web Joystick callback - handle joystick movement
  webJoystickPage.onJoystickValueFromWeb([](int x, int y) {
    // Store the received values
    currentJoystickX = x;
    currentJoystickY = y;

    // Print joystick position values (-100 to +100)
    Serial.print("Joystick - X: ");
    Serial.print(x);
    Serial.print(", Y: ");
    Serial.println(y);
    Serial.print(x);
    Serial.print(", Y: ");
    Serial.println(y);

    // Update table with new joystick values
    webTablePage.sendValueUpdate("Joystick X", String(x));
    webTablePage.sendValueUpdate("Joystick Y", String(y));

    // TODO: Add your control logic here based on joystick position
    // Examples:
    // - Control motors: if (x > 50) { /* move right */ }
    // - Control servos: servo.write(map(y, -100, 100, 0, 180));
    // - Control LEDs: analogWrite(LED_PIN, map(abs(x), 0, 100, 0, 255));
  });

  // Handle joystick values requests (when web page loads/reconnects)
  webJoystickPage.onJoystickValueToWeb([]() {
    webJoystickPage.sendToWebJoystick(currentJoystickX, currentJoystickY);
  });

  // Web Rotator callback - handle rotation angle changes
  webRotatorPage.onRotatorAngleFromWeb([](float angle) {
    // Store the received angle
    currentRotatorAngle = (int)angle;

    // Print rotator angle (0-360°)
    Serial.println("Rotator angle: " + String(angle) + "°");

    // Update table with new rotator angle
    webTablePage.sendValueUpdate("Rotator Angle", String(angle, 0) + "°");

    // TODO: Add your control logic here based on rotator angle
    // Examples:
    // - Control servo: servo.write(map(angle, 0, 360, 0, 180));
    // - Control stepper motor: stepper.moveTo(angle);
    // - Control directional LED strip: setLEDDirection(angle);
  });

  // Handle analog gauge value requests (when web page loads/reconnects)
  webAnalogGaugePage.onGaugeValueRequest([]() {
    webAnalogGaugePage.sendToWebAnalogGauge(currentGaugeValue);
  });

  // Handle table data requests (when web page loads/reconnects)
  webTablePage.onTableValueRequest([]() {
    // Send initial values to the table
    webTablePage.sendValueUpdate("Arduino Status", "Running");
    webTablePage.sendValueUpdate("WiFi Connected", "Yes");
    webTablePage.sendValueUpdate("Uptime", "0 seconds");
    webTablePage.sendValueUpdate("Slider 1", String(currentSlider1));
    webTablePage.sendValueUpdate("Slider 2", String(currentSlider2));
    webTablePage.sendValueUpdate("Joystick X", String(currentJoystickX));
    webTablePage.sendValueUpdate("Joystick Y", String(currentJoystickY));
    webTablePage.sendValueUpdate("Rotator Angle", String(currentRotatorAngle) + "°");
    webTablePage.sendValueUpdate("Gauge Value", String(currentGaugeValue, 1) + "%");
  });
}

void loop() {
  // Handle WebApp server communications
  webAppsServer.loop();

  // Update table with current uptime every 5 seconds
  static unsigned long lastUptimeUpdate = 0;
  if (millis() - lastUptimeUpdate > 5000) {
    lastUptimeUpdate = millis();

    unsigned long uptimeSeconds = millis() / 1000;
    String uptimeStr = String(uptimeSeconds) + " seconds";
    if (uptimeSeconds >= 60) {
      uptimeStr = String(uptimeSeconds / 60) + "m " + String(uptimeSeconds % 60) + "s";
    }

    webTablePage.sendValueUpdate("Uptime", uptimeStr);
  }

  // Simulate sensor data updates every 3 seconds
  static unsigned long lastSensorUpdate = 0;
  if (millis() - lastSensorUpdate > 3000) {
    lastSensorUpdate = millis();

    // Simulate a sensor reading that varies over time
    float sensorValue = 50.0 + 30.0 * sin(millis() / 10000.0);  // Oscillates between 20-80
    currentGaugeValue = sensorValue;

    // Update gauge and table
    webAnalogGaugePage.sendToWebAnalogGauge(currentGaugeValue);
    webTablePage.sendValueUpdate("Gauge Value", String(currentGaugeValue, 1) + "%");
  }

  // TODO: Add your main application code here

  delay(10);
}
