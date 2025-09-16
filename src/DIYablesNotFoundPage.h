#ifndef DIYABLES_NOT_FOUND_PAGE_H
#define DIYABLES_NOT_FOUND_PAGE_H

#include "DIYablesWebAppPageBase.h"

// Forward declaration
class DIYablesWebAppServer;

/**
 * 404 Not Found page handler - serves static 404 error page
 */
class DIYablesNotFoundPage : public DIYablesWebAppPageBase {
public:
    DIYablesNotFoundPage();
    
    // Inherited virtual methods
    void handleHTTPRequest(IWebClient& client) override;
    void handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) override;
    const char* getPageInfo() const override;
    String getNavigationInfo() const override;
};

#endif
