#include "DIYablesWebMonitorPage.h"
#include "html/web_monitor.h"
#include <string.h>

// Callback function pointer specific to WebMonitor
void (*webMonitorCallback)(const String& message) = nullptr;

DIYablesWebMonitorPage::DIYablesWebMonitorPage() : DIYablesWebAppPageBase("/web-monitor") {
}

void DIYablesWebMonitorPage::handleHTTPRequest(IWebClient& client) {
    sendHTTPHeader(client);
    sendLargeHTML(client, WEB_MONITOR_HTML);  // Use chunked sending for large HTML
}

void DIYablesWebMonitorPage::handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) {
    // Only handle messages intended for web monitor (with MONITOR: prefix)
    if (strncmp(message, "MONITOR:", 8) != 0) {
        // Ignore messages from other pages
        return;
    }
    
    Serial.print("WebMonitor WebSocket received: ");
    Serial.println(message);
    
    if (webMonitorCallback) {
        const char* monitorMessage = message + 8; // Skip "MONITOR:" prefix
        String messageStr(monitorMessage); // Convert to String for callback compatibility
        webMonitorCallback(messageStr);
    }
}

void DIYablesWebMonitorPage::onWebMonitorMessage(void (*callback)(const String& message)) {
    webMonitorCallback = callback;
}

void DIYablesWebMonitorPage::sendToWebMonitor(const String& message) {
    // Send to all connected clients - monitor messages should be broadcast
    broadcastToAllClients(message.c_str());
}

const char* DIYablesWebMonitorPage::getPageInfo() const {
    return "📊 Web Monitor";
}

String DIYablesWebMonitorPage::getNavigationInfo() const {
    return "<a href=\"/web-monitor\" class=\"app-card monitor\" style=\"background: linear-gradient(135deg, #4facfe 0%, #00f2fe 100%);\">"
           "<h3>📊 Web Monitor</h3>"
           "<p>Monitor Arduino data in real-time</p>"
           "</a>";
}
