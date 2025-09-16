#ifndef I_WEBSOCKET_H
#define I_WEBSOCKET_H

#include <Arduino.h>
#include <string.h>

/**
 * Abstract interface for WebSocket connections.
 * This abstracts platform-specific WebSocket implementations.
 */
class IWebSocket {
public:
    // Data types for WebSocket messages
    enum DataType {
        TEXT,
        BINARY
    };
    
    // Close codes for WebSocket connections
    enum CloseCode {
        NORMAL_CLOSURE = 1000,
        GOING_AWAY = 1001,
        PROTOCOL_ERROR = 1002,
        UNSUPPORTED_DATA = 1003,
        INVALID_FRAME_PAYLOAD_DATA = 1007,
        POLICY_VIOLATION = 1008,
        MESSAGE_TOO_BIG = 1009,
        INTERNAL_ERROR = 1011
    };
    
    virtual ~IWebSocket() = default;
    
    // Connection management
    virtual bool isConnected() = 0;
    virtual void close(CloseCode code = NORMAL_CLOSURE, const char* reason = nullptr) = 0;
    
    // Message handling
    virtual bool send(DataType dataType, const char* message, uint16_t length) = 0;
    virtual bool send(DataType dataType, const String& message) {
        return send(dataType, message.c_str(), message.length());
    }
    
    // Convenience methods
    virtual bool sendText(const char* message) {
        return send(TEXT, message, strlen(message));
    }
    
    virtual bool sendText(const String& message) {
        return send(TEXT, message);
    }
    
    virtual bool sendBinary(const uint8_t* data, uint16_t length) {
        return send(BINARY, (const char*)data, length);
    }
    
    // Callback management (per-connection event handling)
    virtual void onMessage(void (*callback)(IWebSocket* ws, const DataType dataType, const char* message, uint16_t length)) = 0;
    virtual void onClose(void (*callback)(IWebSocket* ws, const CloseCode code, const char* reason, uint16_t length)) = 0;
    
    // Client information
    virtual String getRemoteIP() = 0;
    virtual uint16_t getRemotePort() = 0;
};

#endif
