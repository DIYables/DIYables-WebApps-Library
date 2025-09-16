#ifndef DIYABLES_WEBAPP_SERVER_H
#define DIYABLES_WEBAPP_SERVER_H

#include "interfaces/INetworkProvider.h"
#include "interfaces/IWebServer.h"
#include "interfaces/IWebSocketServer.h"
#include "interfaces/IWebClient.h"
#include "interfaces/IWebSocket.h"
#include "interfaces/IServerFactory.h"
#include "DIYablesWebAppPageBase.h"

/**
 * Platform-agnostic main server class that manages HTTP and WebSocket servers,
 * and routes requests to appropriate page handlers.
 * 
 * MEMORY SAFETY NOTE: 
 * The constructor takes a factory by reference. To avoid memory safety issues,
 * ensure the factory object has proper lifetime:
 * 
 * SAFE:   static ESP32ServerFactory factory;  // Static or global
 * UNSAFE: ESP32ServerFactory factory;         // Stack object (can become invalid)
 * 
 * Or use convenience functions like createESP32WebAppServer() when available.
 */
class DIYablesWebAppServer {
private:
    IServerFactory* serverFactory;
    INetworkProvider* networkProvider;
    IWebServer* httpServer;
    IWebSocketServer* wsServer;
    uint16_t httpPort;
    uint16_t wsPort;
    bool isInitialized;
    
    // Dynamic page handlers storage
    static const int MAX_PAGES = 10;
    DIYablesWebAppPageBase* pages[MAX_PAGES];
    int pageCount;
    DIYablesWebAppPageBase* notFoundPage;  // Can be any page type, not just DIYablesNotFoundPage
    
    // WebSocket client management
    static const int MAX_WEBSOCKET_CLIENTS = 5;
    IWebSocket* webSocketClients[MAX_WEBSOCKET_CLIENTS];
    int activeClientCount;
    
    // Private methods
    void handleHTTPClient(IWebClient* client);
    DIYablesWebAppPageBase* getPageHandler(const String& path);
    void cleanupPages();
    void cleanup();
    bool startServers();  // Common server startup logic
    
    // Static callbacks for WebSocket events
    static void onWebSocketConnection(IWebSocket* ws);
    static void onWebSocketMessage(IWebSocket* ws, const IWebSocket::DataType dataType, const char* message, uint16_t length);
    static void onWebSocketClose(IWebSocket* ws, const IWebSocket::CloseCode code, const char* reason, uint16_t length);
    
public:
    // Static instance pointer for accessing from static callbacks
    static DIYablesWebAppServer* instance;
    
    // Constructor with server factory
    DIYablesWebAppServer(IServerFactory& factory, uint16_t httpPort = 80, uint16_t wsPort = 81);
    
    ~DIYablesWebAppServer();
    
    // Basic setup methods
    bool begin();  // For Ethernet or pre-configured connections
    bool begin(const char* ssid, const char* password);
    void loop();
    
    // Dynamic app management
    bool addApp(DIYablesWebAppPageBase* app);
    bool removeApp(const char* pagePath);
    DIYablesWebAppPageBase* getApp(const char* pagePath);
    int getAppCount() const { return pageCount; }
    DIYablesWebAppPageBase* getAppByIndex(int index) const { 
        return (index >= 0 && index < pageCount) ? pages[index] : nullptr; 
    }
    
    // 404 Not Found page management (optional for memory savings)
    template<typename PageType>
    void setNotFoundPage(const PageType& page) {
        // Clean up existing 404 page if any
        if (notFoundPage) {
            delete notFoundPage;
        }
        
        // Create a copy of the passed page
        notFoundPage = new PageType(page);
        notFoundPage->setServer(this);
    }
    
    // WebSocket client management
    bool addWebSocketClient(IWebSocket* ws);
    bool removeWebSocketClient(IWebSocket* ws);
    void broadcastMessage(const char* message);
    
    // Utility methods
    String getLocalIP();
    bool isConnected();
    void printConnectionInfo();
    int getConnectedClientCount();
    String getPlatformName();
};

#endif
