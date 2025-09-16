#include "DIYablesHomePage.h"
#include "DIYablesWebAppServer.h"
#include "html/home_page_start.h"
#include "html/home_page_end.h"

DIYablesHomePage::DIYablesHomePage() : DIYablesWebAppPageBase("/") {
}

void DIYablesHomePage::handleHTTPRequest(IWebClient& client) {
    sendHTTPHeader(client);
    
    // Send the start of the HTML
    client.print(HOME_PAGE_START_HTML);
    
    // Build navigation for all added pages (except home itself)
    if (server) {
        bool hasApps = false;
        
        // Get all pages from server and generate their navigation
        for (int i = 0; i < server->getAppCount(); i++) {
            const DIYablesWebAppPageBase* page = server->getAppByIndex(i);
            if (page && page != this) { // Don't include home page itself
                client.print(page->getNavigationInfo());
                hasApps = true;
            }
        }
        
        // Show message if no apps are available
        if (!hasApps) {
            client.print("<div class=\"no-apps\">"
                        "<h3>No Applications Available</h3>"
                        "<p>Add applications using server.addApp() to see them here.</p>"
                        "</div>");
        }
    }
    
    // Send the end of the HTML
    client.print(HOME_PAGE_END_HTML);
}

void DIYablesHomePage::handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) {
    // Home page typically doesn't need special WebSocket handling
    // This is mainly for navigation and information display
}

const char* DIYablesHomePage::getPageInfo() const {
    return "🏠 Home Page";
}

String DIYablesHomePage::getNavigationInfo() const {
    // Home page shouldn't appear in its own navigation
    return "";
}
