/*
 * DIYables WebApp Library - Web Slider Example
 * 
 * This example demonstrates the Web Slider feature:
 * - Two independent sliders (0-255)
 * - Real-time value monitoring
 * - Template for hardware control
 * 
 * Hardware: Arduino Uno R4 WiFi or DIYables STEM V4 IoT
 * 
 * Setup:
 * 1. Update WiFi credentials below
 * 2. Upload the sketch to your Arduino
 * 3. Open Serial Monitor to see the IP address
 * 4. Navigate to http://[IP_ADDRESS]/webslider
 */

#include <DIYablesWebApps.h>

// WiFi credentials - UPDATE THESE WITH YOUR NETWORK
const char WIFI_SSID[] = "YOUR_WIFI_SSID";
const char WIFI_PASSWORD[] = "YOUR_WIFI_PASSWORD";

// Create WebApp server and page instances
UnoR4ServerFactory serverFactory;
DIYablesWebAppServer webAppsServer(serverFactory, 80, 81);
DIYablesHomePage homePage;
DIYablesWebSliderPage webSliderPage;

// Current slider values
int slider1Value = 64;   // Default 25%
int slider2Value = 128;  // Default 50%

void setup() {
  Serial.begin(9600);
  delay(1000);

  // TODO: Initialize your hardware pins here

  Serial.println("DIYables WebApp - Web Slider Example");

  // Add home and web slider pages
  webAppsServer.addApp(&homePage);
  webAppsServer.addApp(&webSliderPage);

  // Optional: Add 404 page for better user experience
  webAppsServer.setNotFoundPage(DIYablesNotFoundPage());

  // Start the WebApp server
  if (!webAppsServer.begin(WIFI_SSID, WIFI_PASSWORD)) {
    while (1) {
      Serial.println("Failed to start WebApp server!");
      delay(1000);
    }
  }

  // Set up slider callback for value changes
  webSliderPage.onSliderValueFromWeb([](int slider1, int slider2) {
    // Store the received values
    slider1Value = slider1;
    slider2Value = slider2;

    // Print slider values (0-255)
    Serial.println("Slider 1: " + String(slider1) + ", Slider 2: " + String(slider2));

    // TODO: Add your control logic here based on slider values
    // Examples:
    // - Control PWM: analogWrite(LED_PIN, slider1);
    // - Control servos: servo.write(map(slider1, 0, 255, 0, 180));
    // - Control motor speed: analogWrite(MOTOR_PIN, slider2);
    // - Control brightness: strip.setBrightness(slider1);
    // - Send values via Serial, I2C, SPI, etc.
  });

  // Set up callback for config requests (when client requests current values)
  webSliderPage.onSliderValueToWeb([]() {
    webSliderPage.sendToWebSlider(slider1Value, slider2Value);
    Serial.println("Web client requested values - Sent: Slider1=" + String(slider1Value) + ", Slider2=" + String(slider2Value));
  });
}

void loop() {
  // Handle WebApp server communications
  webAppsServer.loop();

  // TODO: Add your main application code here

  delay(10);
}
