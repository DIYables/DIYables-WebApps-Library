#ifndef UNO_R4_NETWORK_PROVIDER_H
#define UNO_R4_NETWORK_PROVIDER_H

#ifdef ARDUINO_UNOR4_WIFI

#include "../../interfaces/INetworkProvider.h"
#include <UnoR4WiFi_WebServer.h>

/**
 * Arduino Uno R4 WiFi implementation of INetworkProvider.
 * Wraps the UnoR4WiFi WiFi class.
 */
class UnoR4NetworkProvider : public INetworkProvider {
private:
    String lastSSID;
    String lastPassword;
    
public:
    UnoR4NetworkProvider() = default;
    virtual ~UnoR4NetworkProvider() = default;
    
    // Connection management
    bool begin(const char* ssid, const char* password) override;
    void end() override;
    bool reconnect() override;
    
    // Status and information
    Status getStatus() override;
    bool isConnected() override;
    String getLocalIP() override;
    String getSSID() override;
    int32_t getRSSI() override;

private:
    bool waitForConnection();
};

#endif // ARDUINO_UNOR4_WIFI

#endif
