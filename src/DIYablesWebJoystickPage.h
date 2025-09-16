#ifndef DIYABLES_WEB_JOYSTICK_PAGE_H
#define DIYABLES_WEB_JOYSTICK_PAGE_H

#include "DIYablesWebAppPageBase.h"

// Callback function pointers specific to WebJoystick
extern void (*webJoystickCallback)(int x, int y);
extern void (*webJoystickConfigCallback)();

/**
 * WebJoystick page handler - manages joystick interface
 */
class DIYablesWebJoystickPage : public DIYablesWebAppPageBase {
private:
    bool autoReturn;
    float sensitivity;

public:
    DIYablesWebJoystickPage(bool autoReturn = false, float sensitivity = 1.0);
    
    // Inherited virtual methods
    void handleHTTPRequest(IWebClient& client) override;
    void handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) override;
    const char* getPageInfo() const override;
    String getNavigationInfo() const override;
    
    // Configuration methods
    void setAutoReturn(bool enabled);
    bool getAutoReturn() const;
    void setSensitivity(float value);
    float getSensitivity() const;
    
    // Callback setters
    void onJoystickValueFromWeb(void (*callback)(int x, int y));
    void onJoystickValueToWeb(void (*callback)());
    
    // Send methods
    void sendToWebJoystick(const char* message);
    void sendToWebJoystick(int x, int y);  // Convenience method for sending values
};

#endif
