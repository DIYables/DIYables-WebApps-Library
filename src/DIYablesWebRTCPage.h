#ifndef DIYABLES_WEB_RTC_PAGE_H
#define DIYABLES_WEB_RTC_PAGE_H

#include "DIYablesWebAppPageBase.h"

// Callback function pointers specific to WebRTC
extern void (*webRTCTimeSyncCallback)(unsigned long unixTimestamp);
extern void (*webRTCLocalTimeSyncCallback)(int year, int month, int day, int hour, int minute, int second);
extern void (*webRTCConfigCallback)();

/**
 * WebRTC page handler - manages real-time clock display and time synchronization
 */
class DIYablesWebRTCPage : public DIYablesWebAppPageBase {
public:
    DIYablesWebRTCPage();
    
    // Inherited virtual methods
    void handleHTTPRequest(IWebClient& client) override;
    void handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) override;
    const char* getPageInfo() const override;
    String getNavigationInfo() const override;
    
    // Callback setters
    void onTimeSyncFromWeb(void (*callback)(unsigned long unixTimestamp));
    void onLocalTimeSyncFromWeb(void (*callback)(int year, int month, int day, int hour, int minute, int second));
    void onTimeRequestToWeb(void (*callback)());
    
    // Send methods
    void sendToWebRTC(const String& message);
    void sendTimeToWeb(unsigned long unixTimestamp);  // Convenience method for sending current time
    void sendTimeToWeb(int year, int month, int day, int hour, int minute, int second);  // Convenience method for sending time components
};

#endif
