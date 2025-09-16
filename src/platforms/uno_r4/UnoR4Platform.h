#ifndef UNO_R4_PLATFORM_H
#define UNO_R4_PLATFORM_H

#ifdef ARDUINO_UNOR4_WIFI

/**
 * Arduino Uno R4 WiFi Platform Implementation
 * 
 * This header includes all the Arduino Uno R4 WiFi specific implementations
 * for the DIYables WebApps library platform abstraction system.
 * 
 * This file should only be included when compiling for Arduino Uno R4 WiFi.
 */

// Include Arduino Uno R4 WiFi specific implementations
#include "UnoR4ServerFactory.h"
#include "UnoR4NetworkProvider.h"
#include "UnoR4WebServer.h"
#include "UnoR4WebSocketServer.h"
#include "UnoR4WebClient.h"
#include "UnoR4WebSocket.h"

#endif // ARDUINO_UNOR4_WIFI

#endif // UNO_R4_PLATFORM_H
