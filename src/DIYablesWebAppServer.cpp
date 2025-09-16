#include "DIYablesWebAppServer.h"

// Static instance pointer
DIYablesWebAppServer* DIYablesWebAppServer::instance = nullptr;

DIYablesWebAppServer::DIYablesWebAppServer(IServerFactory& factory, uint16_t httpPort, uint16_t wsPort) 
    : serverFactory(&factory), httpPort(httpPort), wsPort(wsPort), isInitialized(false),
      pageCount(0), notFoundPage(nullptr), activeClientCount(0) {
    
    // Set static instance pointer
    instance = this;
    
    // Create platform-specific implementations using the factory
    networkProvider = serverFactory->createNetworkProvider();
    httpServer = serverFactory->createWebServer(httpPort);
    wsServer = serverFactory->createWebSocketServer(wsPort);
    
    // Initialize pages array
    for (int i = 0; i < MAX_PAGES; i++) {
        pages[i] = nullptr;
    }
    
    // Initialize WebSocket clients array
    for (int i = 0; i < MAX_WEBSOCKET_CLIENTS; i++) {
        webSocketClients[i] = nullptr;
    }
}

DIYablesWebAppServer::~DIYablesWebAppServer() {
    cleanup();
}

// WebSocket event handlers
void DIYablesWebAppServer::onWebSocketConnection(IWebSocket* ws) {
    Serial.println("New WebSocket connection established");
    
    if (!instance) return;
    
    // Add client to tracking list - only proceed if successful like old version
    if (instance->addWebSocketClient(ws)) {
        // Set up message and close handlers for this specific connection
        ws->onMessage(onWebSocketMessage);
        ws->onClose(onWebSocketClose);
        
        // Send welcome message like the old working version
        const char welcome[] = "Connected to DIYables WebApp!";
        ws->sendText(welcome);
    }
}

void DIYablesWebAppServer::cleanup() {
    cleanupPages();
    
    // Clean up platform implementations
    delete networkProvider;
    delete httpServer;
    delete wsServer;
    
    // Server factory is owned by the user, so we don't delete it
    
    networkProvider = nullptr;
    httpServer = nullptr;
    wsServer = nullptr;
    serverFactory = nullptr;
}

void DIYablesWebAppServer::cleanupPages() {
    for (int i = 0; i < pageCount; i++) {
        delete pages[i];
        pages[i] = nullptr;
    }
    pageCount = 0;
    
    delete notFoundPage;
    notFoundPage = nullptr;
}

// Dynamic app management methods
bool DIYablesWebAppServer::addApp(DIYablesWebAppPageBase* app) {
    if (!app || pageCount >= MAX_PAGES) {
        Serial.println("ERROR: Cannot add app - null pointer or max pages reached");
        return false;
    }
    
    // Check if app with same path already exists
    const char* appPath = app->getPagePath();  // Cache the path
    for (int i = 0; i < pageCount; i++) {
        if (pages[i] && strcmp(pages[i]->getPagePath(), appPath) == 0) {
            Serial.print("ERROR: App with path '");
            Serial.print(appPath);
            Serial.println("' already exists");
            return false;
        }
    }
    
    // Add the app
    pages[pageCount] = app;
    app->setServer(this);
    pageCount++;
    
    Serial.print("INFO: Added app ");
    Serial.println(appPath);
    return true;
}

bool DIYablesWebAppServer::removeApp(const char* pagePath) {
    if (!pagePath) return false;
    
    for (int i = 0; i < pageCount; i++) {
        if (pages[i] && strcmp(pages[i]->getPagePath(), pagePath) == 0) {
            delete pages[i];
            
            // Shift remaining pages down (optimized with memmove for better performance)
            for (int j = i; j < pageCount - 1; j++) {
                pages[j] = pages[j + 1];
            }
            pages[pageCount - 1] = nullptr;
            pageCount--;
            
            Serial.print("INFO: Removed app ");
            Serial.println(pagePath);
            return true;
        }
    }
    
    Serial.print("ERROR: App with path '");
    Serial.print(pagePath);
    Serial.println("' not found");
    return false;
}

DIYablesWebAppPageBase* DIYablesWebAppServer::getApp(const char* pagePath) {
    if (!pagePath) return nullptr;
    
    for (int i = 0; i < pageCount; i++) {
        if (pages[i] && strcmp(pages[i]->getPagePath(), pagePath) == 0) {
            return pages[i];
        }
    }
    return nullptr;
}

bool DIYablesWebAppServer::startServers() {
    Serial.println("DIYables WebApp Library");
    Serial.print("Platform: ");
    Serial.println(getPlatformName());

    Serial.println("Network connected!");
    Serial.print("IP address: ");
    Serial.println(getLocalIP());
    
    // Start HTTP server
    if (!httpServer->begin()) {
        Serial.println("Failed to start HTTP server!");
        return false;
    }
    Serial.print("HTTP server started on port ");
    Serial.println(httpPort);
    
    // Configure WebSocket server
    Serial.println("Configuring WebSocket server callbacks...");
    wsServer->onConnection(onWebSocketConnection);
    wsServer->onMessage(onWebSocketMessage);
    
    // Start WebSocket server
    if (!wsServer->begin()) {
        Serial.println("Failed to start WebSocket server!");
        return false;
    }
    Serial.print("WebSocket server started on port ");
    Serial.println(wsPort);
    
    isInitialized = true;
    printConnectionInfo();
    
    return true;
}

bool DIYablesWebAppServer::begin() {
    // Connect to network (parameterless - for Ethernet or pre-configured)
    if (!networkProvider->begin()) {
        Serial.println("Failed to connect to network!");
        return false;
    }

    return startServers();
}

bool DIYablesWebAppServer::begin(const char* ssid, const char* password) {
    // Connect to network
    if (!networkProvider->begin(ssid, password)) {
        Serial.println("Failed to connect to network!");
        return false;
    }

    return startServers();
}

void DIYablesWebAppServer::loop() {
    if (!isInitialized) return;
    
    // Handle HTTP requests
    IWebClient* httpClient = httpServer->available();
    if (httpClient) {
        handleHTTPClient(httpClient);
        delete httpClient;
        delay(10);
        return;
    }
    
    // Handle WebSocket connections
    wsServer->listen();
    
    // Small yield to prevent watchdog issues
    yield();
}

void DIYablesWebAppServer::handleHTTPClient(IWebClient* client) {
    static char request[256];  // Static buffer to avoid repeated allocation
    static char line[128];     // Static buffer for reading lines
    request[0] = '\0';         // Clear request buffer
    
    // Read HTTP request using char buffers
    while (client->connected() && client->available()) {
        int bytesRead = 0;
        char c;
        
        // Read line character by character into buffer
        while (client->available() && bytesRead < sizeof(line) - 1) {
            c = client->read();
            if (c == '\n') break;
            if (c != '\r') {
                line[bytesRead++] = c;
            }
        }
        line[bytesRead] = '\0';
        
        // Check for end of HTTP headers
        if (bytesRead == 0) break;
        
        // Store first line as request
        if (request[0] == '\0') {
            strncpy(request, line, sizeof(request) - 1);
            request[sizeof(request) - 1] = '\0';
        }
    }
    
    // Extract path from request using char array operations
    static char path[64];  // Static buffer for path
    path[0] = '\0';
    
    char* getPos = strstr(request, "GET ");
    if (getPos) {
        getPos += 4; // Skip "GET "
        char* httpPos = strstr(getPos, " HTTP");
        if (httpPos && httpPos > getPos) {
            int pathLen = httpPos - getPos;
            if (pathLen < sizeof(path)) {
                strncpy(path, getPos, pathLen);
                path[pathLen] = '\0';
            }
        }
    }
    
    // Get page handler and route request
    DIYablesWebAppPageBase* pageHandler = getPageHandler(path);
    if (pageHandler) {
        pageHandler->handleHTTPRequest(*client);
    } else if (notFoundPage) {
        notFoundPage->handleHTTPRequest(*client);
    } else {
        // Fallback: Send basic 404 response if no NotFound page is configured
        client->println("HTTP/1.1 404 Not Found");
        client->println("Content-Type: text/html");
        client->println("Connection: close");
        client->println();
        client->println("<html><body><h1>404 - Page Not Found</h1></body></html>");
    }
    
    // Ensure response is fully transmitted before closing
    client->flush();
    delay(50);  // Give time for response to be sent completely
    client->stop();
}

DIYablesWebAppPageBase* DIYablesWebAppServer::getPageHandler(const String& path) {
    for (int i = 0; i < pageCount; i++) {
        if (pages[i]) {
            if (strcmp(pages[i]->getPagePath(), path.c_str()) == 0) {
                // Check if the page is enabled (each page manages its own state)
                if (pages[i]->isEnabled()) {
                    return pages[i];
                } else {
                    return nullptr; // Page is disabled, will trigger 404
                }
            }
        }
    }
    
    return nullptr; // Will trigger 404 page
}

void DIYablesWebAppServer::onWebSocketMessage(IWebSocket* ws, const IWebSocket::DataType dataType, const char* message, uint16_t length) {
    if (!instance) {
        Serial.println("ERROR: No instance available");
        return;
    }
    
    if (dataType == IWebSocket::TEXT) {
        
        // OLD METHOD: Send message to all pages, let each page decide if it should handle it
        // This follows the Open/Closed Principle - adding new pages doesn't require server changes
        for (int i = 0; i < instance->pageCount; i++) {
            if (instance->pages[i]) {
                instance->pages[i]->handleWebSocketMessage(*ws, message, length);
            }
        }
    }
}

void DIYablesWebAppServer::onWebSocketClose(IWebSocket* ws, const IWebSocket::CloseCode code, const char* reason, uint16_t length) {
    Serial.print("WebSocket client disconnected (code: ");
    Serial.print((int)code);
    Serial.println(")");
    
    if (instance) {
        instance->removeWebSocketClient(ws);
    }
}

void DIYablesWebAppServer::broadcastMessage(const char* message) {
    if (!message || strlen(message) == 0) {
        return;
    }
    
    // Use platform's efficient broadcasting method first
    if (wsServer) {
        wsServer->broadcastText(message);
        return;
    }
    
    // Fallback to individual client sends (for platforms without efficient broadcasting)
    int sentCount = 0;
    for (int i = 0; i < MAX_WEBSOCKET_CLIENTS; i++) {
        if (webSocketClients[i] != nullptr) {
            webSocketClients[i]->sendText(message);
            sentCount++;
        }
    }
}

// Utility methods
String DIYablesWebAppServer::getLocalIP() {
    return networkProvider ? networkProvider->getLocalIP() : "0.0.0.0";
}

bool DIYablesWebAppServer::isConnected() {
    return networkProvider ? networkProvider->isConnected() : false;
}

void DIYablesWebAppServer::printConnectionInfo() {
    if (!isConnected()) {
        Serial.println("Not connected to network");
        return;
    }
    
    String ip = getLocalIP();
    Serial.println("\n==========================================");
    Serial.println("        DIYables WebApp Ready!          ");
    Serial.println("==========================================");
    Serial.print("📱 Web Interface: http://");
    Serial.println(ip);
    Serial.print("🔗 WebSocket: ws://");
    Serial.print(ip);
    Serial.print(":");
    Serial.println(wsPort);
    Serial.println("\n📋 Available Applications:");
    
    // Combine page info with base URL
    String baseURL = "http://" + ip;
    for (int i = 0; i < pageCount; i++) {
        if (pages[i]) {
            const char* pageInfo = pages[i]->getPageInfo();
            if (strlen(pageInfo) > 0) {  // Only print non-empty page info
                Serial.print("   ");      // Add leading whitespace
                Serial.print(pageInfo);
                Serial.print(": ");       // Add colon separator
                Serial.print(baseURL);
                Serial.println(pages[i]->getPagePath());
            }
        }
    }
    
    if (pageCount == 0) {
        Serial.println("   (No applications added)");
    }
    
    Serial.println("==========================================\n");
}

int DIYablesWebAppServer::getConnectedClientCount() {
    // Return the actual tracked client count
    return activeClientCount;
}

bool DIYablesWebAppServer::addWebSocketClient(IWebSocket* ws) {
    if (!ws) return false;
    
    for (int i = 0; i < MAX_WEBSOCKET_CLIENTS; i++) {
        if (webSocketClients[i] == nullptr) {
            webSocketClients[i] = ws;
            activeClientCount++;
            return true;
        }
    }
    
    Serial.println("WARNING: Maximum WebSocket clients reached at DIYablesWebAppServer level!");
    return false;
}

bool DIYablesWebAppServer::removeWebSocketClient(IWebSocket* ws) {
    if (!ws) return false;
    
    for (int i = 0; i < MAX_WEBSOCKET_CLIENTS; i++) {
        if (webSocketClients[i] == ws) {
            webSocketClients[i] = nullptr;
            activeClientCount--;
            return true;
        }
    }
    
    Serial.println("WARNING: WebSocket client not found in DIYablesWebAppServer client list!");
    return false;
}

String DIYablesWebAppServer::getPlatformName() {
    return serverFactory ? serverFactory->getPlatformName() : "Unknown Platform";
}
