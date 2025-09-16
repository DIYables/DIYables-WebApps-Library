/*
 * DIYables WebApp Library - Web Joystick Example
 * 
 * This example demonstrates the Web Joystick feature:
 * - Interactive joystick control via web interface
 * - Real-time X/Y coordinate values (-100 to +100)
 * - Control pins based on joystick position
 * 
 * Hardware: Arduino Uno R4 WiFi or DIYables STEM V4 IoT
 * 
 * Setup:
 * 1. Update WiFi credentials below
 * 2. Upload the sketch to your Arduino
 * 3. Open Serial Monitor to see the IP address
 * 4. Navigate to http://[IP_ADDRESS]/webjoystick
 */

#include <DIYablesWebApps.h>

// WiFi credentials - UPDATE THESE WITH YOUR NETWORK
const char WIFI_SSID[] = "YOUR_WIFI_SSID";
const char WIFI_PASSWORD[] = "YOUR_WIFI_PASSWORD";

// Create WebApp server and page instances
// MEMORY SAFETY FIX: Use static factory to avoid stack object lifetime issues
static UnoR4ServerFactory serverFactory;  // Static ensures lifetime matches program
DIYablesWebAppServer webAppsServer(serverFactory, 80, 81);
DIYablesHomePage homePage;
// Configure joystick with autoReturn=false and sensitivity=5 (minimum 5% change to trigger updates)
DIYablesWebJoystickPage webJoystickPage(false, 5);

// Variables to store current joystick values
int currentJoystickX = 0;
int currentJoystickY = 0;

void setup() {
  Serial.begin(9600);
  delay(1000);

  // TODO: initialize your hardware pins here

  Serial.println("DIYables WebApp - Web Joystick Example");

  // Add home and web joystick pages
  webAppsServer.addApp(&homePage);
  webAppsServer.addApp(&webJoystickPage);

  // Optional: Add 404 page for better user experience
  webAppsServer.setNotFoundPage(DIYablesNotFoundPage());

  // Start the WebApp server
  if (!webAppsServer.begin(WIFI_SSID, WIFI_PASSWORD)) {
    while (1) {
      Serial.println("Failed to start WebApp server!");
      delay(1000);
    }
  }

  // Set up joystick callback for position changes
  webJoystickPage.onJoystickValueFromWeb([](int x, int y) {
    // Store the received values
    currentJoystickX = x;
    currentJoystickY = y;

    // Print joystick position values (-100 to +100)
    Serial.println("Joystick - X: " + String(x) + ", Y: " + String(y));

    // TODO: Add your control logic here based on joystick position
    // Examples:
    // - Control motors: if (x > 50) { /* move right */ }
    // - Control servos: servo.write(map(y, -100, 100, 0, 180));
    // - Control LEDs: analogWrite(LED_PIN, map(abs(x), 0, 100, 0, 255));
    // - Send commands to other devices via Serial, I2C, SPI, etc.
  });

  // Optional: Handle requests for current joystick values (when web page loads)
  webJoystickPage.onJoystickValueToWeb([]() {
    // Send the stored joystick values back to the web client
    webJoystickPage.sendToWebJoystick(currentJoystickX, currentJoystickY);
    Serial.println("Web client requested values - Sent to Web: X=" + String(currentJoystickX) + ", Y=" + String(currentJoystickY));
  });

  // You can change configuration at runtime:
  // webJoystickPage.setAutoReturn(false);  // Disable auto-return
  // webJoystickPage.setSensitivity(10.0);  // Only send updates when joystick moves >10% (less sensitive)
}

void loop() {
  // Handle WebApp server communications
  webAppsServer.loop();

  // TODO: Add your main application code here

  delay(10);
}
