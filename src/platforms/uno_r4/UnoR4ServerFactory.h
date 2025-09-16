#ifndef UNO_R4_SERVER_FACTORY_H
#define UNO_R4_SERVER_FACTORY_H

#ifdef ARDUINO_UNOR4_WIFI

#include "../../interfaces/IServerFactory.h"
#include "UnoR4NetworkProvider.h"
#include "UnoR4WebServer.h"
#include "UnoR4WebSocketServer.h"

/**
 * Server factory for Arduino Uno R4 WiFi.
 * Creates UnoR4WiFi-specific implementations of network interfaces.
 */
class UnoR4ServerFactory : public IServerFactory {
public:
    UnoR4ServerFactory() = default;
    virtual ~UnoR4ServerFactory() = default;
    
    // Factory methods
    INetworkProvider* createNetworkProvider() override;
    IWebServer* createWebServer(uint16_t port) override;
    IWebSocketServer* createWebSocketServer(uint16_t port) override;
    
    // Platform information
    String getPlatformName() const override;
};

#endif // ARDUINO_UNOR4_WIFI

#endif
