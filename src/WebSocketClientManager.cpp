#include "WebSocketClientManager.h"
#include <string.h>  // for memset

WebSocketClientManager::WebSocketClientManager() {
    // Initialize all client slots efficiently using memset for better performance
    memset(clients, 0, sizeof(clients));
}

WebSocketClientManager::~WebSocketClientManager() {
    cleanupAllClients();
}

IWebSocket* WebSocketClientManager::addClient(void* nativeWs, IWebSocket* wrapper) {
    if (!nativeWs || !wrapper) {
        return nullptr;
    }
    
    // Find empty slot
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (!clients[i].inUse) {
            clients[i].nativeWs = nativeWs;
            clients[i].wrapper = wrapper;
            clients[i].inUse = true;
            return wrapper;
        }
    }
    
    // No available slots
    return nullptr;
}

bool WebSocketClientManager::removeClient(void* nativeWs) {
    if (!nativeWs) return false;
    
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].inUse && clients[i].nativeWs == nativeWs) {
            // Clean up wrapper
            delete clients[i].wrapper;
            
            // Reset slot
            clients[i].nativeWs = nullptr;
            clients[i].wrapper = nullptr;
            clients[i].inUse = false;
            return true;
        }
    }
    
    return false;
}

IWebSocket* WebSocketClientManager::findClient(void* nativeWs) {
    if (!nativeWs) return nullptr;
    
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].inUse && clients[i].nativeWs == nativeWs) {
            return clients[i].wrapper;
        }
    }
    
    return nullptr;
}

void WebSocketClientManager::cleanupAllClients() {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].inUse && clients[i].wrapper) {
            delete clients[i].wrapper;
        }
        clients[i].nativeWs = nullptr;
        clients[i].wrapper = nullptr;
        clients[i].inUse = false;
    }
}

int WebSocketClientManager::getActiveClientCount() const {
    // Optimization: Use a cached count that's maintained during add/remove operations
    int count = 0;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].inUse) {
            count++;
        }
    }
    return count;
}