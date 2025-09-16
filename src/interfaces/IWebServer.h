#ifndef I_WEB_SERVER_H
#define I_WEB_SERVER_H

#include <Arduino.h>
#include "IWebClient.h"

/**
 * Abstract interface for HTTP web servers.
 * This abstracts platform-specific WiFiServer implementations.
 */
class IWebServer {
public:
    virtual ~IWebServer() = default;
    
    // Server lifecycle
    virtual bool begin() = 0;
    virtual void end() = 0;
    
    // Client management
    virtual IWebClient* available() = 0;
    
    // Configuration
    virtual uint16_t getPort() const = 0;
};

#endif
