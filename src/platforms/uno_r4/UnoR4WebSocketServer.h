#ifndef UNO_R4_WEBSOCKET_SERVER_H
#define UNO_R4_WEBSOCKET_SERVER_H

#ifdef ARDUINO_UNOR4_WIFI

#include "../../interfaces/IWebSocketServer.h"
#include "../../WebSocketClientManager.h"
#include "UnoR4WebSocket.h"
#include <UnoR4WiFi_WebSocket.h>

/**
 * Arduino Uno R4 WiFi implementation of IWebSocketServer.
 * Minimal platform-specific wrapper - delegates client management to core.
 */
class UnoR4WebSocketServer : public IWebSocketServer {
private:
    UnoR4WiFi_WebSocket server;
    uint16_t port;
    
    // Store callbacks
    ConnectionCallback connectionCallback;
    MessageCallback messageCallback;
    CloseCallback closeCallback;
    
    // Use core client manager instead of platform-specific logic
    WebSocketClientManager clientManager;
    
    // Static wrapper functions to bridge between UnoR4WiFi callbacks and our interface
    static void onConnectionWrapper(net::WebSocket& ws);
    static void onMessageWrapper(net::WebSocket& ws, const net::WebSocket::DataType dataType, const char* message, uint16_t length);
    static void onCloseWrapper(net::WebSocket& ws, const net::WebSocket::CloseCode code, const char* reason, uint16_t length);
    
    // Static instance for callback bridging
    static UnoR4WebSocketServer* instance;
    
public:
    UnoR4WebSocketServer(uint16_t serverPort);
    virtual ~UnoR4WebSocketServer();
    
    // Server lifecycle
    bool begin() override;
    void end() override;
    void listen() override;
    
    // Event callbacks
    void onConnection(ConnectionCallback callback) override;
    void onMessage(MessageCallback callback) override;
    void onClose(CloseCallback callback) override;
    
    // Configuration
    uint16_t getPort() const override;
    
    // Broadcasting methods
    void broadcastText(const char* message) override;
    void broadcastBinary(const uint8_t* data, uint16_t length) override;
};

#endif // ARDUINO_UNOR4_WIFI

#endif
