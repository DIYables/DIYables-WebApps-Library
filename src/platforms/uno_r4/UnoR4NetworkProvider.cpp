#ifdef ARDUINO_UNOR4_WIFI
#include "UnoR4NetworkProvider.h"

// Connection management
bool UnoR4NetworkProvider::begin(const char* ssid, const char* password) {
    lastSSID = ssid;
    lastPassword = password;
    WiFi.begin(ssid, password);
    return waitForConnection();
}

void UnoR4NetworkProvider::end() {
    WiFi.end();
}

bool UnoR4NetworkProvider::reconnect() {
    // Arduino Uno R4 WiFi doesn't have a reconnect method, so disconnect and reconnect
    WiFi.disconnect();
    delay(1000);
    return WiFi.begin(lastSSID.c_str(), lastPassword.c_str()) == WL_CONNECTED;
}

// Status and information
UnoR4NetworkProvider::Status UnoR4NetworkProvider::getStatus() {
    uint8_t wifiStatus = WiFi.status();
    // Map WiFi status to our enum
    switch (wifiStatus) {
        case WL_IDLE_STATUS: return IDLE_STATUS;
        case WL_NO_SSID_AVAIL: return NO_SSID_AVAIL;
        case WL_SCAN_COMPLETED: return SCAN_COMPLETED;
        case WL_CONNECTED: return CONNECTED;
        case WL_CONNECT_FAILED: return CONNECT_FAILED;
        case WL_CONNECTION_LOST: return CONNECTION_LOST;
        case WL_DISCONNECTED: return DISCONNECTED;
        default: return IDLE_STATUS;
    }
}

bool UnoR4NetworkProvider::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

String UnoR4NetworkProvider::getLocalIP() {
    return WiFi.localIP().toString();
}

String UnoR4NetworkProvider::getSSID() {
    return WiFi.SSID();
}

int32_t UnoR4NetworkProvider::getRSSI() {
    return WiFi.RSSI();
}

// Private methods
bool UnoR4NetworkProvider::waitForConnection() {
    // Wait up to 10 seconds for connection
    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000) {
        delay(500);
    }
    return WiFi.status() == WL_CONNECTED;
}

#endif // ARDUINO_UNOR4_WIFI
