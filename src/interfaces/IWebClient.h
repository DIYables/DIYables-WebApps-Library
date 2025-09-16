#ifndef I_WEB_CLIENT_H
#define I_WEB_CLIENT_H

#include <Arduino.h>
#include <Stream.h>

/**
 * Abstract interface for web clients (HTTP connections).
 * This abstracts platform-specific WiFiClient implementations.
 * WiFiClient typically inherits from Stream, so we use Stream as base.
 */
class IWebClient : public Stream {
public:
    virtual ~IWebClient() = default;
    
    // Connection management
    virtual bool connected() = 0;
    virtual void stop() = 0;
    
    // Stream interface (inherited)
    // These are already pure virtual in Stream:
    // virtual int available() = 0;
    // virtual int read() = 0;
    // virtual int peek() = 0;
    // virtual size_t write(uint8_t) = 0;
    // virtual void flush() = 0;
    
    // Additional convenience methods
    virtual String readStringUntil(char terminator) {
        return Stream::readStringUntil(terminator);
    }
    
    virtual size_t println(const String& str) {
        size_t n = print(str);
        n += println();
        return n;
    }
    
    virtual size_t println() {
        return print("\r\n");
    }
    
    virtual size_t print(const String& str) {
        return write((const uint8_t*)str.c_str(), str.length());
    }
};

#endif
