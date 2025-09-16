#include "DIYablesWebJoystickPage.h"
#include "html/web_joystick.h"

// Callback function pointers specific to WebJoystick
void (*webJoystickCallback)(int x, int y) = nullptr;
void (*webJoystickConfigCallback)() = nullptr;

DIYablesWebJoystickPage::DIYablesWebJoystickPage(bool autoReturn, float sensitivity) 
    : DIYablesWebAppPageBase("/web-joystick"), autoReturn(autoReturn), sensitivity(sensitivity) {
}

void DIYablesWebJoystickPage::handleHTTPRequest(IWebClient& client) {
    sendHTTPHeader(client);
    sendLargeHTML(client, web_joystick_html);  // Use chunked sending for large HTML
}

void DIYablesWebJoystickPage::handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) {
    // FIXED: Use char array operations instead of String operations
    // Only handle messages intended for web joystick (with JOYSTICK: prefix)
    if (strncmp(message, "JOYSTICK:", 9) != 0) {
        // Ignore messages from other pages
        return;
    }
    
    Serial.print("WebJoystick WebSocket received: ");
    Serial.println(message);
    
    // Handle request for joystick configuration first (before parsing coordinates)
    if (strcmp(message, "JOYSTICK:GET_CONFIG") == 0) {
        Serial.println("Processing config request");
        // FIXED: Use char array instead of String concatenation to avoid ESP32 heap corruption
        char response[128];
        snprintf(response, sizeof(response), 
                "JOYSTICK_CONFIG:{\"autoReturn\":%s,\"sensitivity\":%.1f}", 
                autoReturn ? "true" : "false", sensitivity);
        
        // CRITICAL: Send only to requesting client to avoid broadcast race conditions
        // This prevents multi-client crashes during ESP32 WebSocket operations
        sendWebSocketMessage(ws, response);
        return;
    }
    
    // Handle request for current joystick values (application-specific)
    if (strcmp(message, "JOYSTICK:GET_VALUES") == 0) {
        if (webJoystickConfigCallback) {
            webJoystickConfigCallback();
        }
        return;
    }
    
    // Parse JOYSTICK coordinate commands like "JOYSTICK:50,-75"
    // FIXED: Use char array parsing instead of String substring operations
    if (length > 9) {
        Serial.println("Parsing coordinate data");
        const char* values = message + 9;  // Skip "JOYSTICK:" prefix
        
        // Find comma position
        const char* commaPtr = strchr(values, ',');
        if (commaPtr != nullptr) {
            Serial.print("Found comma at position: ");
            Serial.println(commaPtr - values);
            
            // Parse X value
            char xStr[16];
            int xLen = commaPtr - values;
            if (xLen < sizeof(xStr)) {
                strncpy(xStr, values, xLen);
                xStr[xLen] = '\0';
                int x = atoi(xStr);
                
                // Parse Y value  
                int y = atoi(commaPtr + 1);
                
                Serial.print("Parsed coordinates: x=");
                Serial.print(x);
                Serial.print(", y=");
                Serial.println(y);
                
                if (webJoystickCallback) {
                    Serial.println("Calling joystick callback");
                    webJoystickCallback(x, y);
                } else {
                    Serial.println("No joystick callback registered");
                }
            } else {
                Serial.println("X coordinate too long");
            }
        } else {
            Serial.println("No comma found in coordinate data");
        }
    } else {
        Serial.println("Message too short for coordinate data");
    }
}

void DIYablesWebJoystickPage::setAutoReturn(bool enabled) {
    autoReturn = enabled;
}

bool DIYablesWebJoystickPage::getAutoReturn() const {
    return autoReturn;
}

void DIYablesWebJoystickPage::setSensitivity(float value) {
    sensitivity = value;
}

float DIYablesWebJoystickPage::getSensitivity() const {
    return sensitivity;
}

void DIYablesWebJoystickPage::onJoystickValueFromWeb(void (*callback)(int x, int y)) {
    webJoystickCallback = callback;
}

void DIYablesWebJoystickPage::onJoystickValueToWeb(void (*callback)()) {
    webJoystickConfigCallback = callback;
}

void DIYablesWebJoystickPage::sendToWebJoystick(const char* message) {
    // Send to all connected clients - joystick responses should go to all clients
    broadcastToAllClients(message);
}

void DIYablesWebJoystickPage::sendToWebJoystick(int x, int y) {
    // FIXED: Use char array formatting instead of String concatenation
    char message[64];
    snprintf(message, sizeof(message), "JOYSTICK:%d,%d", x, y);
    broadcastToAllClients(message);
}

const char* DIYablesWebJoystickPage::getPageInfo() const {
    return "🕹️ Web Joystick";
}

String DIYablesWebJoystickPage::getNavigationInfo() const {
    return "<a href=\"/web-joystick\" class=\"app-card joystick\" style=\"background: linear-gradient(135deg, #FF6B35 0%, #F7931E 100%); color: #fff;\">"
           "<h3>🕹️ Web Joystick</h3>"
           "<p>Virtual joystick for directional control</p>"
           "</a>";
}
