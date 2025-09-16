#ifndef DIYABLES_WEB_DIGITAL_PINS_PAGE_H
#define DIYABLES_WEB_DIGITAL_PINS_PAGE_H

#include "DIYablesWebAppPageBase.h"

// Pin mode constants
#define WEB_PIN_OUTPUT 0
#define WEB_PIN_INPUT 1

class DIYablesWebDigitalPinsPage : public DIYablesWebAppPageBase {
private:
    bool enabledPins[16];    // Track which pins are enabled for web access (pins 0-13)
    int pinModes[16];        // Track pin modes (OUTPUT, INPUT) for pins 0-13
    
    String buildPinConfigJson();
    String buildPinStatesJson();
    void handlePinCommand(const String& message, IWebSocket& ws);
    void handleBulkCommand(const String& command);
    void handlePinModeCommand(const String& message, IWebSocket& ws);

public:
    DIYablesWebDigitalPinsPage();
    
    // Override base class methods
    void handleHTTPRequest(IWebClient& client) override;
    void handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) override;
    const char* getPageInfo() const override;
    String getNavigationInfo() const override;
    
    // Pin management methods
    void enablePin(int pin, int mode = WEB_PIN_OUTPUT);
    void disablePin(int pin);
    void enableAllPins(int mode = WEB_PIN_OUTPUT);
    void disableAllPins();
    bool isPinEnabled(int pin);
    int getPinMode(int pin);
    void setPinMode(int pin, int mode);
    int getEnabledPinCount();
    
    // Callback setters
    void onPinWrite(void (*callback)(int pin, int state));       // For output pin control
    void onPinRead(int (*callback)(int pin));                    // For reading pin states
    void onPinModeChange(void (*callback)(int pin, int mode));   // For pin mode changes
    
    // Send methods
    void sendToWebDigitalPins(const String& message);
    void updatePinState(int pin, int state); // For real-time input monitoring
};

#endif
