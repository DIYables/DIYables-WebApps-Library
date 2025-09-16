#ifndef DIYABLES_WEB_ROTATOR_PAGE_H
#define DIYABLES_WEB_ROTATOR_PAGE_H

#include "DIYablesWebAppPageBase.h"

// Rotator mode constants
#define ROTATOR_MODE_CONTINUOUS 0
#define ROTATOR_MODE_LIMITED 1

// Callback function pointers specific to WebRotator
extern void (*webRotatorCallback)(float angle);
extern void (*webRotatorConfigCallback)();

/**
 * WebRotator page handler - manages rotatable disc interface
 */
class DIYablesWebRotatorPage : public DIYablesWebAppPageBase {
private:
    int rotatorMode;
    float minAngle;
    float maxAngle;

public:
    DIYablesWebRotatorPage(int mode);  // Constructor for ROTATOR_MODE_CONTINUOUS
    DIYablesWebRotatorPage(int mode, float minAng, float maxAng);  // Constructor for ROTATOR_MODE_LIMITED
    
    // Inherited virtual methods
    void handleHTTPRequest(IWebClient& client) override;
    void handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) override;
    const char* getPageInfo() const override;
    String getNavigationInfo() const override;
    
    // Configuration methods
    void setRotatorMode(int mode, float minAng = 0, float maxAng = 360);
    int getRotatorMode() const;
    float getMinAngle() const;
    float getMaxAngle() const;
    
    // Callback setters
    void onRotatorAngleFromWeb(void (*callback)(float angle));
    
    // Send methods
    void sendToWebRotator(const String& message);
    void sendToWebRotator(float angle);  // Convenience method for sending angle
};

#endif
