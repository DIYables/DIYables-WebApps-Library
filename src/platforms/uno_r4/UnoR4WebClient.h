#ifndef UNO_R4_WEB_CLIENT_H
#define UNO_R4_WEB_CLIENT_H

#ifdef ARDUINO_UNOR4_WIFI

#include "../../interfaces/IWebClient.h"
#include <UnoR4WiFi_WebServer.h>

/**
 * Arduino Uno R4 WiFi implementation of IWebClient.
 * Wraps the UnoR4WiFi WiFiClient class.
 */
class UnoR4WebClient : public IWebClient {
private:
    WiFiClient client;
    
public:
    UnoR4WebClient(WiFiClient wifiClient);
    virtual ~UnoR4WebClient();
    
    // Connection management
    bool connected() override;
    void stop() override;
    
    // Stream interface implementation
    int available() override;
    int read() override;
    int peek() override;
    size_t write(uint8_t data) override;
    size_t write(const uint8_t* buffer, size_t size) override;
    void flush() override;
    
    // Additional convenience methods (use default implementations from IWebClient)
    String readStringUntil(char terminator) override;
    size_t println(const String& str) override;
    size_t println() override;
    size_t print(const String& str) override;
};

#endif // ARDUINO_UNOR4_WIFI

#endif
