#ifndef UNO_R4_WEBSOCKET_H
#define UNO_R4_WEBSOCKET_H

#ifdef ARDUINO_UNOR4_WIFI
#include "../../interfaces/IWebSocket.h"
#include <UnoR4WiFi_WebServer.h>

/**
 * Arduino Uno R4 WiFi implementation of IWebSocket.
 * Minimal platform wrapper - no static instance management.
 */
class UnoR4WebSocket : public IWebSocket {
private:
    WebSocket* webSocket;
    bool ownsWebSocket;
    
    // Callback storage
    void (*messageCallback)(IWebSocket* ws, const DataType dataType, const char* message, uint16_t length);
    void (*closeCallback)(IWebSocket* ws, const CloseCode code, const char* reason, uint16_t length);
    
public:
    UnoR4WebSocket(WebSocket* ws, bool takeOwnership = false);
    UnoR4WebSocket(WebSocket& ws);
    virtual ~UnoR4WebSocket();
    
    // Connection management
    bool isConnected() override;
    void close(CloseCode code = NORMAL_CLOSURE, const char* reason = nullptr) override;
    
    // Message handling
    bool send(DataType dataType, const char* message, uint16_t length) override;
    
    // Callback management (per-connection event handling)
    void onMessage(void (*callback)(IWebSocket* ws, const DataType dataType, const char* message, uint16_t length)) override;
    void onClose(void (*callback)(IWebSocket* ws, const CloseCode code, const char* reason, uint16_t length)) override;
    
    // Client information
    String getRemoteIP() override;
    uint16_t getRemotePort() override;
    
    // Internal method to get the underlying WebSocket for platform-specific operations
    WebSocket* getUnderlyingWebSocket();
};

#endif // ARDUINO_UNOR4_WIFI

#endif
