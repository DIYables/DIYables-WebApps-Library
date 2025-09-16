#include "DIYablesWebDigitalPinsPage.h"
#include "html/web_digital_pins.h"
#include <string.h>

// Callback function pointers
void (*webDigitalPinWriteCallback)(int pin, int state) = nullptr;
int (*webDigitalPinReadCallback)(int pin) = nullptr;
void (*webDigitalPinModeChangeCallback)(int pin, int mode) = nullptr;

DIYablesWebDigitalPinsPage::DIYablesWebDigitalPinsPage() : DIYablesWebAppPageBase("/web-digital-pins") {
    // Initialize pin management arrays - all pins disabled by default
    for (int i = 0; i < 16; i++) {
        enabledPins[i] = false;
        pinModes[i] = WEB_PIN_OUTPUT; // Default to output mode
    }
}

void DIYablesWebDigitalPinsPage::handleHTTPRequest(IWebClient& client) {
    Serial.println("DEBUG: Serving WebDigitalPins page (static HTML)");
    
    sendHTTPHeader(client);
    sendLargeHTML(client, WEB_DIGITAL_PINS_HTML);  // Use chunked sending for large HTML
    
    Serial.println("DEBUG: Static WebDigitalPins page sent successfully");
}

void DIYablesWebDigitalPinsPage::handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) {
    // Only handle messages intended for digital pins (with DIGITAL_PINS: prefix)
    if (strncmp(message, "DIGITAL_PINS:", 13) != 0) {
        // Ignore messages from other pages
        return;
    }
    
    Serial.print("WebDigitalPins WebSocket received: ");
    Serial.println(message);
    
    // Remove DIGITAL_PINS: prefix and process the actual command
    const char* actualMessage = message + 13; // Skip "DIGITAL_PINS:" prefix
    
    // Handle pin configuration request
    if (strcmp(actualMessage, "GET_PIN_CONFIG") == 0) {
        Serial.println("DEBUG: Sending pin configuration via WebSocket");
        
        String pinConfigMsg = buildPinConfigJson();
        sendWebSocketMessage(ws, pinConfigMsg.c_str());
        Serial.print("DEBUG: Sent pin config: ");
        Serial.println(pinConfigMsg);
        return;
    }
    
    // Handle pin control commands
    if (strncmp(actualMessage, "PIN_", 4) == 0) {
        String actualMessageStr(actualMessage); // Convert to String for existing method compatibility
        handlePinCommand(actualMessageStr, ws);
        return;
    }
    
    // Handle pin mode change commands
    if (strncmp(actualMessage, "MODE_", 5) == 0) {
        String actualMessageStr(actualMessage); // Convert to String for existing method compatibility
        handlePinModeCommand(actualMessageStr, ws);
        return;
    }
    
    // Handle bulk control commands (only for output pins)
    if (strcmp(actualMessage, "ALL_ON") == 0 || strcmp(actualMessage, "ALL_OFF") == 0 || strcmp(actualMessage, "TOGGLE_ALL") == 0) {
        String actualMessageStr(actualMessage); // Convert to String for existing method compatibility
        handleBulkCommand(actualMessageStr);
        return;
    }
    
    // Handle request for current pin states
    if (strcmp(actualMessage, "GET_PIN_STATES") == 0) {
        String statesJson = buildPinStatesJson();
        String responseMessage = "PIN_STATES:" + statesJson;
        sendWebSocketMessage(ws, responseMessage.c_str());
        Serial.print("DEBUG: Sent pin states: ");
        Serial.println(responseMessage);
        return;
    }
}

String DIYablesWebDigitalPinsPage::buildPinConfigJson() {
    String configJson = "PIN_CONFIG:{\"pins\":[";
    bool firstPin = true;
    
    for (int pin = 0; pin <= 13; pin++) {
        if (isPinEnabled(pin)) {
            if (!firstPin) configJson += ",";
            configJson += "{\"pin\":" + String(pin) + ",\"mode\":\"";
            
            switch (getPinMode(pin)) {
                case WEB_PIN_OUTPUT:
                    configJson += "OUTPUT";
                    break;
                case WEB_PIN_INPUT:
                    configJson += "INPUT";
                    break;
            }
            configJson += "\"}";
            firstPin = false;
        }
    }
    configJson += "]}";
    
    return configJson;
}

String DIYablesWebDigitalPinsPage::buildPinStatesJson() {
    if (!webDigitalPinReadCallback) {
        return "{}";
    }
    
    String statesJson = "{";
    bool first = true;
    
    for (int pin = 0; pin <= 13; pin++) {
        if (isPinEnabled(pin)) {
            if (!first) statesJson += ",";
            int pinState = webDigitalPinReadCallback(pin);
            statesJson += "\"" + String(pin) + "\":\"" + (pinState == HIGH ? "ON" : "OFF") + "\"";
            first = false;
        }
    }
    statesJson += "}";
    
    return statesJson;
}

void DIYablesWebDigitalPinsPage::handlePinCommand(const String& message, IWebSocket& ws) {
    // Parse PIN commands like "PIN_6_ON" or "PIN_13_OFF" (only for output pins)
    int underscore = message.indexOf('_', 4);  // Find underscore after "PIN_"
    
    if (underscore != -1) {
        String pinStr = message.substring(4, underscore);   // Extract pin number
        String value = message.substring(underscore + 1);   // "ON" or "OFF"
        int pin = pinStr.toInt();
        
        Serial.print("DEBUG: Pin control - Pin: ");
        Serial.print(pin);
        Serial.print(", Value: ");
        Serial.println(value);
        
        // Check if pin is enabled and is an output pin
        if (isPinEnabled(pin) && getPinMode(pin) == WEB_PIN_OUTPUT) {
            if (webDigitalPinWriteCallback) {
                if (value == "ON") {
                    webDigitalPinWriteCallback(pin, HIGH);
                } else if (value == "OFF") {
                    webDigitalPinWriteCallback(pin, LOW);
                }
                
                // Send all pin states to keep all clients synchronized
                String statesJson = buildPinStatesJson();
                String responseMessage = "PIN_STATES:" + statesJson;
                sendToWebDigitalPins(responseMessage);
                Serial.print("DEBUG: Updated pin states after individual control: ");
                Serial.println(responseMessage);
            }
        } else {
            Serial.println("DEBUG: Pin not controllable (not enabled or not output mode)");
        }
    } else {
        Serial.print("DEBUG: Could not parse PIN command: ");
        Serial.println(message);
    }
}

void DIYablesWebDigitalPinsPage::handlePinModeCommand(const String& message, IWebSocket& ws) {
    // Parse MODE commands like "MODE_6_OUTPUT" or "MODE_8_INPUT"
    int underscore = message.indexOf('_', 5);  // Find underscore after "MODE_"
    
    if (underscore != -1) {
        String pinStr = message.substring(5, underscore);   // Extract pin number
        String modeStr = message.substring(underscore + 1); // "OUTPUT", "INPUT", or "INPUT_PULLUP"
        int pin = pinStr.toInt();
        
        Serial.print("DEBUG: Pin mode change - Pin: ");
        Serial.print(pin);
        Serial.print(", Mode: ");
        Serial.println(modeStr);
        
        if (isPinEnabled(pin)) {
            int newMode;
            if (modeStr == "OUTPUT") {
                newMode = WEB_PIN_OUTPUT;
            } else if (modeStr == "INPUT") {
                newMode = WEB_PIN_INPUT;
            } else {
                Serial.println("DEBUG: Invalid pin mode");
                return;
            }
            
            // Update internal mode tracking
            setPinMode(pin, newMode);
            
            // Notify application of mode change
            if (webDigitalPinModeChangeCallback) {
                webDigitalPinModeChangeCallback(pin, newMode);
            }
            
            // Send updated configuration to all clients
            String configJson = buildPinConfigJson();
            sendToWebDigitalPins(configJson);
            Serial.print("DEBUG: Updated pin configuration: ");
            Serial.println(configJson);
        }
    }
}

void DIYablesWebDigitalPinsPage::handleBulkCommand(const String& command) {
    if (webDigitalPinWriteCallback && webDigitalPinReadCallback) {
        // Apply bulk command only to output pins
        for (int pin = 0; pin <= 13; pin++) {
            if (isPinEnabled(pin) && getPinMode(pin) == WEB_PIN_OUTPUT) {
                int newState;
                if (command.equals("ALL_ON")) {
                    newState = HIGH;
                } else if (command.equals("ALL_OFF")) {
                    newState = LOW;
                } else { // TOGGLE_ALL
                    int currentState = webDigitalPinReadCallback(pin);
                    newState = (currentState == HIGH) ? LOW : HIGH;
                }
                
                // Control the pin through callback
                webDigitalPinWriteCallback(pin, newState);
            }
        }
        
        // Send all pin states at once
        String statesJson = buildPinStatesJson();
        String responseMessage = "PIN_STATES:" + statesJson;
        sendToWebDigitalPins(responseMessage);
        Serial.print("DEBUG: Sent bulk pin states: ");
        Serial.println(responseMessage);
    }
}

// Pin management methods
void DIYablesWebDigitalPinsPage::enablePin(int pin, int mode) {
    if (pin >= 0 && pin <= 13) {
        Serial.print("DEBUG: Enabling pin ");
        Serial.print(pin);
        Serial.print(" with mode ");
        Serial.println(mode == WEB_PIN_OUTPUT ? "OUTPUT" : "INPUT");
        enabledPins[pin] = true;
        pinModes[pin] = mode;
    } else {
        Serial.print("DEBUG: Invalid pin number: ");
        Serial.println(pin);
    }
}

void DIYablesWebDigitalPinsPage::disablePin(int pin) {
    if (pin >= 0 && pin <= 13) {
        enabledPins[pin] = false;
    }
}

void DIYablesWebDigitalPinsPage::enableAllPins(int mode) {
    for (int pin = 0; pin <= 13; pin++) {
        enabledPins[pin] = true;
        pinModes[pin] = mode;
    }
}

void DIYablesWebDigitalPinsPage::disableAllPins() {
    for (int pin = 0; pin <= 13; pin++) {
        enabledPins[pin] = false;
    }
}

bool DIYablesWebDigitalPinsPage::isPinEnabled(int pin) {
    if (pin >= 0 && pin <= 13) {
        return enabledPins[pin];
    }
    return false;
}

int DIYablesWebDigitalPinsPage::getPinMode(int pin) {
    if (pin >= 0 && pin <= 13) {
        return pinModes[pin];
    }
    return WEB_PIN_OUTPUT; // Default
}

void DIYablesWebDigitalPinsPage::setPinMode(int pin, int mode) {
    if (pin >= 0 && pin <= 13) {
        pinModes[pin] = mode;
    }
}

int DIYablesWebDigitalPinsPage::getEnabledPinCount() {
    int count = 0;
    for (int pin = 0; pin <= 13; pin++) {
        if (enabledPins[pin]) count++;
    }
    return count;
}

// Callback setters
void DIYablesWebDigitalPinsPage::onPinWrite(void (*callback)(int pin, int state)) {
    webDigitalPinWriteCallback = callback;
}

void DIYablesWebDigitalPinsPage::onPinRead(int (*callback)(int pin)) {
    webDigitalPinReadCallback = callback;
}

void DIYablesWebDigitalPinsPage::onPinModeChange(void (*callback)(int pin, int mode)) {
    webDigitalPinModeChangeCallback = callback;
}

// Send methods
void DIYablesWebDigitalPinsPage::sendToWebDigitalPins(const String& message) {
    broadcastToAllClients(message.c_str());
}

void DIYablesWebDigitalPinsPage::updatePinState(int pin, int state) {
    // Send real-time input pin state update
    String message = "PIN_UPDATE:{\"pin\":" + String(pin) + ",\"state\":\"" + (state == HIGH ? "ON" : "OFF") + "\"}";
    sendToWebDigitalPins(message);
}

const char* DIYablesWebDigitalPinsPage::getPageInfo() const {
    return "📟 Digital Pins";
}

String DIYablesWebDigitalPinsPage::getNavigationInfo() const {
    return "<a href=\"/web-digital-pins\" class=\"app-card digital-pins\" style=\"background: linear-gradient(135deg, #fa709a 0%, #fee140 100%);\">"
           "<h3>📟 Digital Pins</h3>"
           "<p>Control output pins and monitor input pins via web interface</p>"
           "</a>";
}
