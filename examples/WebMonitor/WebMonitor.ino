/*
 * DIYables WebApp Library - Web Monitor Example
 * 
 * This example demonstrates the Web Monitor feature:
 * - Real-time serial monitor in web browser
 * - Send commands from browser to Arduino
 * - Automatic message timestamping
 * 
 * Hardware: Arduino Uno R4 WiFi or DIYables STEM V4 IoT
 * 
 * Setup:
 * 1. Update WiFi credentials below
 * 2. Upload the sketch to your Arduino
 * 3. Open Serial Monitor to see the IP address
 * 4. Navigate to http://[IP_ADDRESS]/webmonitor
 */

#include <DIYablesWebApps.h>

// WiFi credentials - UPDATE THESE WITH YOUR NETWORK
const char WIFI_SSID[] = "YOUR_WIFI_SSID";
const char WIFI_PASSWORD[] = "YOUR_WIFI_PASSWORD";

// Create WebApp server and page instances
UnoR4ServerFactory serverFactory;
DIYablesWebAppServer webAppsServer(serverFactory, 80, 81);
DIYablesHomePage homePage;
DIYablesWebMonitorPage webMonitorPage;

// Demo variables
unsigned long lastMessage = 0;
int messageCount = 0;

void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.println("DIYables WebApp - Web Monitor Example");

  // Add home and web monitor pages
  webAppsServer.addApp(&homePage);
  webAppsServer.addApp(&webMonitorPage);

  // Optional: Add 404 page for better user experience
  webAppsServer.setNotFoundPage(DIYablesNotFoundPage());

  // Initialize LED for status indication
  pinMode(LED_BUILTIN, OUTPUT);

  // Start the WebApp server
  if (!webAppsServer.begin(WIFI_SSID, WIFI_PASSWORD)) {
    while (1) {
      Serial.println("Failed to start WebApp server!");
      delay(1000);
    }
  }

  // Set up monitor callback for incoming commands
  webMonitorPage.onWebMonitorMessage([](const String& message) {
    Serial.println("Command from web: " + message);

    // Process simple commands
    if (message == "LED_ON") {
      digitalWrite(LED_BUILTIN, HIGH);
      webMonitorPage.sendToWebMonitor("LED turned ON");
      return;
    }

    if (message == "LED_OFF") {
      digitalWrite(LED_BUILTIN, LOW);
      webMonitorPage.sendToWebMonitor("LED turned OFF");
      return;
    }

    if (message == "STATUS") {
      String status = "Arduino Status: LED=" + String(digitalRead(LED_BUILTIN) ? "ON" : "OFF");
      webMonitorPage.sendToWebMonitor(status);
      return;
    }

    if (message == "HELP") {
      webMonitorPage.sendToWebMonitor("Available commands: LED_ON, LED_OFF, STATUS, HELP");
      return;
    }

    webMonitorPage.sendToWebMonitor("Unknown command: " + message);
  });

  // Send welcome message
  webMonitorPage.sendToWebMonitor("Arduino Web Monitor ready!");
  webMonitorPage.sendToWebMonitor("Type HELP for available commands");
}

void loop() {
  // Handle WebApp server communications
  webAppsServer.loop();

  // Send periodic updates to web monitor
  if (millis() - lastMessage > 5000) {  // Every 5 seconds
    messageCount++;

    // Send sensor readings or status updates
    String message = "Message #" + String(messageCount) + " - Uptime: " + String(millis() / 1000) + "s";
    webMonitorPage.sendToWebMonitor(message);

    lastMessage = millis();
  }

  // Add your main application code here

  delay(10);
}
