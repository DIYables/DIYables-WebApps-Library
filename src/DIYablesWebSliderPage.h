#ifndef DIYABLES_WEB_SLIDER_PAGE_H
#define DIYABLES_WEB_SLIDER_PAGE_H

#include "DIYablesWebAppPageBase.h"

// Callback function pointers specific to WebSlider
extern void (*webSliderCallback)(int slider1, int slider2);
extern void (*webSliderConfigCallback)();

/**
 * WebSlider page handler - manages slider interface
 */
class DIYablesWebSliderPage : public DIYablesWebAppPageBase {
public:
    DIYablesWebSliderPage();
    
    // Inherited virtual methods
    void handleHTTPRequest(IWebClient& client) override;
    void handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) override;
    const char* getPageInfo() const override;
    String getNavigationInfo() const override;
    
    // Callback setters
    void onSliderValueFromWeb(void (*callback)(int slider1, int slider2));
    void onSliderValueToWeb(void (*callback)());
    
    // Send methods
    void sendToWebSlider(const String& message);
    void sendToWebSlider(int slider1, int slider2);  // Convenience method for sending values
};

#endif
