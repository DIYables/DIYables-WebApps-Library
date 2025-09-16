#ifndef DIYABLES_WEBAPP_PAGE_BASE_H
#define DIYABLES_WEBAPP_PAGE_BASE_H

#include <Arduino.h>
#include "interfaces/IWebClient.h"
#include "interfaces/IWebSocket.h"

// Forward declarations
class DIYablesWebAppServer;

/**
 * Abstract base class for web application pages.
 * Each page type (WebDigitalPins, WebMonitor, etc.) inherits from this class.
 */
class DIYablesWebAppPageBase {
public:
    DIYablesWebAppPageBase(const String& pagePath);
    virtual ~DIYablesWebAppPageBase() = default;
    
    // Pure virtual methods that must be implemented by derived classes
    virtual void handleHTTPRequest(IWebClient& client) = 0;
    virtual void handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) = 0;
    
    // Virtual methods with default implementations
    virtual void onWebSocketConnection(IWebSocket& ws);
    virtual void onWebSocketClose(IWebSocket& ws);
    
    // Page info method - each page defines its own display info  
    virtual const char* getPageInfo() const = 0;
    
    // Navigation info method - each page defines its own home page button
    virtual String getNavigationInfo() const = 0;
    
    // Getters
    const char* getPagePath() const { return pagePath.c_str(); }
    
    // Enable/disable functionality
    virtual bool isEnabled() const { return enabled; }
    virtual void setEnabled(bool enable) { enabled = enable; }
    
    // Common utility methods
    void sendHTTPHeader(IWebClient& client, const char* contentType = "text/html");
    void sendWebSocketMessage(IWebSocket& ws, const char* message);
    void broadcastToAllClients(const char* message);
    void sendLargeHTML(IWebClient& client, const char* html);  // NEW: Chunked HTML sending
    
protected:
    String pagePath;
    bool enabled;  // Each page manages its own enabled state
    DIYablesWebAppServer* server;  // Reference to server
    
    // Allow server to set reference
    friend class DIYablesWebAppServer;
    void setServer(DIYablesWebAppServer* srv) { server = srv; }
};

#endif
