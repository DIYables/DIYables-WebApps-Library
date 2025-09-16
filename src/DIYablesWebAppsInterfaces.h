#ifndef DIYABLES_WEBAPPS_INTERFACES_H
#define DIYABLES_WEBAPPS_INTERFACES_H

/**
 * DIYables WebApps Library - Public Interfaces
 * 
 * This header provides the public interfaces that other platform libraries
 * should implement to extend DIYables WebApps to new platforms.
 * 
 * Usage for platform extension libraries:
 * 1. Include this header: #include <DIYablesWebAppsInterfaces.h>
 * 2. Implement all the I* interfaces for your platform
 * 3. Create a ServerFactory that creates your implementations
 * 4. Users can then use your factory with DIYablesWebAppServer
 * 
 * Example platform extension library structure:
 * MyPlatformWebApps/
 * ├── library.properties
 * ├── src/
 * │   ├── MyServerFactory.h
 * │   ├── MyPlatformWebClient.h
 * │   ├── MyPlatformWebServer.h
 * │   ├── MyPlatformWebSocket.h
 * │   ├── MyPlatformWebSocketServer.h
 * │   └── MyPlatformNetworkProvider.h
 * └── examples/
 *     └── MyPlatformExample/
 *         └── MyPlatformExample.ino
 */

// Core abstraction interfaces
#include "interfaces/INetworkProvider.h"
#include "interfaces/IWebServer.h"
#include "interfaces/IWebSocketServer.h"
#include "interfaces/IWebClient.h"
#include "interfaces/IWebSocket.h"

// Server factory interface
#include "interfaces/IServerFactory.h"

#endif // DIYABLES_WEBAPPS_INTERFACES_H
