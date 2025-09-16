#ifndef DIYABLES_WEB_TABLE_PAGE_H
#define DIYABLES_WEB_TABLE_PAGE_H

#include "DIYablesWebAppPageBase.h"

// Maximum number of table rows
#define MAX_TABLE_ROWS 20

// Callback function pointer specific to WebTable
extern void (*webTableValueRequestCallback)();

/**
 * WebTable page handler - manages a two-column table display with real-time value updates
 */
class DIYablesWebTablePage : public DIYablesWebAppPageBase {
private:
    String attributes[MAX_TABLE_ROWS];
    int rowCount;
    
public:
    DIYablesWebTablePage();
    
    // Inherited virtual methods
    void handleHTTPRequest(IWebClient& client) override;
    void handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) override;
    const char* getPageInfo() const override;
    String getNavigationInfo() const override;
    
    // Table management methods
    void addRow(const String& attribute);
    void clearTable();
    int getRowCount() const;
    String getAttribute(int index) const;
    
    // Callback setters
    void onTableValueRequest(void (*callback)());
    
    // Send methods
    void sendToWebTable(const char* message);
    void sendToWebTable(const String& message);
    void sendValueUpdate(const String& attribute, const String& value);
    void sendValueUpdate(int index, const String& value);
};

#endif
