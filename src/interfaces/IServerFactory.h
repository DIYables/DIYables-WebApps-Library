#ifndef I_SERVER_FACTORY_H
#define I_SERVER_FACTORY_H

#include "INetworkProvider.h"
#include "IWebServer.h"
#include "IWebSocketServer.h"

/**
 * Abstract factory interface for creating platform-specific server implementations.
 * This allows the library to work with different Arduino platforms by providing
 * the appropriate server components for each platform.
 */
class IServerFactory {
public:
    virtual ~IServerFactory() = default;
    
    // Factory methods for creating platform-specific implementations
    virtual INetworkProvider* createNetworkProvider() = 0;
    virtual IWebServer* createWebServer(uint16_t port) = 0;
    virtual IWebSocketServer* createWebSocketServer(uint16_t port) = 0;
    
    // Platform information
    virtual String getPlatformName() const = 0;
};

#endif
