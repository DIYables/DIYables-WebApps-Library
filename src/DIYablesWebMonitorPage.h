#ifndef DIYABLES_WEB_MONITOR_PAGE_H
#define DIYABLES_WEB_MONITOR_PAGE_H

#include "DIYablesWebAppPageBase.h"

// Callback function pointer specific to WebMonitor
extern void (*webMonitorCallback)(const String& message);

/**
 * WebMonitor page handler - manages monitoring interface
 */
class DIYablesWebMonitorPage : public DIYablesWebAppPageBase {
public:
    DIYablesWebMonitorPage();
    
    // Inherited virtual methods
    void handleHTTPRequest(IWebClient& client) override;
    void handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) override;
    const char* getPageInfo() const override;
    String getNavigationInfo() const override;
    
    // Callback setter
    void onWebMonitorMessage(void (*callback)(const String& message));
    
    // Send methods
    void sendToWebMonitor(const String& message);
};

#endif
