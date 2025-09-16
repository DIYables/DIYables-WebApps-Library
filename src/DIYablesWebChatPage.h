#ifndef DIYABLES_WEB_CHAT_PAGE_H
#define DIYABLES_WEB_CHAT_PAGE_H

#include "DIYablesWebAppPageBase.h"

// Callback function pointer specific to WebChat
extern void (*webChatCallback)(const String& message);

/**
 * WebChat page handler - manages chat interface
 */
class DIYablesWebChatPage : public DIYablesWebAppPageBase {
public:
    DIYablesWebChatPage();
    
    // Inherited virtual methods
    void handleHTTPRequest(IWebClient& client) override;
    void handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) override;
    const char* getPageInfo() const override;
    String getNavigationInfo() const override;
    
    // Callback setter
    void onChatMessage(void (*callback)(const String& message));
    
    // Send methods
    void sendToChat(const String& message);
};

#endif
