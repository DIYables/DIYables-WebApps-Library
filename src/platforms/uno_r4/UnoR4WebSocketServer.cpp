#ifdef ARDUINO_UNOR4_WIFI
#include "UnoR4WebSocketServer.h"

// Static instance definition
UnoR4WebSocketServer* UnoR4WebSocketServer::instance = nullptr;

// Constructor and Destructor
UnoR4WebSocketServer::UnoR4WebSocketServer(uint16_t serverPort) 
    : server(serverPort), port(serverPort), 
      connectionCallback(nullptr), messageCallback(nullptr), closeCallback(nullptr) {
    instance = this;
}

UnoR4WebSocketServer::~UnoR4WebSocketServer() {
    if (instance == this) {
        instance = nullptr;
    }
    // Client cleanup is now handled by WebSocketClientManager
}

// Static wrapper functions - Simplified to use core client manager
void UnoR4WebSocketServer::onConnectionWrapper(net::WebSocket& ws) {
    if (instance && instance->connectionCallback) {
        // Create wrapper and let client manager handle it
        UnoR4WebSocket* wrapper = new UnoR4WebSocket(ws);
        IWebSocket* managedWrapper = instance->clientManager.addClient(&ws, wrapper);
        
        if (managedWrapper) {
            instance->connectionCallback(managedWrapper);
        } else {
            delete wrapper; // Client manager rejected it
            Serial.println("WARNING: Failed to add WebSocket client");
        }
    }
}

void UnoR4WebSocketServer::onMessageWrapper(net::WebSocket& ws, const net::WebSocket::DataType dataType, const char* message, uint16_t length) {
    if (instance && instance->messageCallback) {
        IWebSocket* wrapper = instance->clientManager.findClient(&ws);
        if (wrapper) {
            IWebSocket::DataType iDataType = (dataType == net::WebSocket::DataType::TEXT) 
                ? IWebSocket::TEXT 
                : IWebSocket::BINARY;
            instance->messageCallback(wrapper, iDataType, message, length);
        }
    }
}

void UnoR4WebSocketServer::onCloseWrapper(net::WebSocket& ws, const net::WebSocket::CloseCode code, const char* reason, uint16_t length) {
    if (instance && instance->closeCallback) {
        IWebSocket* wrapper = instance->clientManager.findClient(&ws);
        if (wrapper) {
            IWebSocket::CloseCode iCode = static_cast<IWebSocket::CloseCode>(code);
            instance->closeCallback(wrapper, iCode, reason, length);
            
            // Let client manager handle cleanup
            instance->clientManager.removeClient(&ws);
        }
    }
}

// Server lifecycle
bool UnoR4WebSocketServer::begin() {
    return server.begin();
}

void UnoR4WebSocketServer::end() {
    // Clear callbacks and let client manager cleanup clients
    connectionCallback = nullptr;
    messageCallback = nullptr;
    closeCallback = nullptr;
    clientManager.cleanupAllClients();
}

void UnoR4WebSocketServer::listen() {
    server.loop();
}

// Event callbacks
void UnoR4WebSocketServer::onConnection(ConnectionCallback callback) {
    connectionCallback = callback;
    server.onOpen(onConnectionWrapper);
}

void UnoR4WebSocketServer::onMessage(MessageCallback callback) {
    messageCallback = callback;
    server.onMessage(onMessageWrapper);
}

void UnoR4WebSocketServer::onClose(CloseCallback callback) {
    closeCallback = callback;
    server.onClose(onCloseWrapper);
}

// Broadcasting methods - PURE TRANSPORT LAYER
void UnoR4WebSocketServer::broadcastText(const char* message) {
    if (message) {
        yield();
        server.broadcastTXT(message);
    }
}

void UnoR4WebSocketServer::broadcastBinary(const uint8_t* data, uint16_t length) {
    yield();
    server.broadcastBIN(data, length);
}

// Configuration
uint16_t UnoR4WebSocketServer::getPort() const {
    return port;
}

#endif // ARDUINO_UNOR4_WIFI
