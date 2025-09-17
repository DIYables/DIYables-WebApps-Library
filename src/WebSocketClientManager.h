#ifndef WEBSOCKET_CLIENT_MANAGER_H
#define WEBSOCKET_CLIENT_MANAGER_H

#include "interfaces/IWebSocket.h"

/**
 * Core WebSocket client management logic.
 * Platform implementations should delegate client management to this class.
 */
class WebSocketClientManager {
private:
    static const int MAX_CLIENTS = 5;
    
    struct ClientSlot {
        void* nativeWs;      // Platform-specific WebSocket pointer
        IWebSocket* wrapper; // Our interface wrapper
        bool inUse;
    };
    
    ClientSlot clients[MAX_CLIENTS];
    
public:
    WebSocketClientManager();
    ~WebSocketClientManager();
    
    // Client lifecycle management
    IWebSocket* addClient(void* nativeWs, IWebSocket* wrapper);
    bool removeClient(void* nativeWs);
    IWebSocket* findClient(void* nativeWs);
    
    // Cleanup
    void cleanupAllClients();
    int getActiveClientCount() const;
};

#endif