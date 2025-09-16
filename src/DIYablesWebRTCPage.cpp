#include "DIYablesWebRTCPage.h"
#include "html/web_rtc.h"
#include <string.h>
#include <stdlib.h>

// Callback function pointers specific to WebRTC
void (*webRTCTimeSyncCallback)(unsigned long unixTimestamp) = nullptr;
void (*webRTCLocalTimeSyncCallback)(int year, int month, int day, int hour, int minute, int second) = nullptr;
void (*webRTCConfigCallback)() = nullptr;

DIYablesWebRTCPage::DIYablesWebRTCPage() : DIYablesWebAppPageBase("/web-rtc") {
}

void DIYablesWebRTCPage::handleHTTPRequest(IWebClient& client) {
    sendHTTPHeader(client);
    sendLargeHTML(client, WEB_RTC_HTML);  // Use chunked sending for large HTML
}

void DIYablesWebRTCPage::handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) {
    // Only handle messages intended for web RTC (with RTC: prefix)
    if (strncmp(message, "RTC:", 4) != 0) {
        // Ignore messages from other pages
        return;
    }
    
    Serial.print("WebRTC WebSocket received: ");
    Serial.println(message);
    
    // Handle request for current time first
    if (strcmp(message, "RTC:GET_TIME") == 0) {
        if (webRTCConfigCallback) {
            webRTCConfigCallback();
        }
        return;
    }
    
    // Handle time synchronization command
    if (strncmp(message, "RTC:SYNC:", 9) == 0) {
        const char* timestampStr = message + 9; // Skip "RTC:SYNC:" prefix
        unsigned long unixTimestamp = atol(timestampStr);
        if (webRTCTimeSyncCallback && unixTimestamp > 0) {
            webRTCTimeSyncCallback(unixTimestamp);
        }
        return;
    }
}

void DIYablesWebRTCPage::onTimeSyncFromWeb(void (*callback)(unsigned long unixTimestamp)) {
    webRTCTimeSyncCallback = callback;
}

void DIYablesWebRTCPage::onLocalTimeSyncFromWeb(void (*callback)(int year, int month, int day, int hour, int minute, int second)) {
    webRTCLocalTimeSyncCallback = callback;
}

void DIYablesWebRTCPage::onTimeRequestToWeb(void (*callback)()) {
    webRTCConfigCallback = callback;
}

void DIYablesWebRTCPage::sendToWebRTC(const String& message) {
    // Send to all connected clients - RTC responses should go to all clients
    broadcastToAllClients(message.c_str());
}

void DIYablesWebRTCPage::sendTimeToWeb(unsigned long unixTimestamp) {
    String message = "TIME:" + String(unixTimestamp);
    sendToWebRTC(message);
}

void DIYablesWebRTCPage::sendTimeToWeb(int year, int month, int day, int hour, int minute, int second) {
    String message = "DATETIME:" + String(year) + "," + String(month) + "," + String(day) + "," + 
                     String(hour) + "," + String(minute) + "," + String(second);
    sendToWebRTC(message);
}

const char* DIYablesWebRTCPage::getPageInfo() const {
    return "🕐 Web RTC";
}

String DIYablesWebRTCPage::getNavigationInfo() const {
    return "<a href=\"/web-rtc\" class=\"app-card rtc\" style=\"background: linear-gradient(135deg, #ffecd2 0%, #fcb69f 100%); color: #333;\">"
           "<h3>🕐 Web RTC</h3>"
           "<p>Real-time clock display and time synchronization</p>"
           "</a>";
}
