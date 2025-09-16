#ifdef ARDUINO_UNOR4_WIFI
#include "UnoR4WebClient.h"

// Constructor
UnoR4WebClient::UnoR4WebClient(WiFiClient wifiClient) 
    : client(wifiClient) {}

// Destructor
UnoR4WebClient::~UnoR4WebClient() {
    // No need to delete anything - client is stored by value
}

// Connection management
bool UnoR4WebClient::connected() {
    return client.connected();
}

void UnoR4WebClient::stop() {
    client.stop();
}

// Stream interface implementation
int UnoR4WebClient::available() {
    return client.available();
}

int UnoR4WebClient::read() {
    return client.read();
}

int UnoR4WebClient::peek() {
    return client.peek();
}

size_t UnoR4WebClient::write(uint8_t data) {
    return client.write(data);
}

size_t UnoR4WebClient::write(const uint8_t* buffer, size_t size) {
    return client.write(buffer, size);
}

void UnoR4WebClient::flush() {
    client.flush();
}

// Additional convenience methods
String UnoR4WebClient::readStringUntil(char terminator) {
    return client.readStringUntil(terminator);
}

size_t UnoR4WebClient::println(const String& str) {
    return client.println(str);
}

size_t UnoR4WebClient::println() {
    return client.println();
}

size_t UnoR4WebClient::print(const String& str) {
    return client.print(str);
}

#endif // ARDUINO_UNOR4_WIFI
