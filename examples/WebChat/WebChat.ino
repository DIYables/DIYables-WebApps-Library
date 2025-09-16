/*
 * DIYables WebApp Library - WebChat Example
 * 
 * This example demonstrates the WebChat feature:
 * - Interactive chat interface
 * - Intelligent Arduino responses
 * - Built-in LED control via chat commands
 * 
 * Hardware: Arduino Uno R4 WiFi or DIYables STEM V4 IoT
 * 
 * Setup:
 * 1. Update WiFi credentials below
 * 2. Upload the sketch to your Arduino
 * 3. Open Serial Monitor to see the IP address
 * 4. Navigate to http://[IP_ADDRESS]/chat
 */

#include <DIYablesWebApps.h>

// WiFi credentials - UPDATE THESE WITH YOUR NETWORK
const char WIFI_SSID[] = "YOUR_WIFI_SSID";
const char WIFI_PASSWORD[] = "YOUR_WIFI_PASSWORD";

// Create WebApp server and page instances
UnoR4ServerFactory serverFactory;
DIYablesWebAppServer webAppsServer(serverFactory, 80, 81);
DIYablesHomePage homePage;
DIYablesWebChatPage chatPage;

// Chat variables
String userName = "";
int chatCount = 0;

void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.println("DIYables WebApp - WebChat Example");

  // Add only home and webchat pages
  webAppsServer.addApp(&homePage);
  webAppsServer.addApp(&chatPage);

  // Optional: Add 404 page for better user experience (local object)
  webAppsServer.setNotFoundPage(DIYablesNotFoundPage());

  // Initialize LED for chat commands
  pinMode(LED_BUILTIN, OUTPUT);

  // Start the WebApp server
  if (!webAppsServer.begin(WIFI_SSID, WIFI_PASSWORD)) {
    while (1) {
      Serial.println("Failed to start WebApp server!");
      delay(1000);
    }
  }

  // Set up chat callback
  chatPage.onChatMessage([](const String& message) {
    chatCount++;
    Serial.println("Chat message #" + String(chatCount) + ": " + message);

    String response = "";
    String lowerMessage = message;
    lowerMessage.toLowerCase();

    // Process chat commands
    if (lowerMessage.indexOf("hello") >= 0 || lowerMessage.indexOf("hi") >= 0) {
      response = "Hello! I'm your Arduino assistant. Try saying 'led on' or 'led off' to control the LED!";
      chatPage.sendToChat(response);
      return;
    }

    if (lowerMessage.indexOf("led on") >= 0 || lowerMessage.indexOf("light on") >= 0) {
      digitalWrite(LED_BUILTIN, HIGH);
      response = "LED is now ON! ✨";
      chatPage.sendToChat(response);
      return;
    }

    if (lowerMessage.indexOf("led off") >= 0 || lowerMessage.indexOf("light off") >= 0) {
      digitalWrite(LED_BUILTIN, LOW);
      response = "LED is now OFF! 💡";
      chatPage.sendToChat(response);
      return;
    }

    if (lowerMessage.indexOf("status") >= 0) {
      String ledStatus = digitalRead(LED_BUILTIN) ? "ON" : "OFF";
      response = "Arduino Status: LED is " + ledStatus + ", Uptime: " + String(millis() / 1000) + " seconds";
      chatPage.sendToChat(response);
      return;
    }

    if (lowerMessage.indexOf("help") >= 0) {
      response = "Available commands: 'led on', 'led off', 'status', 'help'. Just chat with me!";
      chatPage.sendToChat(response);
      return;
    }

    if (lowerMessage.indexOf("time") >= 0) {
      response = "Arduino has been running for " + String(millis() / 1000) + " seconds.";
      chatPage.sendToChat(response);
      return;
    }

    if (lowerMessage.indexOf("name") >= 0) {
      response = "I'm your Arduino Uno R4 WiFi! What's your name?";
      chatPage.sendToChat(response);
      return;
    }

    // General responses
    String responses[] = {
      "That's interesting! Tell me more.",
      "I understand! As an Arduino, I love processing your messages.",
      "Cool! I'm here and ready to help.",
      "Thanks for chatting with me! Try 'led on' to see something happen.",
      "I'm just an Arduino, but I enjoy our conversation!"
    };
    response = responses[chatCount % 5];
    chatPage.sendToChat(response);
  });

  // Send welcome message
  chatPage.sendToChat("Arduino Chat Bot is online! 🤖");
  chatPage.sendToChat("Say 'hello' or 'help' to get started!");
}

void loop() {
  // Handle WebApp server communications
  webAppsServer.loop();

  // Add your main application code here

  delay(10);
}
