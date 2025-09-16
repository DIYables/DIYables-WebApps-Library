#ifndef DIYABLES_WEB_TEMPERATURE_PAGE_H
#define DIYABLES_WEB_TEMPERATURE_PAGE_H

#include "DIYablesWebAppPageBase.h"

// Callback function pointers specific to WebTemperature
extern void (*webTemperatureConfigCallback)();

class DIYablesWebTemperaturePage : public DIYablesWebAppPageBase {
public:
    // Constructor with temperature range and unit configuration
    DIYablesWebTemperaturePage(float minTemp = 0.0, float maxTemp = 100.0, const String& unit = "°C");
    
    void sendTemperature(float temperature);
    
    // Inherited virtual methods
    void handleHTTPRequest(IWebClient& client) override;
    void handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) override;
    const char* getPageInfo() const override;
    String getNavigationInfo() const override;
    
    // Callback setter for temperature value updates
    void onTemperatureValueRequested(void (*callback)());
    
private:
    float _minTemp;
    float _maxTemp;
    String _unit;
    bool _configSent;
};

#endif
