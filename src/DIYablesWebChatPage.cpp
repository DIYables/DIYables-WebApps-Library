#include "DIYablesWebChatPage.h"
#include "html/chat.h"
#include <string.h>

// Callback function pointer specific to WebChat
void (*webChatCallback)(const String& message) = nullptr;

DIYablesWebChatPage::DIYablesWebChatPage() : DIYablesWebAppPageBase("/chat") {
}

void DIYablesWebChatPage::handleHTTPRequest(IWebClient& client) {
    sendHTTPHeader(client);
    sendLargeHTML(client, CHAT_HTML);  // Use chunked sending for large HTML
}

void DIYablesWebChatPage::handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) {
    // Only handle messages intended for chat (with CHAT: prefix)
    if (strncmp(message, "CHAT:", 5) != 0) {
        // Ignore messages from other pages
        return;
    }
    
    if (webChatCallback) {
        const char* chatMessage = message + 5; // Skip "CHAT:" prefix
        String messageStr(chatMessage); // Convert to String for callback compatibility
        webChatCallback(messageStr);
    }
}

void DIYablesWebChatPage::onChatMessage(void (*callback)(const String& message)) {
    webChatCallback = callback;
}

void DIYablesWebChatPage::sendToChat(const String& message) {
    // Send to all connected clients - chat messages should be broadcast
    broadcastToAllClients(message.c_str());
}

const char* DIYablesWebChatPage::getPageInfo() const {
    return "💬 WebChat";
}

String DIYablesWebChatPage::getNavigationInfo() const {
    return "<a href=\"/chat\" class=\"app-card chat\" style=\"background: linear-gradient(135deg, #43e97b 0%, #38f9d7 100%);\">"
           "<h3>💬 WebChat</h3>"
           "<p>Real-time communication interface</p>"
           "</a>";
}
