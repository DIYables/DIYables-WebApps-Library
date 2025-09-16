#include "DIYablesWebAnalogGaugePage.h"
#include "html/web_analog_gauge.h"
#include <string.h>

// Callback function pointer specific to WebAnalogGauge
void (*webAnalogGaugeValueRequestCallback)() = nullptr;

DIYablesWebAnalogGaugePage::DIYablesWebAnalogGaugePage(float minValue, float maxValue, const String& unit) : DIYablesWebAppPageBase("/web-gauge") {
    this->minValue = minValue;
    this->maxValue = maxValue;
    this->unit = unit;
    currentValue = minValue;
}

void DIYablesWebAnalogGaugePage::handleHTTPRequest(IWebClient& client) {
    sendHTTPHeader(client);
    sendLargeHTML(client, WEB_ANALOG_GAUGE_HTML);  // Use chunked sending for large HTML
}

void DIYablesWebAnalogGaugePage::handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) {
    // Only handle messages intended for web analog gauge (with GAUGE: prefix)
    if (strncmp(message, "GAUGE:", 6) != 0) {
        // Ignore messages from other pages
        return;
    }
    
    Serial.print("WebAnalogGauge WebSocket received: ");
    Serial.println(message);
    
    // Handle request for gauge configuration first (before parsing values)
    if (strcmp(message, "GAUGE:GET_CONFIG") == 0) {
        // Always handle configuration automatically - no callback needed
        char response[256];
        snprintf(response, sizeof(response), "GAUGE_CONFIG:{\"minValue\":%.2f,\"maxValue\":%.2f,\"unit\":\"%s\"}", 
                minValue, maxValue, unit.c_str());
        broadcastToAllClients(response);
        return;
    }
    
    // Handle request for current gauge value
    if (strcmp(message, "GAUGE:REQUEST_VALUE") == 0) {
        if (webAnalogGaugeValueRequestCallback) {
            webAnalogGaugeValueRequestCallback();
        }
    }
    // Ignore all other messages
}

const char* DIYablesWebAnalogGaugePage::getPageInfo() const {
    return "⏲️ Web Analog Gauge";
}

String DIYablesWebAnalogGaugePage::getNavigationInfo() const {
    return "<a href=\"/web-gauge\" class=\"app-card gauge\" style=\"background: linear-gradient(135deg, #4CAF50 0%, #45a049 100%); color: #fff;\">"
           "<h3>⏲️ Web Analog Gauge</h3>"
           "<p>Monitor values with professional analog gauge display</p>"
           "</a>";
}

void DIYablesWebAnalogGaugePage::onGaugeValueRequest(void (*callback)()) {
    webAnalogGaugeValueRequestCallback = callback;
}

void DIYablesWebAnalogGaugePage::sendToWebAnalogGauge(float value) {
    currentValue = value;
    char message[64];
    snprintf(message, sizeof(message), "GAUGE_VALUE:%.2f", value);
    broadcastToAllClients(message);
}

void DIYablesWebAnalogGaugePage::updateGaugeValue(float value) {
    sendToWebAnalogGauge(value);
}
