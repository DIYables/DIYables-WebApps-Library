#include "DIYablesWebSliderPage.h"
#include "html/web_slider.h"
#include <string.h>

// Callback function pointers specific to WebSlider
void (*webSliderCallback)(int slider1, int slider2) = nullptr;
void (*webSliderConfigCallback)() = nullptr;

DIYablesWebSliderPage::DIYablesWebSliderPage() : DIYablesWebAppPageBase("/web-slider") {
}

void DIYablesWebSliderPage::handleHTTPRequest(IWebClient& client) {
    sendHTTPHeader(client);
    sendLargeHTML(client, WEB_SLIDER_HTML);  // Use chunked sending for large HTML
}

void DIYablesWebSliderPage::handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) {
    // Only handle messages intended for web slider (with SLIDER: prefix)
    if (strncmp(message, "SLIDER:", 7) != 0) {
        // Ignore messages from other pages
        return;
    }
    
    Serial.print("WebSlider WebSocket received: ");
    Serial.println(message);
    
    // Handle request for current slider values first (before parsing coordinates)
    if (strcmp(message, "SLIDER:GET_VALUES") == 0) {
        if (webSliderConfigCallback) {
            webSliderConfigCallback();
        }
        return;
    }
    
    // Parse SLIDER value commands like "SLIDER:128,255"
    // FIXED: Add length check like WebJoystick to prevent malformed message issues
    if (length > 7) {
        Serial.println("Parsing slider data");
        const char* values = message + 7; // Skip "SLIDER:" prefix
        const char* commaPos = strchr(values, ',');
        if (commaPos != nullptr) {
            Serial.print("Found comma at position: ");
            Serial.println(commaPos - values);
            
            // Parse first slider value
            char slider1Str[16];
            int len1 = commaPos - values;
            if (len1 < sizeof(slider1Str)) {
                strncpy(slider1Str, values, len1);
                slider1Str[len1] = '\0';
                int slider1 = atoi(slider1Str);
                
                // Parse second slider value
                int slider2 = atoi(commaPos + 1);
                
                Serial.print("Parsed slider values: slider1=");
                Serial.print(slider1);
                Serial.print(", slider2=");
                Serial.println(slider2);
                
                if (webSliderCallback) {
                    Serial.println("Calling slider callback");
                    webSliderCallback(slider1, slider2);
                } else {
                    Serial.println("No slider callback registered");
                }
            } else {
                Serial.println("Slider1 value too long");
            }
        } else {
            Serial.println("No comma found in slider message");
        }
    } // FIXED: Added missing closing brace for if (length > 7)
}

void DIYablesWebSliderPage::onSliderValueFromWeb(void (*callback)(int slider1, int slider2)) {
    webSliderCallback = callback;
}

void DIYablesWebSliderPage::onSliderValueToWeb(void (*callback)()) {
    webSliderConfigCallback = callback;
}

void DIYablesWebSliderPage::sendToWebSlider(const String& message) {
    // Send to all connected clients - slider responses should go to all clients
    broadcastToAllClients(message.c_str());
}

void DIYablesWebSliderPage::sendToWebSlider(int slider1, int slider2) {
    // Format the message and send - use SLIDER_VALUES for current values response
    char message[64];
    snprintf(message, sizeof(message), "SLIDER_VALUES:%d,%d", slider1, slider2);
    broadcastToAllClients(message);
}

const char* DIYablesWebSliderPage::getPageInfo() const {
    return "🎚️ Web Slider";
}

String DIYablesWebSliderPage::getNavigationInfo() const {
    return "<a href=\"/web-slider\" class=\"app-card slider\" style=\"background: linear-gradient(135deg, #a8edea 0%, #fed6e3 100%); color: #333;\">"
           "<h3>🎚️ Web Slider</h3>"
           "<p>Control values with interactive sliders</p>"
           "</a>";
}
