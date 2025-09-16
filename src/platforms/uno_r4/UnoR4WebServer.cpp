#ifdef ARDUINO_UNOR4_WIFI
#include "UnoR4WebServer.h"

// Constructor
UnoR4WebServer::UnoR4WebServer(uint16_t serverPort) : server(serverPort), port(serverPort) {}

// Server lifecycle
bool UnoR4WebServer::begin() {
    server.begin();
    return true; // WiFiServer.begin() doesn't return a status
}

void UnoR4WebServer::end() {
    server.end();
}

// Client management
IWebClient* UnoR4WebServer::available() {
    WiFiClient client = server.available();
    if (client) {
        return new UnoR4WebClient(client);
    }
    return nullptr;
}

// Configuration
uint16_t UnoR4WebServer::getPort() const {
    return port;
}

#endif // ARDUINO_UNOR4_WIFI
