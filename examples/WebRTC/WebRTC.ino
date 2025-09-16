/*
 * DIYables WebApp Library - Web RTC Example
 * 
 * This example demonstrates the Web RTC feature:
 * - Real-time clock display for both Arduino and client device
 * - One-click time synchronization from web browser to Arduino
 * - Hardware RTC integration for persistent timekeeping
 * - Visual time difference monitoring
 * 
 * Hardware: Arduino Uno R4 WiFi or DIYables STEM V4 IoT
 * 
 * Setup:
 * 1. Update WiFi credentials below
 * 2. Upload the sketch to your Arduino
 * 3. Open Serial Monitor to see the IP address
 * 4. Navigate to http://[IP_ADDRESS]/web-rtc
 */

#include <DIYablesWebApps.h>
#include "RTC.h"

// WiFi credentials - UPDATE THESE WITH YOUR NETWORK
const char WIFI_SSID[] = "YOUR_WIFI_SSID";
const char WIFI_PASSWORD[] = "YOUR_WIFI_PASSWORD";

// Create WebApp server and page instances
UnoR4ServerFactory serverFactory;
DIYablesWebAppServer webAppsServer(serverFactory, 80, 81);
DIYablesHomePage homePage;
DIYablesWebRTCPage webRTCPage;

void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.println("DIYables WebApp - Web RTC Example");

  // Initialize RTC
  RTC.begin();

  // Check if RTC is running and set initial time if needed
  RTCTime savedTime;
  RTC.getTime(savedTime);

  if (!RTC.isRunning() || savedTime.getYear() == 2000) {
    Serial.println("RTC is NOT running, setting initial time...");
    // Set a default time - you can modify this to match current time
    RTCTime startTime(28, Month::AUGUST, 2025, 12, 0, 0, DayOfWeek::THURSDAY, SaveLight::SAVING_TIME_ACTIVE);
    RTC.setTime(startTime);
    Serial.println("RTC initialized with default time");
  } else {
    Serial.println("RTC is already running");
  }

  // Print initial RTC time
  RTCTime initialTime;
  RTC.getTime(initialTime);
  Serial.print("Initial RTC Time: ");
  Serial.print(initialTime.getYear());
  Serial.print("/");
  Serial.print(Month2int(initialTime.getMonth()));
  Serial.print("/");
  Serial.print(initialTime.getDayOfMonth());
  Serial.print(" - ");
  if (initialTime.getHour() < 10) Serial.print("0");
  Serial.print(initialTime.getHour());
  Serial.print(":");
  if (initialTime.getMinutes() < 10) Serial.print("0");
  Serial.print(initialTime.getMinutes());
  Serial.print(":");
  if (initialTime.getSeconds() < 10) Serial.print("0");
  Serial.print(initialTime.getSeconds());
  Serial.println();

  // Add pages to server
  webAppsServer.addApp(&homePage);
  webAppsServer.addApp(&webRTCPage);

  // Optional: Add 404 page for better user experience
  webAppsServer.setNotFoundPage(DIYablesNotFoundPage());

  // Set callback for time sync from web
  webRTCPage.onTimeSyncFromWeb(onTimeSyncReceived);

  // Set callback for time request from web
  webRTCPage.onTimeRequestToWeb(onTimeRequested);

  // Start the WebApp server
  if (!webAppsServer.begin(WIFI_SSID, WIFI_PASSWORD)) {
    while (1) {
      Serial.println("Failed to connect to WiFi");
      delay(1000);
    }
  }
}

void loop() {
  // Handle web server
  webAppsServer.loop();

  // Send current time to web clients and print to Serial every 1 second
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate >= 1000) {
    lastUpdate = millis();

    // Get current RTC time
    RTCTime currentTime;
    RTC.getTime(currentTime);

    // Send time to web clients in human readable format
    webRTCPage.sendTimeToWeb(currentTime.getYear(), Month2int(currentTime.getMonth()),
                             currentTime.getDayOfMonth(), currentTime.getHour(),
                             currentTime.getMinutes(), currentTime.getSeconds());  // Print time to Serial Monitor
    Serial.print("RTC Time: ");
    Serial.print(currentTime.getYear());
    Serial.print("/");
    Serial.print(Month2int(currentTime.getMonth()));
    Serial.print("/");
    Serial.print(currentTime.getDayOfMonth());
    Serial.print(" - ");
    if (currentTime.getHour() < 10) Serial.print("0");
    Serial.print(currentTime.getHour());
    Serial.print(":");
    if (currentTime.getMinutes() < 10) Serial.print("0");
    Serial.print(currentTime.getMinutes());
    Serial.print(":");
    if (currentTime.getSeconds() < 10) Serial.print("0");
    Serial.print(currentTime.getSeconds());
    Serial.println();
  }

  delay(10);
}

// Callback function called when web client sends time sync command
void onTimeSyncReceived(unsigned long unixTimestamp) {
  Serial.print("Time sync received: ");
  Serial.println(unixTimestamp);

  // Convert Unix timestamp to RTCTime
  RTCTime newTime;
  newTime.setUnixTime(unixTimestamp);

  // Set RTC time
  RTC.setTime(newTime);

  Serial.println("Arduino RTC synchronized!");
}

// Callback function called when web client requests current Arduino time
void onTimeRequested() {
  // Get current RTC time and send to web in human readable format
  RTCTime currentTime;
  RTC.getTime(currentTime);

  webRTCPage.sendTimeToWeb(currentTime.getYear(), Month2int(currentTime.getMonth()),
                           currentTime.getDayOfMonth(), currentTime.getHour(),
                           currentTime.getMinutes(), currentTime.getSeconds());
}