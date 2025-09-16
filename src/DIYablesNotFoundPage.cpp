#include "DIYablesNotFoundPage.h"
#include "DIYablesWebAppServer.h"
#include "html/not_found.h"

DIYablesNotFoundPage::DIYablesNotFoundPage() : DIYablesWebAppPageBase("/404") {
}

void DIYablesNotFoundPage::handleHTTPRequest(IWebClient& client) {
    client.println("HTTP/1.1 404 Not Found");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    
    // Send the HTML template directly
    client.print(NOT_FOUND_HTML);
}

void DIYablesNotFoundPage::handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) {
    Serial.print("404 WebSocket received: ");
    Serial.println(message);
    
    // 404 page typically doesn't need special WebSocket handling
}

const char* DIYablesNotFoundPage::getPageInfo() const {
    // 404 page typically shouldn't be in navigation
    return "";
}

String DIYablesNotFoundPage::getNavigationInfo() const {
    // 404 page typically shouldn't be in navigation
    return "";
}
