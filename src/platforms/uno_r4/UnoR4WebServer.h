#ifndef UNO_R4_WEB_SERVER_H
#define UNO_R4_WEB_SERVER_H

#ifdef ARDUINO_UNOR4_WIFI

#include "../../interfaces/IWebServer.h"
#include "UnoR4WebClient.h"
#include <UnoR4WiFi_WebServer.h>

/**
 * Arduino Uno R4 WiFi implementation of IWebServer.
 * Wraps the UnoR4WiFi WiFiServer class.
 */
class UnoR4WebServer : public IWebServer {
private:
    WiFiServer server;
    uint16_t port;
    
public:
    UnoR4WebServer(uint16_t serverPort);
    virtual ~UnoR4WebServer() = default;
    
    // Server lifecycle
    bool begin() override;
    void end() override;
    
    // Client management
    IWebClient* available() override;
    
    // Configuration
    uint16_t getPort() const override;
};

#endif // ARDUINO_UNOR4_WIFI

#endif
