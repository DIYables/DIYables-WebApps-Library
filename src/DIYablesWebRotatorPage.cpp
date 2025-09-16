#include "DIYablesWebRotatorPage.h"
#include "html/web_rotator.h"
#include <string.h>

// Callback function pointer specific to WebRotator
void (*webRotatorCallback)(float angle) = nullptr;

DIYablesWebRotatorPage::DIYablesWebRotatorPage(int mode) : DIYablesWebAppPageBase("/web-rotator") {
    rotatorMode = mode;
    minAngle = 0;
    maxAngle = 360;
}

DIYablesWebRotatorPage::DIYablesWebRotatorPage(int mode, float minAng, float maxAng) : DIYablesWebAppPageBase("/web-rotator") {
    rotatorMode = mode;
    minAngle = minAng;
    maxAngle = maxAng;
}

void DIYablesWebRotatorPage::handleHTTPRequest(IWebClient& client) {
    sendHTTPHeader(client);
    sendLargeHTML(client, WEB_ROTATOR_HTML);  // Use chunked sending for large HTML
}

void DIYablesWebRotatorPage::handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) {
    // Only handle messages intended for web rotator (with ROTATOR: prefix)
    if (strncmp(message, "ROTATOR:", 8) != 0) {
        // Ignore messages from other pages
        return;
    }
    
    // Handle request for current configuration first
    if (strcmp(message, "ROTATOR:GET_CONFIG") == 0) {
        // Always handle configuration automatically - no callback needed
        char config[128];
        snprintf(config, sizeof(config), "ROTATOR:CONFIG:%d,%.1f,%.1f", rotatorMode, minAngle, maxAngle);
        broadcastToAllClients(config);
        return;
    }
    
    // Parse ROTATOR angle commands like "ROTATOR:45.5"
    const char* angleStr = message + 8; // Skip "ROTATOR:" prefix
    float angle = atof(angleStr);
    
    // Apply angle limits if in limited mode
    if (rotatorMode == ROTATOR_MODE_LIMITED) {
        if (angle < minAngle) angle = minAngle;
        if (angle > maxAngle) angle = maxAngle;
    }
    
    if (webRotatorCallback) {
        webRotatorCallback(angle);
    }
}

const char* DIYablesWebRotatorPage::getPageInfo() const {
    return "🔄 Web Rotator";
}

String DIYablesWebRotatorPage::getNavigationInfo() const {
    return "<a href=\"/web-rotator\" class=\"app-card rotator\" style=\"background: linear-gradient(135deg, #ff9a9e 0%, #fecfef 100%); color: #333;\">"
           "<h3>🔄 Web Rotator</h3>"
           "<p>Control rotation with interactive disc interface</p>"
           "</a>";
}

void DIYablesWebRotatorPage::setRotatorMode(int mode, float minAng, float maxAng) {
    rotatorMode = mode;
    minAngle = minAng;
    maxAngle = maxAng;
    
    // Send configuration to web page
    char config[128];
    snprintf(config, sizeof(config), "CONFIG:%d,%.1f,%.1f", mode, minAng, maxAng);
    sendToWebRotator(config);
}

int DIYablesWebRotatorPage::getRotatorMode() const {
    return rotatorMode;
}

float DIYablesWebRotatorPage::getMinAngle() const {
    return minAngle;
}

float DIYablesWebRotatorPage::getMaxAngle() const {
    return maxAngle;
}

void DIYablesWebRotatorPage::onRotatorAngleFromWeb(void (*callback)(float angle)) {
    webRotatorCallback = callback;
}

void DIYablesWebRotatorPage::sendToWebRotator(const String& message) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "ROTATOR:%s", message.c_str());
    broadcastToAllClients(buffer);
}

void DIYablesWebRotatorPage::sendToWebRotator(float angle) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "ROTATOR:%.1f", angle);
    broadcastToAllClients(buffer);
}
