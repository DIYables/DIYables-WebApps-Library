#ifndef I_NETWORK_PROVIDER_H
#define I_NETWORK_PROVIDER_H

#include <Arduino.h>

/**
 * Abstract interface for network connectivity providers.
 * This abstracts platform-specific WiFi implementations.
 */
class INetworkProvider {
public:
    // Network status
    enum Status {
        IDLE_STATUS = 0,
        NO_SSID_AVAIL = 1,
        SCAN_COMPLETED = 2,
        CONNECTED = 3,
        CONNECT_FAILED = 4,
        CONNECTION_LOST = 5,
        DISCONNECTED = 6
    };
    
    virtual ~INetworkProvider() = default;
    
    // Connection management
    virtual bool begin() { return false; }  // For Ethernet or pre-configured connections - override if needed
    virtual bool begin(const char* ssid, const char* password) = 0;
    virtual void end() = 0;
    virtual bool reconnect() = 0;
    
    // Status and information
    virtual Status getStatus() = 0;
    virtual bool isConnected() = 0;
    virtual String getLocalIP() = 0;
    virtual String getSSID() = 0;
    virtual int32_t getRSSI() = 0;
    
    // Convenience method
    virtual bool waitForConnection(int maxAttempts = 20, int delayMs = 500) {
        int attempts = 0;
        while (!isConnected() && attempts < maxAttempts) {
            delay(delayMs);
            attempts++;
        }
        return isConnected();
    }
};

#endif
