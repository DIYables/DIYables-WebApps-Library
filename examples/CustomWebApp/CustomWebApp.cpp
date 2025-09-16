#include "CustomWebApp.h"
#include "custom_page_html.h"

// Define the static member - WebSocket message identifier for this custom app
const String CustomWebAppPage::APP_IDENTIFIER = "CUSTOM:";

// Callback function for handling messages from web browser
void (*customMessageCallback)(const String& payload) = nullptr;

CustomWebAppPage::CustomWebAppPage() : DIYablesWebAppPageBase("/custom") {
}

void CustomWebAppPage::handleHTTPRequest(IWebClient& client) {
    // Send the HTML page to web browser
    sendHTTPHeader(client);
    client.print(CUSTOM_PAGE_HTML);
}

void CustomWebAppPage::handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) {
    String messageStr = String(message, length);
    Serial.print("Custom WebApp received: ");
    Serial.println(messageStr);
    
    // Only handle messages that start with our app identifier
    if (messageStr.startsWith(APP_IDENTIFIER)) {
        String payload = messageStr.substring(APP_IDENTIFIER.length()); // Remove identifier
        
        // Call your callback function with the payload
        if (customMessageCallback) {
            customMessageCallback(payload);
        }
    }
}

void CustomWebAppPage::onCustomMessageReceived(void (*callback)(const String& payload)) {
    customMessageCallback = callback;
}

void CustomWebAppPage::sendToWeb(const String& message) {
    // Send message to web browser with app identifier
    String fullMessage = APP_IDENTIFIER + message;
    broadcastToAllClients(fullMessage.c_str());
}

const char* CustomWebAppPage::getPageInfo() const {
    return "🔧 Custom WebApp";
}

String CustomWebAppPage::getNavigationInfo() const {
    String result = "<a href=\"";
    result += getPagePath();
    result += "\" class=\"app-card custom\" style=\"background: linear-gradient(135deg, #007bff 0%, #0056b3 100%);\">";
    result += "<h3>🔧 Custom WebApp</h3>";
    result += "<p>Simple template for your own apps</p>";
    result += "</a>";
    return result;
}
