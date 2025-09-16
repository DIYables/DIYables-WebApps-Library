#ifndef DIYABLES_HOME_PAGE_H
#define DIYABLES_HOME_PAGE_H

#include "DIYablesWebAppPageBase.h"

/**
 * Home page handler - manages the main landing page
 */
class DIYablesHomePage : public DIYablesWebAppPageBase {
public:
    DIYablesHomePage();
    
    // Inherited virtual methods
    void handleHTTPRequest(IWebClient& client) override;
    void handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) override;
    const char* getPageInfo() const override;
    String getNavigationInfo() const override;
};

#endif
