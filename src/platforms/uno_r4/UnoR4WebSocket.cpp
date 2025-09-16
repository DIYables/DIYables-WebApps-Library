#ifdef ARDUINO_UNOR4_WIFI
#include "UnoR4WebSocket.h"

// Constructors and Destructor
UnoR4WebSocket::UnoR4WebSocket(WebSocket* ws, bool takeOwnership) 
    : webSocket(ws), ownsWebSocket(takeOwnership), messageCallback(nullptr), closeCallback(nullptr) {
}

UnoR4WebSocket::UnoR4WebSocket(WebSocket& ws) 
    : webSocket(&ws), ownsWebSocket(false), messageCallback(nullptr), closeCallback(nullptr) {
}

UnoR4WebSocket::~UnoR4WebSocket() {
    if (ownsWebSocket && webSocket) {
        delete webSocket;
    }
}

// Connection management
bool UnoR4WebSocket::isConnected() {
    return webSocket != nullptr; // UnoR4WiFi WebSocket doesn't have a direct isConnected method
}

void UnoR4WebSocket::close(CloseCode code, const char* reason) {
    if (webSocket) {
        // Convert our enum to UnoR4WiFi enum
        WebSocket::CloseCode r4Code = static_cast<WebSocket::CloseCode>(code);
        webSocket->close(r4Code, true, reason, reason ? strlen(reason) : 0);
    }
}

// Message handling
bool UnoR4WebSocket::send(DataType dataType, const char* message, uint16_t length) {
    if (!webSocket) return false;
    
    // Additional validation like ESP32
    if (!message || length == 0) return false;
    
    // SIMPLE FIX: Add connection check to prevent sending to dead connections
    if (!isConnected()) return false;
    
    // Convert our enum to UnoR4WiFi enum
    WebSocket::DataType r4DataType = (dataType == TEXT) 
        ? WebSocket::DataType::TEXT 
        : WebSocket::DataType::BINARY;
    
    // FIXED: Add yield() like ESP32 to prevent frame corruption on Arduino Uno R4 WiFi
    yield();
    
    webSocket->send(r4DataType, message, strlen(message));
    
    return true; // UnoR4WiFi send method is void, so assume success
}

// Callback management - Simplified (callbacks are managed at server level)
void UnoR4WebSocket::onMessage(void (*callback)(IWebSocket* ws, const DataType dataType, const char* message, uint16_t length)) {
    messageCallback = callback;
    // Note: Actual callback registration happens at the server level via WebSocketClientManager
}

void UnoR4WebSocket::onClose(void (*callback)(IWebSocket* ws, const CloseCode code, const char* reason, uint16_t length)) {
    closeCallback = callback;
    // Note: Actual callback registration happens at the server level via WebSocketClientManager
}

// Client information
String UnoR4WebSocket::getRemoteIP() {
    // UnoR4WiFi WebSocket might not expose this directly
    // Return empty string or implement based on available methods
    return String(""); 
}

uint16_t UnoR4WebSocket::getRemotePort() {
    // UnoR4WiFi WebSocket might not expose this directly
    // Return 0 or implement based on available methods
    return 0;
}

// Internal method
WebSocket* UnoR4WebSocket::getUnderlyingWebSocket() { 
    return webSocket; 
}

#endif // ARDUINO_UNOR4_WIFI