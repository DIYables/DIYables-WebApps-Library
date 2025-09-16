#include "DIYablesWebAppPageBase.h"
#include "DIYablesWebAppServer.h"

DIYablesWebAppPageBase::DIYablesWebAppPageBase(const String& pagePath) 
    : pagePath(pagePath), enabled(true), server(nullptr) {
}

void DIYablesWebAppPageBase::onWebSocketConnection(IWebSocket& ws) {
    // Default implementation - no welcome message to prevent frame corruption on Arduino Uno R4 WiFi
}

void DIYablesWebAppPageBase::onWebSocketClose(IWebSocket& ws) {
    // Default implementation - just log (optimized to avoid String concatenation)
    Serial.print("WebSocket client disconnected from ");
    Serial.println(pagePath);
}

void DIYablesWebAppPageBase::sendHTTPHeader(IWebClient& client, const char* contentType) {
    client.println("HTTP/1.1 200 OK");
    client.print("Content-Type: ");
    client.println(contentType);
    client.println("Connection: close");
    client.println();
}

void DIYablesWebAppPageBase::sendWebSocketMessage(IWebSocket& ws, const char* message) {
    ws.sendText(message);
}

void DIYablesWebAppPageBase::broadcastToAllClients(const char* message) {
    if (server) {
        server->broadcastMessage(message);
    }
}

void DIYablesWebAppPageBase::sendLargeHTML(IWebClient& client, const char* html) {
    // Send large HTML content in chunks to avoid TCP buffer overflow
    const char* ptr = html;
    const size_t CHUNK_SIZE = 1024;  // 1KB chunks to stay within Arduino Uno R4 WiFi limits
    size_t totalLength = strlen(html);
    size_t remaining = totalLength;
    
    while (remaining > 0) {
        size_t chunkSize = (remaining > CHUNK_SIZE) ? CHUNK_SIZE : remaining;
        
        // Create chunk string
        char chunk[CHUNK_SIZE + 1];
        strncpy(chunk, ptr, chunkSize);
        chunk[chunkSize] = '\0';
        
        // Send chunk
        client.print(chunk);
        client.flush();  // Ensure data is sent before next chunk
        
        // Move to next chunk
        ptr += chunkSize;
        remaining -= chunkSize;
        
        // Small delay to allow TCP stack to process
        if (remaining > 0) {
            delay(5);
        }
    }
}
