#ifndef DIYABLES_WEB_ANALOG_GAUGE_PAGE_H
#define DIYABLES_WEB_ANALOG_GAUGE_PAGE_H

#include "DIYablesWebAppPageBase.h"

// Callback function pointer specific to WebAnalogGauge
extern void (*webAnalogGaugeValueRequestCallback)();

/**
 * WebAnalogGauge page handler - manages analog gauge interface
 */
class DIYablesWebAnalogGaugePage : public DIYablesWebAppPageBase {
public:
    DIYablesWebAnalogGaugePage(float minValue = 0.0, float maxValue = 100.0, const String& unit = "");
    
    // Inherited virtual methods
    void handleHTTPRequest(IWebClient& client) override;
    void handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) override;
    const char* getPageInfo() const override;
    String getNavigationInfo() const override;
    
    // Callback setters
    void onGaugeValueRequest(void (*callback)());
    
    // Send methods
    void sendToWebAnalogGauge(float value);
    void updateGaugeValue(float value);
    
private:
    float currentValue;
    float minValue;
    float maxValue;
    String unit;
};

#endif
