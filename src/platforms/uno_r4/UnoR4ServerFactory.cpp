#ifdef ARDUINO_UNOR4_WIFI
#include "UnoR4ServerFactory.h"

// Factory methods
INetworkProvider* UnoR4ServerFactory::createNetworkProvider() {
    return new UnoR4NetworkProvider();
}

IWebServer* UnoR4ServerFactory::createWebServer(uint16_t port) {
    return new UnoR4WebServer(port);
}

IWebSocketServer* UnoR4ServerFactory::createWebSocketServer(uint16_t port) {
    return new UnoR4WebSocketServer(port);
}

// Platform information
String UnoR4ServerFactory::getPlatformName() const {
    return "Arduino Uno R4 WiFi";
}

#endif // ARDUINO_UNOR4_WIFI
