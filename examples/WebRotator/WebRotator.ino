/*
 * DIYables WebApp Library - Web Rotator Example
 * 
 * This example demonstrates the Web Rotator application:
 * - Interactive rotatable disc control
 * - Two modes: Continuous rotation and Limited angle range
 * - Real-time angle feedback with WebSocket communication
 * - Touch and mouse support for desktop and mobile
 * 
 * Features:
 * - Configurable rotation modes (continuous or limited)
 * - Beautiful conic gradient disc with visual indicator
 * - Real-time angle display and feedback
 * - WebSocket communication for live updates
 * - Professional responsive UI design
 * 
 * Hardware: Arduino Uno R4 WiFi or DIYables STEM V4 IoT
 * 
 * Setup:
 * 1. Update WiFi credentials below
 * 2. Upload the sketch to your Arduino
 * 3. Open Serial Monitor to see the IP address
 * 4. Navigate to http://[arduino-ip]/web-rotator in your web browser
 */

#include <DIYablesWebApps.h>

// WiFi credentials - UPDATE THESE WITH YOUR NETWORK
const char WIFI_SSID[] = "YOUR_WIFI_SSID";
const char WIFI_PASSWORD[] = "YOUR_WIFI_PASSWORD";

// Create WebApp server and page instances
UnoR4ServerFactory serverFactory;
DIYablesWebAppServer webAppsServer(serverFactory, 80, 81);
DIYablesHomePage homePage;

// Rotator configuration constants
const int ROTATOR_MODE = ROTATOR_MODE_CONTINUOUS;  // Change to ROTATOR_MODE_LIMITED for limited rotation
const float MIN_ANGLE = 0.0;                       // Minimum angle for limited mode
const float MAX_ANGLE = 180.0;                     // Maximum angle for limited mode

// Create WebRotator page with configuration
//DIYablesWebRotatorPage webRotatorPage(ROTATOR_MODE_CONTINUOUS);
DIYablesWebRotatorPage webRotatorPage(ROTATOR_MODE_LIMITED, MIN_ANGLE, MAX_ANGLE);

// Variables for angle tracking
float currentAngle = 0.0;

void setup() {
  Serial.begin(9600);
  delay(1000);

  // TODO: Initialize your hardware pins here

  Serial.println("DIYables WebApp - Web Rotator Example");

  // Add pages to server
  webAppsServer.addApp(&homePage);
  webAppsServer.addApp(&webRotatorPage);

  // Set 404 Not Found page (optional - for better user experience)
  webAppsServer.setNotFoundPage(DIYablesNotFoundPage());

  // Set callback functions for WebRotator
  webRotatorPage.onRotatorAngleFromWeb(onRotatorAngleReceived);

  // Start server
  webAppsServer.begin(WIFI_SSID, WIFI_PASSWORD);

  if (ROTATOR_MODE == ROTATOR_MODE_LIMITED) {
    Serial.println("\nRotator Mode: Limited");
    Serial.print("Angle Range: ");
    Serial.print(MIN_ANGLE);
    Serial.print("° to ");
    Serial.print(MAX_ANGLE);
    Serial.println("°");
  } else {
    Serial.println("\nRotator Mode: Continuous Rotation");
  }

  Serial.println("\nTurn the disc in your web browser to control the rotator!");
}

void loop() {
  // Handle web server and WebSocket connections
  webAppsServer.loop();

  // Simulate rotator movement or control actual hardware here
  // For demonstration, we'll just echo back the received angle

  delay(10);
}

/**
 * Callback function called when angle is received from web interface
 * This is where you would control your actual rotator hardware
 */
void onRotatorAngleReceived(float angle) {
  currentAngle = angle;

  Serial.print("Rotator angle received: ");
  Serial.print(angle, 1);
  Serial.println("°");

  // TODO: Add your rotator control code here
  // Examples:
  // - Control servo motor: servo.write(map(angle, 0, 360, 0, 180));
  // - Control stepper motor: stepper.moveTo(angle * stepsPerDegree);
  // - Control DC motor with encoder feedback
  // - Send commands to external rotator controller

  // Note: No echo back to avoid interfering with smooth web interface rotation
}

/**
 * Example function to change rotator mode at runtime
 * Call this function to switch between continuous and limited modes
 */
void setRotatorMode(int mode, float minAng = 0, float maxAng = 360) {
  webRotatorPage.setRotatorMode(mode, minAng, maxAng);

  Serial.print("Rotator mode changed to: ");
  if (mode == ROTATOR_MODE_LIMITED) {
    Serial.print("Limited (");
    Serial.print(minAng);
    Serial.print("° to ");
    Serial.print(maxAng);
    Serial.println("°)");
  } else {
    Serial.println("Continuous");
  }
}

/**
 * Example function to send angle updates to web interface
 * Call this function when your rotator position changes
 */
void sendAngleUpdate(float angle) {
  currentAngle = angle;
  webRotatorPage.sendToWebRotator(angle);

  Serial.print("Angle update sent to web: ");
  Serial.print(angle, 1);
  Serial.println("°");
}
