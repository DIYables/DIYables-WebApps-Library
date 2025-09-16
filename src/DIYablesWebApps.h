#ifndef DIYABLES_WEBAPPS_H
#define DIYABLES_WEBAPPS_H

/**
 * DIYables WebApps Library - Unified Entry Point
 * 
 * This library provides a modular web application framework for Arduino
 * with automatic platform detection and abstraction.
 * 
 * Supported platforms:
 * - Arduino Uno R4 WiFi (auto-detected)
 * - Other platforms (manual platform implementation required)
 * 
 * Usage examples:
 * 
 * 1. For supported platforms (Arduino Uno R4 WiFi):
 *    #include <DIYablesWebApps.h>
 *    UnoR4ServerFactory factory;
 *    DIYablesWebAppServer server(factory, 80, 81);
 *    DIYablesHomePage homePage;
 *    server.addApp(&homePage);
 *    server.begin("WiFi_SSID", "WiFi_Password");
 * 
 * 2. For other platforms:
 *    #include <YOUR_PLATFORM_platform.h>  // e.g., #include <ESP32_platform.h>
 *    #include <DIYablesWebApps.h>
 *    // Use your platform's specific implementation
 */

// Core abstraction interfaces (always included)
#include "interfaces/INetworkProvider.h"
#include "interfaces/IWebServer.h"
#include "interfaces/IWebSocketServer.h"
#include "interfaces/IWebClient.h"
#include "interfaces/IWebSocket.h"

// Server factory
#include "interfaces/IServerFactory.h"

// Core WebSocket client management
#include "WebSocketClientManager.h"

// Abstracted server implementation (uses dependency injection)
#include "DIYablesWebAppServer.h"

// Platform detection and automatic inclusion
#if defined(ARDUINO_UNOR4_WIFI)
    // Arduino Uno R4 WiFi - include platform-specific implementations
    #include "platforms/uno_r4/UnoR4Platform.h"
#endif

// Page base class (works with abstracted interfaces)
#include "DIYablesWebAppPageBase.h"

// Include built-in page implementations
#include "DIYablesHomePage.h"
#include "DIYablesWebMonitorPage.h"
#include "DIYablesWebChatPage.h"
#include "DIYablesWebSliderPage.h"
#include "DIYablesWebJoystickPage.h"
#include "DIYablesWebDigitalPinsPage.h"
#include "DIYablesWebPlotterPage.h"
#include "DIYablesWebAnalogGaugePage.h"
#include "DIYablesWebRotatorPage.h"
#include "DIYablesWebTemperaturePage.h"
#include "DIYablesWebRTCPage.h"
#include "DIYablesWebTablePage.h"
#include "DIYablesNotFoundPage.h"

#endif
