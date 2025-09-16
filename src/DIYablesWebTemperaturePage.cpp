#include "DIYablesWebTemperaturePage.h"
#include "html/web_temperature.h"
#include <string.h>

// Callback function pointer specific to WebTemperature
void (*webTemperatureValueCallback)() = nullptr;

DIYablesWebTemperaturePage::DIYablesWebTemperaturePage(float minTemp, float maxTemp, const String& unit) : DIYablesWebAppPageBase("/web-temperature") {
    _minTemp = minTemp;
    _maxTemp = maxTemp;
    _unit = unit;
    _configSent = false;
}

void DIYablesWebTemperaturePage::handleHTTPRequest(IWebClient& client) {
    sendHTTPHeader(client);
    sendLargeHTML(client, HTML_CONTENT_TEMPERATURE);  // Use chunked sending for large HTML
}

void DIYablesWebTemperaturePage::handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) {
    // Only handle messages intended for temperature (with TEMP: prefix)
    if (strncmp(message, "TEMP:", 5) != 0) {
        // Ignore messages from other pages
        return;
    }
    
    Serial.print("WebTemperature WebSocket received: ");
    Serial.println(message);
    
    if (strcmp(message, "TEMP:GET_CONFIG") == 0) {
        // Automatically send configuration
        char response[256];
        snprintf(response, sizeof(response), "TEMP_CONFIG:{\"minValue\":%.1f,\"maxValue\":%.1f,\"unit\":\"%s\"}", 
                _minTemp, _maxTemp, _unit.c_str());
        broadcastToAllClients(response);
    } else if (strcmp(message, "TEMP:REQUEST_VALUE") == 0) {
        // Send current temperature using callback if set
        if (webTemperatureValueCallback) {
            webTemperatureValueCallback();
        }
    }
}

const char* DIYablesWebTemperaturePage::getPageInfo() const {
    return "🌡️ Web Temperature";
}

String DIYablesWebTemperaturePage::getNavigationInfo() const {
    return "<a href=\"/web-temperature\" class=\"app-card temperature\" style=\"background: linear-gradient(135deg, #ff6b6b 0%, #ffa8a8 100%); color: #333;\">"
           "<h3>🌡️ Web Temperature</h3>"
           "<p>Monitor temperature with thermometer visualization</p>"
           "</a>";
}

void DIYablesWebTemperaturePage::sendTemperature(float temperature) {
    char message[128];
    snprintf(message, sizeof(message), "TEMP_VALUE:{\"value\":%.1f,\"unit\":\"%s\"}", 
            temperature, _unit.c_str());
    broadcastToAllClients(message);
}

void DIYablesWebTemperaturePage::onTemperatureValueRequested(void (*callback)()) {
    webTemperatureValueCallback = callback;
}
