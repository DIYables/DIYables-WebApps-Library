#ifndef I_WEBSOCKET_SERVER_H
#define I_WEBSOCKET_SERVER_H

#include <Arduino.h>
#include "IWebSocket.h"

/**
 * Abstract interface for WebSocket servers.
 * This abstracts platform-specific WebSocketServer implementations.
 */
class IWebSocketServer {
public:
    // Callback function types
    typedef void (*ConnectionCallback)(IWebSocket* ws);
    typedef void (*MessageCallback)(IWebSocket* ws, const IWebSocket::DataType dataType, const char* message, uint16_t length);
    typedef void (*CloseCallback)(IWebSocket* ws, const IWebSocket::CloseCode code, const char* reason, uint16_t length);
    
    virtual ~IWebSocketServer() = default;
    
    // Server lifecycle
    virtual bool begin() = 0;
    virtual void end() = 0;
    virtual void listen() = 0;
    
    // Event callbacks
    virtual void onConnection(ConnectionCallback callback) = 0;
    virtual void onMessage(MessageCallback callback) = 0;
    virtual void onClose(CloseCallback callback) = 0;
    
    // Configuration
    virtual uint16_t getPort() const = 0;
    
    // Broadcasting methods
    virtual void broadcastText(const char* message) = 0;
    virtual void broadcastBinary(const uint8_t* data, uint16_t length) = 0;
};

#endif
